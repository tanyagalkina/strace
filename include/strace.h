/*
** EPITECH PROJECT, 2020
** strace
** File description:
** header
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <libelf.h>
#include <stdbool.h>
#include <fcntl.h>
#include <wait.h>
#include <syscall.h>
#include <unistd.h>
#include <string.h>
#define SC_NUMBER  (8 * ORIG_RAX)
#define SC_RETCODE (8 * RAX)
#define USR struct user_regs_struct

int p_flag_loop(int pid);
int my_strace(int ac, char **av, char **envp, int s_f);
void if_call(int pid, USR *regs, int is_s, char *file_name);
int do_trace(int pid);