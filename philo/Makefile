CC = gcc
NAME = philo
SRCS_DIR = srcs/
SRCS_FILE = main.c \
	simulate.c \
	utils.c \
	atoi.c \
	sleep.c \
	eat.c \
	arg_utils.c \
	monitor.c \
	init.c \
	routine.c \
	destroy.c \
	think.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILE))
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
