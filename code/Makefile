NAME = woody_woodpacker
TEST = sample
SRCS = main.c srcs/utils.c
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.c=.o)

all : $(NAME)

test : $(TEST)

$(TEST) : write_file.o
	gcc $(CFLAGS) write_file.c -o $(TEST)

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
