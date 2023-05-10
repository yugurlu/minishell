

NAME        := minishell
CC        := gcc
FLAGS    := -Wall -Wextra -Werror #-g -fsanitize=address

SRCS        :=      libft/ft_strnstr.c \
                          libft/ft_isdigit.c \
                          libft/ft_lstadd_back.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_lstnew.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strlen.c \
                          libft/ft_lstlast.c \
                          libft/ft_memcmp.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_lstclear.c \
                          libft/ft_lstiter.c \
                          libft/ft_strchr.c \
                          libft/ft_striteri.c \
                          libft/ft_bzero.c \
                          libft/ft_strjoin.c \
                          libft/ft_isascii.c \
                          libft/ft_memcpy.c \
                          libft/ft_isprint.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_lstmap.c \
                          libft/ft_lstsize.c \
                          libft/ft_toupper.c \
                          libft/ft_split.c \
                          libft/ft_lstadd_front.c \
                          libft/ft_strrchr.c \
                          libft/ft_isalpha.c \
                          libft/ft_memchr.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_memset.c \
                          libft/ft_substr.c \
                          libft/ft_strncmp.c \
                          libft/ft_strmapi.c \
                          libft/ft_strtrim.c \
                          libft/ft_memmove.c \
                          libft/ft_strlcat.c \
                          libft/ft_calloc.c \
                          libft/ft_strdup.c \
                          libft/ft_atoi.c \
                          libft/ft_isalnum.c \
                          libft/ft_lstdelone.c \
                          libft/ft_itoa.c \
                          libft/ft_tolower.c \
                          src/utils/utils2.c \
                          src/utils/utils_tokens.c \
                          src/utils/utils_list.c \
                          src/utils/utils_env.c \
                          src/utils/utils_env2.c \
                          src/utils/utils.c \
                          src/utils/utils3.c \
                          src/builtins/exit.c \
                          src/builtins/unset.c \
                          src/builtins/env.c \
                          src/builtins/error.c \
                          src/builtins/pwd.c \
                          src/builtins/export.c \
                          src/builtins/cd.c \
                          src/builtins/echo.c \
                          src/main.c \
                          src/exec/single_command.c \
                          src/exec/signal.c \
                          src/exec/execution.c \
                          src/exec/path.c \
                          src/parsing/parsing.c \
                          src/parsing/correct_syntax.c \
                          src/parsing/extract_tokens.c \
                          src/parsing/quotes.c \
                          src/parsing/preprocess.c \
                          src/parsing/creat_cmd_list.c \
                          src/parsing/dollar_and_env.c \
                          src/parsing/file.c \
                          src/utils/utils_quotes.c \
                          src/utils/utils_exec.c \

OBJS        := $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I/Users/yugurlu/readline/include

RM		    := rm -f

${NAME}:	${OBJS}
			@${CC} ${FLAGS} -o ${NAME} ${OBJS} -I/Users/yugurlu/readline/include/ -L/Users/yugurlu/readline/lib/ -lreadline

all:		${NAME}

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
