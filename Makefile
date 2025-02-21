NAME = minishell

SRCS = main.c ./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

HEADER = -I.
DEPS = minishell.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft -o $(NAME)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re