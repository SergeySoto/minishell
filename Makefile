NAME = minishell

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline
INCLUDES = -I./includes -I./libft
LIBS = -L./libft -lft -lreadline

# DIRECTORIES
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/lexer/tokenizer.c \
	$(SRC_DIR)/parser/parser.c \
	$(SRC_DIR)/executor/executor.c \
	$(SRC_DIR)/builtins/echo.c \

# ARCHIVOS OBJETO
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# REGLA PRINCIPAL
all: $(NAME)

# COMPILAR LIBFT PRIMERO
$(LIBFT):
	@echo -e "$(GREEN)Compilando libft...$(RESET)"
	@make -C $(LIBFT_DIR)

# CREAR DIRECTORIOS DE OBJETOS
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo -e "$(GREEN)Compilado: $<$(RESET)"

# CREAR EL EJECUTABLE
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo -e "$(GREEN)✓ Minishell compilado exitosamente$(RESET)"

# LIMPIAR OBJETOS
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo -e "$(RED)Objetos eliminados$(RESET)"

# LIMPIAR TODO
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo -e "$(RED)Ejecutable eliminado$(RESET)"

# RECOMPILAR TODO
re: fclean all

# PHONY RULES
.PHONY: all clean fclean re