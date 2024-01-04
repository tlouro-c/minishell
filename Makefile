# Sample Makefile
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE_DIR)
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
			 $(SRC_DIR)/signals.c
			 $(SRC_DIR)/pathfinder.c \
			 $(SRC_DIR)/execute.c

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: libft $(NAME)

libft:
	cd $(LIBFT_DIR) && make

$(NAME): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LIBFT) -lreadline

# Make sure dir exists
$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	clear
	valgrind --leak-check=full ./$(NAME)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@if [ -d "$(OBJ_DIR)" ]; then 		rm -rf $(OBJ_DIR); 	fi

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)/libft.a

re: fclean all

.PHONY: all clean fclean re libft

