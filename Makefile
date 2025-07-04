#If the subject requires it, you must submit a Makefile that compiles your source
#files to the required output with the flags -Wall, -Wextra, and -Werror, using cc.
#Additionally, your Makefile must not perform unnecessary relinking.
#Your Makefile must at contain at least the rules $(NAME), all, clean, fclean and
#re

NAME = get_next_line.a
FLAGS = -Wall -Wextra -Werror
CC = cc

OBJS = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME)

re: fclean all
