import os
import re
from collections import Counter
try:
    import tkinter as tk
    from tkinter import filedialog
    TKINTER_AVAILABLE = True
except ImportError:
    TKINTER_AVAILABLE = False

def select_file(prompt, initial_dir=None):
    
    if TKINTER_AVAILABLE:
        root = tk.Tk()
        root.withdraw()  
        
        file_path = filedialog.askopenfilename(
            title=prompt,
            initialdir=initial_dir if initial_dir and os.path.isdir(initial_dir) else os.getcwd()
        )
        root.destroy()
        return file_path if file_path else None
    else:
        
        while True:
            file_path = input(f"{prompt} (enter path): ").strip()
            if os.path.isfile(file_path):
                return file_path
            else:
                print(f"Error: '{file_path}' is not a valid file. Please try again.")
        return None

def parse_syscall_log(file_path):
    
    syscall_pattern = r"Syscall: (\d+) \("
    syscalls = []
    
    try:
        with open(file_path, 'r') as file:
            
            for line in file:
                match = re.search(syscall_pattern, line)
                if match:
                    syscall_num = int(match.group(1))
                    syscalls.append(syscall_num)
        
        return Counter(syscalls)
    
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        return Counter()

def compare_syscalls(baseline_counts, target_counts):
    
    anomalies = []
    all_syscalls = set(baseline_counts.keys()).union(target_counts.keys())
    total_baseline = sum(baseline_counts.values())
    total_target = sum(target_counts.values())

    for syscall in all_syscalls:
        baseline_count = baseline_counts.get(syscall, 0)
        target_count = target_counts.get(syscall, 0)
        
        
        baseline_freq = baseline_count / total_baseline if total_baseline > 0 else 0
        target_freq = target_count / total_target if total_target > 0 else 0
        
        
        if baseline_count == 0 and target_count > 0:
            anomalies.append(f"Syscall {syscall} detected in target ({target_count} times) but absent in baseline.")
        
        elif baseline_freq > 0 and target_freq > 2 * baseline_freq and target_count > 1:
            anomalies.append(f"Syscall {syscall} frequency increased significantly: "
                           f"Baseline {baseline_count} ({baseline_freq:.4f}), "
                           f"Target {target_count} ({target_freq:.4f})")

    return anomalies

def print_syscall_summary(counts, title):
    
    print(f"\n{title}:")
    total = sum(counts.values())
    for syscall, count in sorted(counts.items()):
        freq = count / total if total > 0 else 0
        print(f"Syscall {syscall}: {count} times ({freq:.4f})")

def main():
    
    script_dir = os.path.dirname(os.path.abspath(__file__))
    logs_dir = os.path.abspath(os.path.join(script_dir, "..", "logs"))
    
    
    if not os.path.isdir(logs_dir):
        print(f"Warning: Logs directory '{logs_dir}' does not exist. File dialog will open in current directory.")
        logs_dir = None

    
    print("Select the baseline syscall log file...")
    baseline_file = select_file("Select baseline syscall log file", initial_dir=logs_dir)
    if not baseline_file:
        print("No baseline file selected. Exiting.")
        return

    print("Select the target syscall log file...")
    target_file = select_file("Select target syscall log file", initial_dir=logs_dir)
    if not target_file:
        print("No target file selected. Exiting.")
        return

    
    baseline_counts = parse_syscall_log(baseline_file)
    target_counts = parse_syscall_log(target_file)

    if not baseline_counts:
        print("Baseline log is empty or invalid. Exiting.")
        return
    if not target_counts:
        print("Target log is empty or invalid. Exiting.")
        return

    
    print_syscall_summary(baseline_counts, "Baseline Log Syscall Counts")
    print_syscall_summary(target_counts, "Target Log Syscall Counts")

    
    anomalies = compare_syscalls(baseline_counts, target_counts)

    
    print("\nAnalysis Results:")
    if anomalies:
        print("Anomalies detected:")
        for anomaly in anomalies:
            print(f"- {anomaly}")
    else:
        print("No significant anomalies detected.")

if __name__ == "__main__":
    main()