/*
** EPITECH PROJECT, 2020
** PSU, instr
** File description:
** src
*/

#include "../include/strace.h"

int p_flag_loop(int pid)
{
    if (getpgid(pid) < 0) {
        fprintf(stderr, "strace: attach: ptrace(PTRACE_SEIZE, %d): No such process\n", pid);
        exit (84);
    }
    if (-1 == (ptrace(PTRACE_SEIZE, pid, 0, PTRACE_O_TRACESYSGOOD))) {
        fprintf(stderr, "strace: attach: ptrace(PTRACE_SEIZE, %d): ", pid);
        perror("");
        exit (84);
    }
    while (getpgid(pid) >= 0) {
        sleep(5);
        printf("hello, I am pid_flag\n");
    }
}