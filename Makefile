NAME = pipex

LIB_NAME = libft.a
PX_LIB_NAME = pipex.a

LIB_SRCS_DIR = ./libft
LIB_SRCS = $(wildcard $(LIB_SRCS_DIR)/ft*.c)
PX_LIB_SRCS = $(wildcard ./pipex*.c)

MAIN = main.c

LIB_OBJS = $(LIB_SRCS:.c=.o)
PX_LIB_OBJS = $(PX_LIB_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(LIB_NAME) $(PX_LIB_NAME) $(NAME)

$(LIB_NAME): $(LIB_OBJS)
	ar rcs $(LIB_NAME) $(LIB_OBJS)

$(PX_LIB_NAME): $(PX_LIB_OBJS)
	ar rcs $(PX_LIB_NAME) $(PX_LIB_OBJS)

$(NAME): $(LIB_NAME) $(PX_LIB_NAME) $(MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(LIB_NAME) $(PX_LIB_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(LIB_OBJS) $(PX_LIB_OBJS)

fclean: clean
	$(RM) $(LIB_NAME) $(PX_LIB_NAME) $(NAME)

re: fclean all

.PHONY: all clean fclean re
