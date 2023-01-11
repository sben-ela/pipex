CFLAGS = -Wall -Wextra -Werror
NAME = pipex.a
EX_FILE = pipex

SOURCES = pipex.c pipex_util.c ft_strjoin.c ft_strlen.c ft_split.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	gcc $(CFLAGS) $(NAME) -o $(EX_FILE)
	
clean:
	rm -f $(OBJECTS) 

fclean: clean
	rm -f $(NAME)

re: fclean all