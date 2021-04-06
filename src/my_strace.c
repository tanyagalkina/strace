/*
** EPITECH PROJECT, 2020
** PSU, instr
** File description:
** src
*/

#include "../include/strace.h"
#include "../include/syscall.h"

int do_trace(int pid)
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
                if_call(pid, &u_in, 0, "tanya");
            if (WIFEXITED(status))
                loop = 1;
            ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
            wait4(pid, &status, 0, &r_us);
        }
        ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
        printf("%s = %c\n", table[u_in.rax].name, '?');
        dprintf(2, "+++ exited with %d +++\n", WEXITSTATUS(status));
        return (0);
}

void if_call(int pid, USR *regs, int is_s, char *path)
{
    (void)is_s;
    (void)path;
    long long data = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);
    //if (data == 0x0F05)
    unsigned char numb = (unsigned)0xFF & data;
    unsigned char op = ((unsigned)0xFF00 & data) >> 8;
    //if (numb == 0x00F && op == 0x05)
        //printf("the next will be a syscall\n");
        //printf("this is the num of the next op %d\n", op);
    if (regs->orig_rax != -1) {
        printf("%s", table[regs->orig_rax].name);
        if (regs->rax == 60 || regs->rax == 231)
            printf("?\n");
        else
            printf(" = 0x%llx\n", regs->rax);
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
        return do_trace(pid);
    }
    return (0);
}