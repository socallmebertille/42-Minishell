NAME = libft.a

INC_DIR = includes/
OBJS_DIR = objs/

# Définir les répertoires pour chaque groupe de fichiers
CHAR_DIR = srcs/char/
CONVERT_DIR = srcs/convert/
PUT_FD_DIR = srcs/put_fd/
LIST_DIR = srcs/list/
MEMORY_DIR = srcs/memory/
STRING_DIR = srcs/string/
PRINTF_DIR = srcs/printf/
GNL_DIR = srcs/gnl/

# Définir les fichiers sources pour chaque groupe
CHAR_SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_tolower.c ft_toupper.c
CONVERT_SRCS = ft_atoi.c ft_itoa.c ft_atol.c ft_atol_under_lldmax.c
PUT_FD_SRCS = ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c
LIST_SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
MEMORY_SRCS = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c
STRING_SRCS = ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c ft_split.c ft_strcmp.c ft_free_tab.c ft_strncat.c
PRINTF_SRCS = ft_printf.c ft_print_char.c ft_putnbr_base.c
GNL_SRCS = get_next_line.c get_next_line_utils.c

# Ajouter le préfixe du répertoire à chaque fichier source
SRCS = $(addprefix $(CHAR_DIR),$(CHAR_SRCS)) \
		$(addprefix $(CONVERT_DIR),$(CONVERT_SRCS)) \
		$(addprefix $(PUT_FD_DIR),$(PUT_FD_SRCS)) \
		$(addprefix $(LIST_DIR),$(LIST_SRCS)) \
		$(addprefix $(MEMORY_DIR),$(MEMORY_SRCS)) \
		$(addprefix $(STRING_DIR),$(STRING_SRCS)) \
		$(addprefix $(PRINTF_DIR),$(PRINTF_SRCS)) \
		$(addprefix $(GNL_DIR),$(GNL_SRCS))

OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

CC = cc

CFLAGS = -Wall -Wextra -Werror -I${INC_DIR} -MMD

all: ${NAME}

${NAME}: ${OBJS}
	@ar rcs ${NAME} ${OBJS}

clean:
	@rm -rf ${OBJS_DIR}

fclean: clean
	@rm -rf ${NAME}

re: fclean ${NAME}

.PHONY: all clean fclean re

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)