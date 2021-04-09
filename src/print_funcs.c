/*
** EPITECH PROJECT, 2020
** PSU, instr
** File description:
** src
*/

#include <errno.h>
#include "../include/strace.h"

static void	print_char(char c)
{
    if (((c > 32 && c < 127) || c == ' ') && c != '\0')
        printf("%c", c);
    else if (c != '\n' && c != '\0')
        printf("\\%o", c);
}

void p_str(unsigned long long reg, tools_t pr_tool)
{
    int	i;
    long	c;
    if (!pr_tool.s_f) {
        if (reg)
            printf("%p", reg);
        else
            printf("0x0");
        return;
    }
    printf("\"");
    i = 0;
    c = -1;
    while ((char)c != '\0' && i < 42)
    {
        if ((c = ptrace(PTRACE_PEEKDATA, pr_tool.pid,
                        reg, NULL)) == -1)
        {
            printf("ptrace PTRACE_PEEK_DATA error: ");
            printf("%s\"", strerror(errno));
            return ;
        }
        print_char(c);
        ++reg;
        ++i;
    }
    printf("\"");
}

void p_str2d(unsigned long long reg, tools_t pr_tool)
{
    unsigned long long	str;
    int			i;

    if (!pr_tool.s_f) {
        if (reg)
            printf("%p", reg);
        else
            printf("0x0");
        return;
    }
    printf("[");
    i = 0;
    str = (long long)-1;
    while ((void *)str != NULL && i < 6)
    {
        if ((str = ptrace(PTRACE_PEEKDATA, pr_tool.pid,
                          reg, NULL)) == (long)-1)
        {
            printf("ptrace PTRACE_PEEK_DATA error: ");
            printf("%s", strerror(errno));
            return ;
        }
        if (str)
            p_str(str, pr_tool);
        reg += sizeof(char *);
        ++i;
    }
    printf("]");
    if (i >= 6)
        printf(" ... ");
}

void p_unimplemented(unsigned long long reg, tools_t pr_tools)
{
    (void)reg;
    printf("unimplemented");
}

void p_nix(unsigned long long reg, tools_t pr_tools)
{
    (void)reg;
}

void p_int(unsigned long long reg, tools_t pr_tools)
{
    if (pr_tools.s_f)
        printf("%d", (int)reg);
    else {
        if ((int)reg == 0)
            printf("0x0");
        else
            printf("%p", (int)reg);
    }
}

void p_long(unsigned long long reg, tools_t pr_tools)
{
    if (pr_tools.s_f)
        printf("%ld", (long)reg);
    else {
        if (!(long)reg)
            printf("0x0");
        else
            printf("%p", (long) reg);
    }

}

void p_uint(unsigned long long reg, tools_t pr_tools)
{
    if (pr_tools.s_f)
        printf("%u", (unsigned int)reg);
    else {
        if ((unsigned int) reg == 0)
            printf("0x0");
        else
            printf("%p", (unsigned int) reg);
    }
}

void p_ulong(unsigned long long reg, tools_t pr_tools)
{
    if (pr_tools.s_f)
        printf("%lu", (unsigned long)reg);
    else {
        if (!(unsigned long) reg)
            printf("0x0");
        else
            printf("%p", (unsigned long) reg);
    }
}

void	p_pointer(unsigned long long reg, tools_t pr_tools)
{
    if (reg == 0) {
        if (pr_tools.s_f)
            printf("NULL");
        else
            printf("0x0");
    }
    else
        printf("%p", (void*)reg);
}
