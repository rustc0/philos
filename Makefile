NAME = philo

CC = cc -g -Wall -Wextra -Werror

CFLAGS = -pthread -fsanitize=thread

SRCS = main.c utils.c init.c utilstani.c thread.c routine.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo.h
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c philo.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJS)
