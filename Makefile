NAME = philo_bonus

CFLAGS = -Wall -Wextra -Werror

CC = cc

HEADER = philo_bonus.h

SRCS = main_bonus.c \
		error_messages.c\
		parsing.c\
		philo_bonus.c\
		safe_func.c\
		start_dinner.c\
		utils_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.%o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all