NAME = pipex
NAME_BONUS = pipex_bonus

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

PIPEX_LIB = ./inc/pipex.a
PIPEX_BONUS_LIB = ./inc/pipex_bonus.a

SRCS = $(wildcard src/pipex*.c)
SRCS_BONUS = $(wildcard src_bonus/pipex*bonus.c)

MAIN = main.c
MAIN_BONUS = main_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m


$(NAME): $(LIBFT) $(PIPEX_LIB) $(MAIN)
	@echo "$(YELLOW)Compiling ./pipex executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN) $(PIPEX_LIB) $(LIBFT)
	@echo "$(GREEN)./pipex executable created successfully.$(RESET)"

$(LIBFT): 
	@make -C $(LIBFT_DIR)

$(PIPEX_LIB): $(OBJS)
	@echo "$(YELLOW)Compiling pipex.a library...$(RESET)"
	@ar rcs $(PIPEX_LIB) $(OBJS)
	@echo "$(GREEN)pipex.a created successfully.$(RESET)"

$(PIPEX_BONUS_LIB): $(OBJS_BONUS)
	@echo "$(YELLOW)Compiling pipex_bonus.a library...$(RESET)"
	ar rcs $(PIPEX_BONUS_LIB) $(OBJS_BONUS)
	@echo "$(GREEN)pipex_bonus.a created successfully.$(RESET)"

$(NAME_BONUS): $(LIBFT) $(PIPEX_LIB) $(PIPEX_BONUS_LIB) $(MAIN_BONUS)
	@echo "$(YELLOW)Compiling ./pipex_bonus executable...$(RESET)"
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(MAIN_BONUS) $(PIPEX_LIB) $(PIPEX_BONUS_LIB) $(LIBFT)
	@echo "$(GREEN)./pipex_bonus executable created successfully.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(LIBFT) $(PIPEX_LIB) $(PIPEX_BONUS_LIB) $(NAME_BONUS)

all: $(LIBFT) $(PIPEX_LIB) $(PIPEX_BONUS_LIB) $(NAME) $(NAME_BONUS)

clean:
	@echo "$(YELLOW)Deleting all the object files...$(RESET)"
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)All the object files deleted succesfully.$(RESET)"

fclean: clean
	@echo "$(YELLOW)Deleting the object files, *.a and executable file...$(RESET)"
	@$(RM) $(PIPEX_LIB) $(PIPEX_BONUS_LIB) $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Everything deleted succesfully.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
