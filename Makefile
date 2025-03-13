NAME 		= minishell

CC 			= gcc -g
CFLAGS 		= -Wall -Wextra -Werror
RM 			= rm -f
PRINTF 		= printf

SRC_DIR 	= srcs
OBJ_DIR 	= obj
LIBFT_DIR 	= libft

LIBFT 		= $(LIBFT_DIR)/libft.a

SRC 		= $(wildcard $(SRC_DIR)/builtin/*.c) \
			$(wildcard $(SRC_DIR)/core/*.c) \
			$(wildcard $(SRC_DIR)/env/*.c) \
			$(wildcard $(SRC_DIR)/exec/*.c) \
			$(wildcard $(SRC_DIR)/free/*.c) \
			$(wildcard $(SRC_DIR)/gnl/*.c) \
			$(wildcard $(SRC_DIR)/lexer/*.c) \
			$(wildcard $(SRC_DIR)/parser/*.c) \
			$(wildcard $(SRC_DIR)/utils/*.c) \
			$(wildcard $(SRC_DIR)/*.c)

OBJ 		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

RESET 		= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA 	= \033[0;95m
CYAN 		= \033[0;96m
WHITE 		= \033[0;97m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include $(LIBFT) -lreadline -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)File '$(NAME)' has been compiled!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(PRINTF) "\r%100s\rCompiling $(BLUE)$<$(RESET)..."
	@$(CC) -I ~/readline/include $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)All object files were removed from MINISHELL$(RESET)"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(MAGENTA)Removed everything from MINISHELL$(RESET)"

re: fclean all

.PHONY: all clean fclean re
