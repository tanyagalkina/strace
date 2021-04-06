#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <libelf.h>
#include <stdbool.h>

#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <syscall.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#define SC_NUMBER  (8 * ORIG_RAX)
#define SC_RETCODE (8 * RAX)



int p_flag_loop(int pid);
int my_strace(int ac, char **av, char **envp, int s_f);