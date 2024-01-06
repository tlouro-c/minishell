CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
NAME = libft.a

# Colors
RED=\033[0;31m
BOLD_LIGHT_GREEN=\033[1;32m
YELLOW=\033[0;33m
BLUE=\033[1;34m
RESET=\033[0m

# Directories
INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

# Recursively find all .c files in SRC_DIR and its subdirectories
SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD_LIGHT_GREEN)--> Compiling libft <--$(RESET)"
	@ar -rcs $@ $^
	@echo "$(BOLD_LIGHT_GREEN)=== libft Compiled ===$(RESET)"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)=== Cleaning libft ===$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)=== Removed libft ===$(RESET)"

re: fclean all

.PHONY: all clean fclean re
