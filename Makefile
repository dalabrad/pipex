NAME = pipex

LIB_NAME = libft.a

LIB_SRCS_DIR = ./libft
LIB_SRCS = $(wildcard $(LIB_SRCS_DIR)/ft*.c)

MAIN = main.c

LIB_OBJS = $(LIB_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(LIB_NAME) $(NAME)

$(LIB_NAME): $(LIB_OBJS)
	ar rcs $(LIB_NAME) $(LIB_OBJS)

$(NAME): $(LIB_NAME) $(MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(LIB_NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(LIB_OBJS)

fclean: clean
	$(RM) $(LIB_NAME) $(NAME)

re: fclean all

.PHONY: all clean fclean re
