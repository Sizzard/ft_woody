NAME = woody_woodpacker
SRCS = main.c srcs/utils.c srcs/injection.c srcs/encrypt.c
CFLAGS = -Wall -Wextra -Werror -g
OBJDIR = objs
OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

%.o:%.c woody.h
	gcc $(CFLAGS) -c -o $@ $<

clean :
	rm -f $(OBJ) write_file.o

fclean : clean
	rm -f $(NAME) $(TEST)

re : fclean all

.PHONY: test clean fclean all re
