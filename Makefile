NAME = minishell

SRCS = minishell.c lexer.c lexer_command.c lexer_command2.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		parser.c parser2.c tree_array.c parsing_command.c parsing_command2.c \
		parsing_command3.c

OBJS = $(SRCS:.c=.o)

HEADER = -I.
DEPS = minishell.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LFLAGS = -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	@make -C Libft
	@$(CC) $(CFLAGS)  $(OBJS) -LLibft -lft -o $(NAME) $(LFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C Libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C Libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re