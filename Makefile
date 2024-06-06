NAME = pipex

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

PIPEX_LIB = pipex.a

SRCS = $(wildcard ./pipex*.c)

MAIN = main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(LIBFT) $(PIPEX_LIB) $(NAME)

$(LIBFT): 
	make -C $(LIBFT_DIR)
	echo libft.a created

$(PIPEX_LIB): $(OBJS)
	ar rcs $(PIPEX_LIB) $(OBJS)

$(NAME): $(LIBFT) $(PIPEX_LIB) $(MAIN)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(PIPEX_LIB) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(PIPEX_LIB) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
