#If the subject requires it, you must submit a Makefile that compiles your source
#files to the required output with the flags -Wall, -Wextra, and -Werror, using cc.
#Additionally, your Makefile must not perform unnecessary relinking.
#Your Makefile must at contain at least the rules $(NAME), all, clean, fclean and
#re


NAME = get_next_line.a
BONUS_NAME = get_next_line_bonus.a
FLAGS = -Wall -Wextra -Werror
CC = cc

SRC = get_next_line.c get_next_line_utils.c
OBJS = $(SRC:.c=.o)
BONUS_SRC = get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS = $(BONUS_SRC:.c=.o)


.PHONY: all clean fclean re bonus


all: $(NAME)


%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@


$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(BONUS_NAME): $(BONUS_OBJS)
	ar rcs $(BONUS_NAME) $(BONUS_OBJS)



bonus: $(BONUS_NAME) $(NAME)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)


fclean:
	rm -rf $(NAME) $(BONUS_NAME)


re: fclean all
