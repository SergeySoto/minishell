# Makefile

# VARIABLES

# Name of the final library
NAME = libft.a

# Command to compile
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = \
	src/ft_isalpha.c \
      src/ft_isdigit.c \
      src/ft_isalnum.c \
      src/ft_isascii.c \
      src/ft_isprint.c \
      src/ft_strlen.c \
      src/ft_memset.c \
      src/ft_bzero.c \
      src/ft_memcpy.c \
      src/ft_memmove.c \
	src/ft_strlcpy.c \
	src/ft_strlcat.c \
	src/ft_strchr.c \
	src/ft_toupper.c \
	src/ft_tolower.c \
	src/ft_strrchr.c \
	src/ft_strncmp.c \
	src/ft_memchr.c \
	src/ft_memcmp.c \
	src/ft_strnstr.c \
	src/ft_atoi.c \
	src/ft_calloc.c \
	src/ft_strdup.c \
	src/ft_substr.c \
	src/ft_strjoin.c \
	src/ft_strtrim.c \
	src/ft_split.c \
	src/ft_itoa.c \
	src/ft_strmapi.c \
	src/ft_striteri.c \
	src/ft_putchar_fd.c \
	src/ft_putstr_fd.c \
	src/ft_putendl_fd.c \
	src/ft_putnbr_fd.c \
	src/get_next_line_utils.c \
	src/get_next_line.c \
	src/ft_printf.c \
	src/ft_printf_complements.c \


# Source bonus files
//SRC_BONUS = src/ft_lstnew.c \
//			src/ft_lstadd_front.c \
//			src/ft_lstsize.c \
//			src/ft_lstlast.c \
//			src/ft_lstadd_back.c \
//			src/ft_lstdelone.c

# Object files
OBJ = $(SRC:src/%.c=obj/%.o)

# Command to create the bonus
//OBJ_BONUS = $(SRC_BONUS:src/%.c=obj/%.o)
	
# Make libraries
AR = ar rcs

# Rule to compile all
all: $(NAME)

# Create .o files from .c 
obj/%.o: src/%.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the library
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

# Removes every object inside the directory
clean:
	rm -rf $(OBJ)

# Removes the final files made with this makefile by force, executing clean as well
fclean: clean
	rm -rf obj
	rm -f $(NAME)

# Restarts the Makefile. Erase everything and executes again
re: fclean all

.PHONY: all clean fclean re
