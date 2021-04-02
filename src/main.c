/*
** EPITECH PROJECT, 2020
** PSU_instr,
** File description:
** call trace
*/

#include "../include/strace.h"

static void print_help()
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    exit (0);
}

static int is_pos_int(char *av2)
{
    int pid = atoi(av2);
    int num_length = 0;

    while(pid) {
        num_length++;
        pid /= 10;
    }
    if (atoi(av2) <= 0 || strlen(av2) != num_length) {
        fprintf(stderr, "strace: Invalid process id: '%s'\n", av2);
        exit (84);
    }
    return (1);
}

int main(int ac, char *av[], char **envp)
{
    if (ac < 2) {
        fprintf(stderr, "strace: must have PROG [ARGS] or -p PID\n");
        fprintf(stderr, "Try 'strace --h' for more information.\n");
        return (84);
    }
    if (ac == 2 && !strcmp(av[1], "--h"))
        print_help();
    if (ac == 3 && !strcmp((av[1]), "-p") && is_pos_int(av[2]))
        p_flag_loop(atoi(av[2]));
    my_strace(ac, av, envp);
    return (0);

	pid_t pid;
	int status;
	int ret;
	long long int syscall;
	char *arg[] = {"ls", NULL};
	struct user_regs_struct u_in;
	struct rusage r_us;
#define SC_NUMBER  (8 * ORIG_RAX)
#define SC_RETCODE (8 * RAX)

	pid = fork();
	//printf("the child#s pid is %d\n", pid);
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0) //if i am a child
	{
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		kill(getpid(), SIGSTOP);
		ret = execve(av[1], NULL, NULL);
		if (ret == -1)
			perror("execve: ");
	} else {
		int i = 0;
		while(1)
		{
			wait4(pid, &status, 0, &r_us);
			
                           if (WIFEXITED(status)) {
                               printf("Child exit with status %d\n", WEXITSTATUS(status));
                                  break;
			   }
			   if (WIFSIGNALED(status)) {
                                printf("Child exit due to signal %d\n", WTERMSIG(status));
                                 exit(0);
                          }
			   if (!WIFSTOPPED(status)) {
                                printf("wait() returned unhandled status 0x%x\n", status);
                                 exit(0);
                            }
             

			if (WSTOPSIG(status) == SIGTRAP){
				//int sc_number = ptrace(PTRACE_PEEKUSER, pid, SC_NUMBER, NULL);
				//int sc_retcode = ptrace(PTRACE_PEEKUSER, pid, SC_RETCODE, NULL);
				ptrace(PTRACE_GETREGS, pid, NULL, &u_in);
				//printf("SIGTRAP: syscall %ld, rc = %d\n", sc_number, sc_retcode);
				printf("the rax has %d\n", u_in.orig_rax);
				printf("  the ret is %d\n", u_in.rax);
				//
				}
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		      
		}
		printf("Child is finished)\n");
	}

	return (0);
}
	
	
