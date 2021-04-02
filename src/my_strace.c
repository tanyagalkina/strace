/*
** EPITECH PROJECT, 2020
** PSU, instr
** File description:
** src
*/

#include "../include/strace.h"

int my_strace(int ac, char **av, char **envp)
{
    pid_t pid;
    int status;
    int ret;
    //long long int syscall;
    //char *arg[] = {"ls", NULL};
    struct user_regs_struct u_in;
    struct rusage r_us;

    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        //kill(getpid(), SIGSTOP);
        ret = execve(av[1], NULL, NULL);
        if (ret == -1)
            perror("execve: ");
    } else {
        wait4(pid, &status, 0, &r_us);

            /*if (WIFSIGNALED(status)) {
                printf("Child exit due to signal %d\n", WTERMSIG(status));
                exit(0);
            }
            if (!WIFSTOPPED(status)) {
                printf("wait() returned unhandled status 0x%x\n", status);
                exit(0);
            }*/


            //if (WSTOPSIG(status) == SIGTRAP) {
                //int sc_number = ptrace(PTRACE_PEEKUSER, pid, SC_NUMBER, NULL);
                   //int sc_retcode = ptrace(PTRACE_PEEKUSER, pid, SC_RETCODE, NULL);
            //}
            while(WIFSTOPPED(status)) {
                ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
                   //printf("SIGTRAP: syscall %ld, rc = %d\n", sc_number, sc_retcode);
                  // system("ausyscall 5");
                if (u_in.orig_rax != -1) {
                    printf("syscall %d = ", u_in.orig_rax);
                    printf("%lld\n", u_in.rax);
                }
                status = ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
                wait4(pid, &status, 0, &r_us);
            }
            if (WIFEXITED(status)) {
                printf("+++ exited with %d +++\n", WEXITSTATUS(status));
            }
    }
    return (0);
}