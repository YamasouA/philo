CC = gcc
NAME = philo
SRCS = main.c \
	simulate.c \
	utils.c \
	atoi.c \
	action.c \
	arg_utils.c \
	monitor.c \
	init.c
OBJS = $(SRCS:.c=.o)
INCLUDE = -I includes
CFLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
