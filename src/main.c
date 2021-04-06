/*
** EPITECH PROJECT, 2020
** PSU_instr,
** File description:
** call trace
*/

#include <sys/stat.h>
#include "../include/strace.h"

static char **get_args(int ac, int *s_f, char **av)
{
    if (ac > 2 && !strcmp(av[1], "-s")) {
        *s_f = 1;
    }
    return ((char **)&av[1 + *s_f]);
    //return av + *s_f;


}

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
    if (atoi(av2) <= 0 || strlen(av2) != (size_t)num_length) {
        fprintf(stderr, "strace: Invalid process id: '%s'\n", av2);
        exit (84);
    }
    return (1);
}

static bool file_exists(char *path)
{
    struct stat buffer;

    return (stat (path, &buffer) == 0);
}

int main(int ac, char *av[], char **envp)
{
    int s_f = 0;
    char **args;
    if (ac < 2) {
        fprintf(stderr, "strace: must have PROG [ARGS] or -p PID\n");
        fprintf(stderr, "Try 'strace --h' for more information.\n");
        return (84);
    }
    if (ac == 2 && !strcmp(av[1], "--h"))
        print_help();
    if (ac == 3 && !strcmp((av[1]), "-p") && is_pos_int(av[2]))
        p_flag_loop(atoi(av[2]));
    args = get_args(ac, &s_f, av);
    if (!file_exists(args[0])) {
        fprintf(stderr, "strace: Cant stat '%s': No such file or directory\n", args[0]);
        return (84);
    }
    return my_strace(ac, args, envp, s_f);
}
	
	
