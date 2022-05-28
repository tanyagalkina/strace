#  STRACE
## Purpose:
It's 2nd year project of Epitech, a part of "Unix Programming Instrumentation" Module.<br/>
The goal of this project is to recode the Linux Utility "strace" https://strace.io/ in C.<br/>


## Skills to be acquired
- Discern the userland's kernel space;
- Know which information can be retrieved in a process
- Explore the system call concept in greater depth
- Learn how to plot a program's execution

### Forbidden Functions

- PTRACE_SYSCALL

#### This is Linux code
## Usage:
- To build:
```
$ make
```

```
Usage : ./strace [-s] [-p <pid>|<command>]
    -s : show arguments details
    -p : PID of the process to attach (to connect to already running process)
   
```

### Personal

After finishing this project we have a better understanding of ELF files and
reverse engineering. We understand how debuggers and disassemblers function in UNIX.

Would be nice to have better assistance in the proj, because I am very interested to
learn Unix properly.
