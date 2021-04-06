/*
** EPITECH PROJECT, 2020
** PSU, instr
** File description:
** src
*/

#include "../include/strace.h"
#include "../include/syscall.h"

static void	catch_syscall(int pid, struct user_regs_struct *regs,
                             int is_s, char *file_name)
{
    long long data = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);
    //if (data == 0x0F05)
    unsigned char numb = (unsigned)0xFF & data;
    unsigned char op = ((unsigned)0xFF00 & data) >> 8;
    //if (numb == 0x00F && op == 0x05)
        //printf("the next will be a syscall\n");
        //printf("this is the num of the next op %d\n", op);
    if (regs->orig_rax != -1) {
        printf("syscall %lld = 0x%llx\n", regs->orig_rax, regs->rax);
        //printf("this is data:%llu", data);
    }
}

int my_strace(int ac, char **av, char **envp, int s_f)
{
    pid_t pid;
    int status;
    int ret;
    struct user_regs_struct u_in;
    struct rusage r_us;

    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        //kill(getpid(), SIGSTOP);
        ret = execve(av[0], av, envp);
        if (ret == -1)
            perror("execve: ");
    } else {
        int loop = 0;
        siginfo_t sigget;
        //for the first stop because of execve
        wait4(pid, &status, 0, &r_us);
        while (loop == 0) {
            ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
            ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
            wait4(pid, &status, 0, &r_us);
            if (WEXITSTATUS(status) == 84)
                return (84);
            if (WIFSTOPPED(status))
                catch_syscall(pid, &u_in, 0, "tanya");
            if (WIFEXITED(status))
                loop = 1;
        }
        ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
        printf("syscall %lld = %lld\n", u_in.rax, 999);
        dprintf(2, "+++ exited with %d +++\n", WEXITSTATUS(status));

        return (0);
    }
    return (0);
}