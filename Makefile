NAME = minishell

# COLORS
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
BOLD = \033[1m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I. -I./includes -I./libft
LIBS = -L./libft -lft -lreadline

# DIRECTORIES
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/error.c \
	$(SRC_DIR)/token_utils.c \
				

# ARCHIVOS OBJETO
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# REGLA PRINCIPAL
all: $(NAME)

# COMPILAR LIBFT PRIMERO
$(LIBFT):
	@echo "$(YELLOW)Linking...$(RESET)"
	@make -sC $(LIBFT_DIR) --no-print-directory \
	&& echo "$(BLUE)	Libft compiled $<$(RESET)" \
	|| (echo "$(RED)	✖ Failed to compile files $<$(RESET)" && exit 1)

# CREAR DIRECTORIOS DE OBJETOS
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ \
	&& echo "$(CYAN)Compiled: $<$(RESET)" \
	|| (echo "$(RED)	✖ Failed to compile files: $<$(RESET)" && exit 1)

# CREAR EL EJECUTABLE
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo  "$(GREEN)	✓ Minishell compiled successfully!$(RESET)"

# LIMPIAR OBJETOS
clean:
	@rm -rf $(OBJ_DIR)
	@make -sC $(LIBFT_DIR) clean --no-print-directory
	@echo "$(BLUE)Objects deleted$(RESET)"

# LIMPIAR TODO
fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(BLUE)Executable deleted$(RESET)"

# RECOMPILAR TODO
re: fclean all

# PHONY RULES
.PHONY: all clean fclean re