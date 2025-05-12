#ifndef SYSCALLS_H
#define SYSCALLS_H


struct syscall_map 
{
    long num;           // Syscall num
    const char *name;   // Syscall name
};


extern const struct syscall_map syscall_table[];


const char *get_syscall_name(long syscall_num);

#endif