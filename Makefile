##
## EPITECH PROJECT, 2020
## nm_objdump
## File description:
## Makefile
##

CC	= gcc

RM	= rm -f

NAME	= strace

SRCS	=	./src/main.c 		\
		./src/p_flag_loop.c	\
		./src/my_strace.c


OBJS	= $(SRCS:.c=.o)

CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS)


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ./strace
:
re: fclean all

.PHONY: all strace clean fclean re
