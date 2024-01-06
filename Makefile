CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
LIBFT = -L$(LIBFT_DIR) -lft
NAME = minishell

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBFT_DIR = ./libft

SRC_FILES =  $(SRC_DIR)/main.c \
			 $(SRC_DIR)/built_ins.c \
			 $(SRC_DIR)/built_ins2.c \
			 $(SRC_DIR)/manage_env.c \
			 $(SRC_DIR)/manage_env2.c \
			 $(SRC_DIR)/parser.c \
			 $(SRC_DIR)/parser2.c \
			 $(SRC_DIR)/parser3.c \
			 $(SRC_DIR)/exit_utils.c \
			 $(SRC_DIR)/utils.c \
			 $(SRC_DIR)/error_messages.c \
			 $(SRC_DIR)/pathfinder.c \
			 $(SRC_DIR)/execute.c \
			 $(SRC_DIR)/execute2.c \

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Colors
RED=\033[0;31m
BOLD_LIGHT_GREEN=\033[1;32m
YELLOW=\033[0;33m
BLUE=\033[1;34m
RESET=\033[0m

all: libft $(NAME)

libft:
	@echo "$(BOLD_LIGHT_GREEN)Making libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	@echo "$(BLUE)Compiling $(NAME)...$(RESET)"
	@$(CC) $^ -o $@ $(LIBFT) -lreadline
	@echo "$(BLUE)$(NAME) compiled successfully.$(RESET)"

# Make sure dir exists
$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning up...$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@if [ -d "$(OBJ_DIR)" ]; then rm -rf $(OBJ_DIR); fi

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re libft
