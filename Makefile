NAME		= pipex
NAME_B		= pipex_bonus

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -Ilibft

# Libft directory and sources
LIBFT_DIR	= libft
LIBFT_OBJ_DIR = $(LIBFT_DIR)/obj
LIBFT_SRCS	= ft_abs.c ft_atoi.c ft_bzero.c ft_calloc.c \
			  ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
			  ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			  ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c \
			  ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c ft_putchar_fd.c ft_putendl_fd.c \
			  ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c \
			  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
			  ft_strncpy.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
			  ft_toupper.c process_c.c process_id.c process_p.c process_s.c process_u.c \
			  process_x.c process_xx.c ft_free_split.c get_next_line.c openfd.c

LIBFT_OBJS = $(addprefix $(LIBFT_OBJ_DIR)/, $(LIBFT_SRCS:.c=.o))

# Source files
SRCS_MAIN	= pipex.c pipex_utils.c
SRCS_BONUS	= pipex_bonus.c pipex_utils_bonus.c

OBJ_DIR		= obj
OBJS_MAIN	= $(addprefix $(OBJ_DIR)/, $(SRCS_MAIN:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

# Default target
all: $(NAME) $(NAME_B)

# Build main program
$(NAME): $(OBJS_MAIN) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_MAIN) $(LIBFT_OBJS)

# Build bonus program
$(NAME_B): $(OBJS_BONUS) $(LIBFT_OBJS)
	$(CC) $(CFLAGS) -o $(NAME_B) $(OBJS_BONUS) $(LIBFT_OBJS)

# Compile pipex and bonus sources
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile libft sources
$(LIBFT_OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c | $(LIBFT_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create object directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_OBJ_DIR):
	mkdir -p $(LIBFT_OBJ_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBFT_OBJ_DIR)

# Remove executables and object files
fclean: clean
	rm -f $(NAME) $(NAME_B)

# Rebuild everything
re: fclean all

#Bonus-only build
bonus: $(NAME_B)

.PHONY: all clean fclean re bonus
