# Scrutiny
A tool to establish behavioral baselines for processes by tracing various behaviors. Goal: Detect Malicious Deviations

## Usage (preparation)
1. It's a linux program
2. sudo apt update
3. sudo apt install python3-tk

## Usage (baselining and monitoring)
1. navigate to Scrutiny directory
2. make clean (if necessary)
3. make
4. open a second terminal, run as admin
5. in user-level terminal, "make run targetProc0".  This is your baseline process.  take note of PID
6. in admin terminal, "make run baseliner".  immediately enter the previously noted PID
7. programs will exit together after approx 2 minutes

8. repeat the same steps using targetProc1 instead of targetProc0
9. targetProc1 is a carbon copy, but with an added suspicious syscall (access)

## Usage (analysis)
1. navigate to Scrutiny/src
2. python3 monitor.py
3. Twice, you will be prompted with a GUI file explorer focused on the logs directory
4. First, select the log in targetProc0
5. Next, select the log in targetProc1
6. An analysis will output to the console, showing an overview and any anomalies
