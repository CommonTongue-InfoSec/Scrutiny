#include "syscalls.h"
#include <stddef.h>

const struct syscall_map syscall_table[] = {
    { 0, "read" },                  // Read from file
    { 1, "write" },                 // Write to file
    { 2, "open" },                  // Open file
    { 3, "close" },                 // Close file
    { 4, "stat" },                  // File status
    { 5, "fstat" },                 // File status by fd
    { 6, "lstat" },                 // Symbolic link status
    { 7, "poll" },                  // Wait for events
    { 8, "lseek" },                 // Reposition file offset
    { 9, "mmap" },                  // Map files/memory
    { 10, "mprotect" },             // Set memory protection
    { 11, "munmap" },               // Unmap memory
    { 12, "brk" },                  // Change data segment size
    { 13, "rt_sigaction" },         // Set signal handler
    { 14, "rt_sigprocmask" },       // Set signal mask
    { 15, "rt_sigreturn" },         // Return from signal
    { 16, "ioctl" },                // Device control
    { 17, "pread64" },              // Read at offset
    { 18, "pwrite64" },             // Write at offset
    { 19, "readv" },                // Read into multiple buffers
    { 20, "writev" },               // Write from multiple buffers
    { 21, "access" },               // Check file existence (suspect, targetProc0)
    { 22, "pipe" },                 // Create pipe
    { 23, "select" },               // Synchronous I/O multiplexing
    { 24, "sched_yield" },          // Yield CPU
    { 25, "mremap" },               // Remap memory
    { 26, "msync" },                // Synchronize memory with file
    { 27, "mincore" },              // Check memory residency
    { 28, "madvise" },              // Memory advice
    { 29, "shmget" },               // Get shared memory
    { 30, "shmat" },                // Attach shared memory
    { 31, "shmctl" },               // Shared memory control
    { 32, "dup" },                  // Duplicate fd
    { 33, "dup2" },                 // Duplicate fd to specific number
    { 34, "pause" },                // Suspend process
    { 35, "nanosleep" },            // Sleep (targetProc0)
    { 36, "getitimer" },            // Get timer
    { 37, "alarm" },                // Set alarm
    { 38, "setitimer" },            // Set timer
    { 39, "getpid" },               // Get process ID (targetProc0)
    { 40, "sendfile" },             // Transfer data between fds
    { 41, "socket" },               // Create socket (targetProc2)
    { 42, "connect" },              // Connect to socket (targetProc2)
    { 43, "accept" },               // Accept connection
    { 44, "sendto" },               // Send message
    { 45, "recvfrom" },             // Receive message
    { 46, "sendmsg" },              // Send message on socket
    { 47, "recvmsg" },              // Receive message on socket
    { 48, "shutdown" },             // Shut down socket
    { 49, "bind" },                 // Bind socket
    { 50, "listen" },               // Listen for connections
    { 51, "getsockname" },          // Get socket name
    { 52, "getpeername" },          // Get peer name
    { 53, "socketpair" },           // Create socket pair
    { 54, "setsockopt" },           // Set socket options
    { 55, "getsockopt" },           // Get socket options
    { 56, "clone" },                // Create thread/process
    { 57, "fork" },                 // Create child process
    { 58, "vfork" },                // Create child (shared memory)
    { 59, "execve" },               // Execute program
    { 60, "exit" },                 // Terminate process
    { 61, "wait4" },                // Wait for process
    { 62, "kill" },                 // Send signal (suspicious)
    { 63, "uname" },                // System information
    { 64, "semget" },               // Get semaphore
    { 65, "semop" },                // Semaphore operations
    { 66, "semctl" },               // Semaphore control
    { 67, "shmdt" },                // Detach shared memory
    { 68, "msgget" },               // Get message queue
    { 69, "msgsnd" },               // Send message
    { 70, "msgrcv" },               // Receive message
    { 71, "msgctl" },               // Message queue control
    { 72, "fcntl" },                // File control
    { 73, "flock" },                // File locking
    { 74, "fsync" },                // Synchronize file
    { 75, "fdatasync" },            // Synchronize file data
    { 76, "truncate" },             // Truncate file
    { 77, "ftruncate" },            // Truncate file by fd
    { 78, "getdents" },             // Get directory entries
    { 79, "getcwd" },               // Get current directory
    { 80, "chdir" },                // Change directory
    { 81, "fchdir" },               // Change directory by fd
    { 82, "rename" },               // Rename file
    { 83, "mkdir" },                // Create directory
    { 84, "rmdir" },                // Remove directory
    { 85, "creat" },                // Create file
    { 86, "link" },                 // Create hard link
    { 87, "unlink" },               // Delete file (targetProc2)
    { 88, "symlink" },              // Create symbolic link
    { 89, "readlink" },             // Read symbolic link
    { 90, "chmod" },                // Change file mode (suspicious)
    { 91, "fchmod" },               // Change file mode by fd
    { 92, "chown" },                // Change file owner (suspicious)
    { 93, "fchown" },               // Change file owner by fd
    { 94, "fchownat" },             // Change owner relative to dir
    { 95, "fchmodat" },             // Change mode relative to dir
    { 96, "umask" },                // Set file mode creation mask
    { 97, "gettimeofday" },         // Get time
    { 98, "getrlimit" },            // Get resource limits
    { 99, "getrusage" },            // Get resource usage
    { 100, "sysinfo" },             // System information
    { 101, "times" },               // Process times
    { 102, "getuid" },              // Get user ID
    { 103, "syslog" },              // System logging
    { 104, "setuid" },              // Set user ID (suspicious)
    { 105, "getgid" },              // Get group ID
    { 106, "setgid" },              // Set group ID
    { 107, "getppid" },             // Get parent PID
    { 108, "getpgrp" },             // Get process group
    { 109, "setsid" },              // Create session
    { 110, "gettid" },              // Get thread ID
    { 111, "setreuid" },            // Set real/effective UID
    { 112, "setregid" },            // Set real/effective GID
    { 113, "getgroups" },           // Get supplementary groups
    { 114, "setgroups" },           // Set supplementary groups
    { 115, "setresuid" },           // Set real/effective/saved UID
    { 116, "setresgid" },           // Set real/effective/saved GID
    { 117, "prctl" },               // Process control (suspicious)
    { 118, "capget" },              // Get capabilities
    { 119, "capset" },              // Set capabilities
    { 120, "sigaltstack" },         // Set alternate signal stack
    { 121, "getpriority" },         // Get process priority
    { 122, "setpriority" },         // Set process priority
    { 123, "sched_setparam" },      // Set scheduling parameters
    { 124, "sched_getparam" },      // Get scheduling parameters
    { 125, "sched_setscheduler" },  // Set scheduler
    { 126, "sched_getscheduler" },  // Get scheduler
    { 127, "sched_get_priority_max" }, // Get max priority
    { 128, "sched_get_priority_min" }, // Get min priority
    { 129, "sched_rr_get_interval" }, // Get round-robin interval
    { 130, "mlock" },               // Lock memory
    { 131, "munlock" },             // Unlock memory
    { 132, "mlockall" },            // Lock all memory
    { 133, "munlockall" },          // Unlock all memory
    { 134, "vhangup" },             // Hang up terminal
    { 135, "modify_ldt" },          // Modify local descriptor table
    { 136, "pivot_root" },          // Change root filesystem
    { 137, "prlimit64" },           // Set/get resource limits
    { 138, "adjtimex" },            // Adjust system clock
    { 139, "setrlimit" },           // Set resource limits
    { 140, "chroot" },              // Change root directory
    { 141, "sync" },                // Synchronize filesystems
    { 142, "acct" },                // Enable/disable accounting
    { 143, "settimeofday" },        // Set time
    { 144, "mount" },               // Mount filesystem
    { 145, "umount2" },             // Unmount filesystem
    { 146, "swapon" },              // Enable swap
    { 147, "swapoff" },             // Disable swap
    { 148, "reboot" },              // Reboot system
    { 149, "sethostname" },         // Set hostname
    { 150, "setdomainname" },       // Set domain name
    { 151, "iopl" },                // Set I/O privilege level
    { 152, "ioperm" },              // Set I/O port permissions
    { 153, "create_module" },       // Create kernel module
    { 154, "init_module" },         // Initialize kernel module
    { 155, "delete_module" },       // Delete kernel module
    { 156, "get_kernel_syms" },     // Get kernel symbols
    { 157, "query_module" },        // Query kernel module
    { 158, "quotactl" },            // Quota control
    { 159, "nfsservctl" },          // NFS control
    { 160, "getpmsg" },             // Get protocol message
    { 161, "putpmsg" },             // Put protocol message
    { 162, "afs_syscall" },         // AFS syscall
    { 163, "tuxcall" },             // TUX syscall
    { 164, "security" },            // Security syscall
    { 165, "gettid" },              // Get thread ID
    { 166, "readahead" },           // Preload file data
    { 167, "setxattr" },            // Set extended attribute
    { 168, "lsetxattr" },           // Set extended attribute for link
    { 169, "fsetxattr" },           // Set extended attribute by fd
    { 170, "getxattr" },            // Get extended attribute
    { 171, "lgetxattr" },           // Get extended attribute for link
    { 172, "fgetxattr" },           // Get extended attribute by fd
    { 173, "listxattr" },           // List extended attributes
    { 174, "llistxattr" },          // List extended attributes for link
    { 175, "flistxattr" },          // List extended attributes by fd
    { 176, "removexattr" },         // Remove extended attribute
    { 177, "lremovexattr" },        // Remove extended attribute for link
    { 178, "fremovexattr" },        // Remove extended attribute by fd
    { 179, "tkill" },               // Send signal to thread
    { 180, "time" },                // Get time (targetProc0)
    { 181, "futex" },               // Fast user-space locking
    { 182, "sched_setaffinity" },   // Set CPU affinity
    { 183, "sched_getaffinity" },   // Get CPU affinity
    { 184, "set_thread_area" },     // Set thread-local storage
    { 185, "io_setup" },            // Setup I/O context
    { 186, "io_destroy" },          // Destroy I/O context
    { 187, "io_getevents" },        // Get I/O events
    { 188, "io_submit" },           // Submit I/O operations
    { 189, "io_cancel" },           // Cancel I/O operations
    { 190, "get_thread_area" },     // Get thread-local storage
    { 191, "lookup_dcookie" },      // Lookup directory cookie
    { 192, "epoll_create" },        // Create epoll instance
    { 193, "epoll_ctl_old" },       // Control epoll (deprecated)
    { 194, "epoll_wait_old" },      // Wait epoll (deprecated)
    { 195, "remap_file_pages" },    // Remap file pages
    { 196, "getdents64" },         // Get directory entries
    { 197, "set_tid_address" },     // Set TID address
    { 198, "restart_syscall" },     // Restart syscall
    { 199, "semtimedop" },          // Timed semaphore operations
    { 200, "fadvise64" },           // File advice
    { 201, "timer_create" },        // Create timer
    { 202, "timer_settime" },       // Set timer
    { 203, "timer_gettime" },       // Get timer
    { 204, "timer_getoverrun" },    // Get timer overrun
    { 205, "timer_delete" },        // Delete timer
    { 206, "clock_settime" },       // Set clock
    { 207, "clock_gettime" },       // Get clock
    { 208, "clock_getres" },        // Get clock resolution
    { 209, "clock_nanosleep" },     // High-res sleep
    { 210, "exit_group" },          // Exit all threads (targetProc0)
    { 211, "epoll_wait" },          // Wait epoll
    { 212, "epoll_ctl" },           // Control epoll
    { 213, "tgkill" },              // Send signal to thread group
    { 214, "utimes" },              // Set file times
    { 215, "vserver" },             // Vserver syscall
    { 216, "mbind" },               // Set memory policy
    { 217, "set_mempolicy" },       // Set memory policy
    { 218, "get_mempolicy" },       // Get memory policy
    { 219, "mq_open" },             // Open message queue
    { 220, "mq_unlink" },           // Remove message queue
    { 221, "mq_timedsend" },        // Send timed message
    { 222, "mq_timedreceive" },     // Receive timed message
    { 223, "mq_notify" },           // Notify message queue
    { 224, "mq_getsetattr" },       // Get/set message queue attributes
    { 225, "kexec_load" },          // Load kernel image
    { 226, "waitid" },              // Wait for process
    { 227, "add_key" },             // Add key to keyring
    { 228, "request_key" },         // Request key
    { 229, "keyctl" },              // Key control
    { 230, "ioprio_set" },          // Set I/O priority
    { 231, "ioprio_get" },          // Get I/O priority
    { 232, "inotify_init" },        // Initialize inotify
    { 233, "inotify_add_watch" },   // Add inotify watch
    { 234, "inotify_rm_watch" },    // Remove inotify watch
    { 235, "migrate_pages" },       // Migrate memory pages
    { 236, "openat" },              // Open file relative to dir (targetProc0)
    { 237, "mkdirat" },             // Create directory relative to dir
    { 238, "mknodat" },             // Create node relative to dir
    { 239, "fchownat" },            // Change owner relative to dir
    { 240, "futimesat" },           // Set file times relative to dir
    { 241, "newfstatat" },          // File status relative to dir
    { 242, "unlinkat" },            // Delete file relative to dir
    { 243, "renameat" },            // Rename file relative to dir
    { 244, "linkat" },              // Create hard link relative to dir
    { 245, "symlinkat" },           // Create symbolic link relative to dir
    { 246, "readlinkat" },          // Read symbolic link relative to dir
    { 247, "fchmodat" },            // Change mode relative to dir
    { 248, "faccessat" },           // Check access relative to dir
    { 249, "pselect6" },            // Synchronous I/O multiplexing
    { 250, "ppoll" },               // Poll with timeout
    { 251, "unshare" },             // Unshare namespace
    { 252, "set_robust_list" },     // Set robust futex list
    { 253, "get_robust_list" },     // Get robust futex list
    { 254, "splice" },              // Splice data between pipes
    { 255, "tee" },                 // Duplicate pipe content
    { 256, "sync_file_range" },     // Sync file range
    { 257, "vmsplice" },            // Splice user pages to pipe
    { 258, "move_pages" },          // Move memory pages
    { 259, "utimensat" },           // Set file times relative to dir
    { 260, "epoll_pwait" },         // Wait epoll with signal mask
    { 261, "signalfd" },            // Create signal fd
    { 262, "timerfd_create" },      // Create timer fd
    { 263, "eventfd" },             // Create event fd
    { 264, "fallocate" },           // Allocate file space
    { 265, "timerfd_settime" },     // Set timer fd
    { 266, "timerfd_gettime" },     // Get timer fd
    { 267, "accept4" },             // Accept connection with flags
    { 268, "signalfd4" },           // Create signal fd with flags
    { 269, "eventfd2" },            // Create event fd with flags
    { 270, "epoll_create1" },       // Create epoll instance with flags
    { 271, "dup3" },                // Duplicate fd with flags
    { 272, "pipe2" },               // Create pipe with flags
    { 273, "inotify_init1" },       // Initialize inotify with flags
    { 274, "preadv" },              // Read into multiple buffers at offset
    { 275, "pwritev" },             // Write from multiple buffers at offset
    { 276, "rt_tgsigqueueinfo" },   // Send signal with info
    { 277, "perf_event_open" },     // Open performance event
    { 278, "recvmmsg" },            // Receive multiple messages
    { 279, "fanotify_init" },       // Initialize fanotify
    { 280, "fanotify_mark" },       // Mark fanotify
    { 281, "prlimit64" },           // Set/get resource limits
    { 282, "name_to_handle_at" },   // Get file handle
    { 283, "open_by_handle_at" },   // Open file by handle
    { 284, "clock_adjtime" },       // Adjust clock
    { 285, "syncfs" },              // Synchronize filesystem
    { 286, "sendmmsg" },            // Send multiple messages
    { 287, "setns" },               // Set namespace
    { 288, "getcpu" },              // Get CPU and node
    { 289, "process_vm_readv" },    // Read process memory
    { 290, "process_vm_writev" },   // Write process memory
    { 291, "kcmp" },                // Compare processes
    { 292, "finit_module" },        // Initialize kernel module
    { 293, "sched_setattr" },       // Set scheduling attributes
    { 294, "sched_getattr" },       // Get scheduling attributes
    { 295, "renameat2" },           // Rename file with flags
    { 296, "seccomp" },             // Security computing mode (suspicious)
    { 297, "getrandom" },           // Get random bytes (targetProc0, rand())
    { 298, "memfd_create" },        // Create memory fd
    { 299, "kexec_file_load" },     // Load kernel image by file
    { 300, "bpf" },                 // BPF program control
    { 301, "execveat" },            // Execute program relative to dir
    { 302, "userfaultfd" },         // User fault fd
    { 303, "membarrier" },          // Memory barrier
    { 304, "mlock2" },              // Lock memory with flags
    { 305, "copy_file_range" },     // Copy file range
    { 306, "preadv2" },             // Read into multiple buffers with flags
    { 307, "pwritev2" },            // Write from multiple buffers with flags
    { 308, "pkey_mprotect" },       // Protect memory with key
    { 309, "pkey_alloc" },          // Allocate protection key
    { 310, "pkey_free" },           // Free protection key
    { 311, "statx" },               // Extended file status
    { 312, "io_pgetevents" },       // Get I/O events
    { 313, "rseq" },                // Restartable sequences
    { 314, "pidfd_send_signal" },   // Send signal via pidfd
    { 315, "pidfd_open" },          // Open pidfd
    { 316, "pidfd_getfd" },         // Get fd via pidfd
    { 317, "openat2" },             // Open file with flags
    { 318, "epoll_pwait2" },        // Wait epoll with timeout
    { 319, "mount_setattr" },       // Set mount attributes
    { 320, "quotactl_fd" },         // Quota control by fd
    { 321, "landlock_create_ruleset" }, // Create Landlock ruleset
    { 322, "landlock_add_rule" },   // Add Landlock rule
    { 323, "landlock_restrict_self" }, // Restrict self with Landlock
    { 324, "memfd_secret" },        // Create secret memory fd
    { 325, "process_mrelease" },    // Release process memory
    { 326, "futex_waitv" },         // Wait on multiple futexes
    { 327, "set_mempolicy_home_node" }, // Set memory policy home node
    { 328, "cachestat" },           // Cache statistics
    { 329, "fchmodat2" },           // Change mode with flags
    { 330, "map_shadow_stack" },    // Map shadow stack
    { 331, "futex_wake" },          // Wake futex
    { 332, "futex_wait" },          // Wait futex
    { 333, "futex_requeue" },       // Requeue futex
    { 334, "statmount" },           // Mount statistics
    { 335, "listmount" },           // List mounts
    { 336, "lsm_get_self_attr" },   // Get LSM attributes
    { 337, "lsm_set_self_attr" },   // Set LSM attributes
    { 338, "lsm_list_modules" },    // List LSM modules
    // Higher syscalls (up to ~425, modern kernels)
    { 400, "clock_gettime64" },     // 64-bit clock time
    { 401, "clock_settime64" },     // 64-bit clock set
    { 402, "clock_adjtime64" },     // 64-bit clock adjust
    { 403, "clock_getres64" },      // 64-bit clock resolution
    { 404, "clock_nanosleep64" },   // 64-bit nanosleep
    { 405, "timer_gettime64" },     // 64-bit timer get
    { 406, "timer_settime64" },     // 64-bit timer set
    { 407, "timerfd_gettime64" },   // 64-bit timerfd get
    { 408, "timerfd_settime64" },   // 64-bit timerfd set
    { 409, "semtimedop_time64" },   // 64-bit timed semaphore
    { 410, "pselect6_time64" },     // 64-bit pselect
    { 411, "ppoll_time64" },        // 64-bit ppoll
    { 412, "io_pgetevents_time64" }, // 64-bit I/O events
    { 413, "recvmmsg_time64" },     // 64-bit receive multiple
    { 414, "mq_timedsend_time64" }, // 64-bit timed send
    { 415, "mq_timedreceive_time64" }, // 64-bit timed receive
    { 416, "semtimedop_time64" },   // 64-bit timed semaphore (alias)
    { 417, "rt_sigtimedwait_time64" }, // 64-bit timed sigwait
    { 418, "futex_time64" },        // 64-bit futex
    { 419, "sched_rr_get_interval_time64" }, // 64-bit round-robin interval
    { 420, "pidfd_send_signal" },   // Send signal via pidfd
    { 421, "io_uring_setup" },      // Setup I/O uring
    { 422, "io_uring_enter" },      // Enter I/O uring
    { 423, "io_uring_register" },   // Register I/O uring
    { 424, "open_tree" },           // Open filesystem tree
    { 425, "move_mount" },          // Move mount
    // Sentinel
    { -1, NULL }
};

const char *get_syscall_name(long syscall_num) 
{
    for (int i = 0; syscall_table[i].num != -1; i++) 
    {
        if (syscall_table[i].num == syscall_num) 
        {
            return syscall_table[i].name;
        }
    }
    return "unknown";
}