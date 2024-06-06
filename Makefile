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

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

all: $(LIBFT) $(PIPEX_LIB) $(NAME)

$(LIBFT): 
	@make -C $(LIBFT_DIR)

$(PIPEX_LIB): $(OBJS)
	@echo "$(YELLOW)Compiling pipex.a library...$(RESET)"
	@ar rcs $(PIPEX_LIB) $(OBJS)
	@echo "$(GREEN)pipex.a created successfully.$(RESET)"

$(NAME): $(LIBFT) $(PIPEX_LIB) $(MAIN)
	@echo "$(YELLOW)Compiling ./pipex executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(PIPEX_LIB) $(LIBFT)
	@echo "$(GREEN)./pipex executable created successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)All the object files deleted succesfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Deleting the object files, *.a and executable file...$(RESET)"
	@$(RM) $(PIPEX_LIB) $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Everything deleted succesfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
