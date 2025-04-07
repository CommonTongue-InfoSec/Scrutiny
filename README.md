# Scrutiny
A tool to establish behavioral baselines for processes by tracing system calls, useful for detecting potential malicious deviations.

## Usage (baselining)
1. make
2. make run_<target process name> (sample target processes configured in makefile) (take note of PID)
3. make run_baseliner.c (enter the target PID)
4. Logs are stored in logs/<target process name>/.
