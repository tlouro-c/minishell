CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
NAME = libft.a

# Directories
INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

CYAN = \033[1;36m
UNDERLINE_CYAN = \033[4;36m
RESET = \033[0m # Reset

# Recursively find all .c files in SRC_DIR and its subdirectories
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)Building..."
	@ar -rcs $@ $^
	@echo "Library created successfully!"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "$(CYAN)Compiling $(UNDERLINE_CYAN)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(CYAN)Cleaning..."
	@rm -rf $(OBJ_DIR)
	@echo "Clean complete!"


fclean: clean
	@echo "$(CYAN)Removing \033[9m$(NAME)$(RESET)"
	@rm -f $(NAME)
	@echo "$(CYAN)Removing complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
