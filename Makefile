CC = cc
CFLAGS = -Wall -Wextra -g -Werror -I$(INCLUDE_DIR)
NAME = minishell

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft

PURPLE = \033[1;35m
CYAN = \033[1;36m
UNDERLINED_PURPLE = \033[4;35m
RESET = \033[0m

SRC_FILES = $(SRC_DIR)/built_ins/built_ins.c \
			$(SRC_DIR)/built_ins/built_ins2.c \
			$(SRC_DIR)/built_ins/built_ins_utils.c \
			$(SRC_DIR)/exits_and_errors/error_messages.c \
			$(SRC_DIR)/exits_and_errors/exit_utils.c \
			$(SRC_DIR)/exits_and_errors/exit_utils2.c \
			$(SRC_DIR)/parsing/load_commands.c \
			$(SRC_DIR)/parsing/load_commands2.c \
			$(SRC_DIR)/parsing/prepare_input.c \
			$(SRC_DIR)/parsing/pathfinder.c \
			$(SRC_DIR)/utils/manage_files.c \
			$(SRC_DIR)/utils/manage_env.c \
			$(SRC_DIR)/utils/user_interface.c \
			$(SRC_DIR)/utils/utils.c \
			$(SRC_DIR)/execution/execute.c \
			$(SRC_DIR)/execution/execute2.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/signals.c \
			$(SRC_DIR)/signals2.c

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: libft $(NAME)

libft:
	@echo "$(PURPLE)Making libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ_FILES)
	@echo "$(PURPLE)Building...$(RESET)"
	@$(CC) $^ -o $@ -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(PURPLE)$(NAME) compiled successfully.$(RESET)"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(PURPLE)Compiling $(UNDERLINED_PURPLE)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	clear
	valgrind --leak-check=full ./$(NAME)

clean:
	@echo "$(PURPLE)Cleaning up...$(RESET)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ_FILES)
	@if [ -d "$(OBJ_DIR)" ]; then rm -rf $(OBJ_DIR); fi
	@echo "$(PURPLE)Clean complete!$(RESET)"

fclean: clean
	@echo "$(PURPLE)Removing  \033[9m$(NAME)$(RESET)"
	@rm -f $(NAME)
	@echo "$(CYAN)Removing  \033[9m$(LIBFT_DIR)/libft.a$(RESET)"
	@rm -f $(LIBFT_DIR)/libft.a
	@echo "$(PURPLE)Removing complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft
