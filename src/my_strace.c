/*
** EPITECH PROJECT, 2020
** PSU, instr
** File description:
** src
*/

#include "../include/strace.h"
#include "../include/syscall.h"

int do_trace(int pid, int s_f, char **av)
{
    int status;
    USR u_in;
    struct rusage r_us;
    int loop = 0;
    while (loop == 0) {
        ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
        if (WEXITSTATUS(status) == 84)
            return (84);
        if (WIFSTOPPED(status))
            if_call(pid, &u_in, s_f, av[0]);
        if (WIFEXITED(status))
            loop = 1;
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        wait4(pid, &status, 0, &r_us);
    }
    ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
    if (s_f)
        printf("%s(0) = ?\n", table[u_in.rax].name);
    else
        printf("%s(0x0) = ?\n", table[u_in.rax].name);
    printf("+++ exited with %d +++\n", WEXITSTATUS(status));
    return (0);
}

void if_call(int pid, USR *regs, int s_f, char *path)
{
    (void)path;
    tools_t pr_tools;
    pr_tools.pid = pid;
    pr_tools.s_f = s_f;
    if ((int)regs->orig_rax != -1) {
        printf("%s", table[regs->orig_rax].name);
        pr_tools.call_nb = (unsigned int)regs->orig_rax;
        if (regs->orig_rax == 59) {
            printf("(\"%s\")", path);
        } else
            p_args(regs, pr_tools);
        p_retcode(regs, s_f, pr_tools);
    }
}

int my_strace(int ac, char **av, char **envp, int s_f)
{
    pid_t pid;
    int ret;

    pid = fork();
    if (pid == -1) {
        exit (84);
    }
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        ret = execve(av[0], av, envp);
        if (ret == -1) {
            perror("execve: ");
            exit (84);
        }
    } else {
        return do_trace(pid, s_f, av);
    }
    return (0);
}