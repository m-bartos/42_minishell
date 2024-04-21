# Colours
BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# readline() flag to link the library for compiler (MacOS only)
READLINE_FLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBFT_DIR = ./libft

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/**/**/*.c)
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Headers
HEADER = -I ./

# Program name
NAME = minishell

# Default rule
all: $(LIBFT) $(NAME)

# Rule to make the program
$(NAME): $(OBJS)
	@echo "$(BOLD)$(BCYAN)[ Compiling $(NAME)... ]$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft $(READLINE_FLAGS)
	@echo "$(BOLD)$(GREEN)[ $(NAME) ready! ]$(NC)"

# Generic rule for objects
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< $(HEADER) -o $@

# Libft compilation rule
$(LIBFT):
	@make -sC $(LIBFT_DIR)

# Clean rule
clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean
	@echo "$(BOLD)$(RED)[ Obj files deleted ]$(NC)"

# Full clean rule
fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@echo "$(BOLD)$(RED)[ Program deleted ]$(NC)"

# Rebuild rule
re: fclean all

.PHONY: all clean fclean re
