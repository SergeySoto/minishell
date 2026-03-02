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
	$(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/utils/token_utils.c \
	$(SRC_DIR)/lexer/tokenizer.c \
	$(SRC_DIR)/lexer/smart_split.c \
	$(SRC_DIR)/lexer/expander.c \
	$(SRC_DIR)/lexer/expander_utils.c \
	$(SRC_DIR)/parser/parser.c \
	$(SRC_DIR)/parser/parser_utils.c \
	$(SRC_DIR)/builtins/ft_pwd.c \
	$(SRC_DIR)/builtins/ft_env.c \
	$(SRC_DIR)/builtins/ft_echo.c \
	$(SRC_DIR)/builtins/ft_export.c \
	$(SRC_DIR)/builtins/ft_unset.c \
	$(SRC_DIR)/parser/pre_pars.c \
	$(SRC_DIR)/parser/pre_pars_utils.c\
	$(SRC_DIR)/parser/envp.c\
	$(SRC_DIR)/parser/envp_utils.c\
	$(SRC_DIR)/executor/path.c\
	$(SRC_DIR)/executor/executor_main.c\
	$(SRC_DIR)/executor/handle_execution.c\
	$(SRC_DIR)/executor/handle_redirections.c\
	$(SRC_DIR)/executor/handle_single.c\
	$(SRC_DIR)/executor/handle_pipeline.c\
	$(SRC_DIR)/executor/executor_builtins.c\
	$(SRC_DIR)/signal/signal.c\
				


TOTAL_FILES := $(words $(SRC))
CURRENT_INDEX = 0

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

# MODIFICA TU REGLA DE OBJETOS (.o)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@$(eval CURRENT_INDEX=$(shell echo $$(($(CURRENT_INDEX)+1))))
	@PERCENTAGE=$$(($(CURRENT_INDEX) * 100 / $(TOTAL_FILES))); \
	printf "$(CYAN)Compiling: [%-20s] %d%% $(RESET)\r" "$$(yes '#' | head -n $$(($$PERCENTAGE / 5)) | tr -d '\n')" $$PERCENTAGE

# CREAR EL EJECUTABLE
$(NAME): $(LIBFT) $(OBJ)
	@printf "$(CYAN)Compiling: [%-20s] 100%% $(RESET)\n" "####################"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ Minishell compiled successfully!$(RESET)"

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