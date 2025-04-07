# Scrutiny
A tool to establish behavioral baselines for processes by tracing various behaviors. Goal: Detect Malicious Deviations

## Usage (baselining)
1. make
2. make run_<target process name> (sample target processes configured in makefile) (take note of PID)
3. make run_baseliner.c (enter the target PID)
4. Logs are stored in logs/<target process name>/.
