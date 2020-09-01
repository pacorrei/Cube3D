NAME = Cube3D

all: ${NAME}

CFLAGS = -Wall -Werror -Wextra

CC = gcc

RM = rm -rf

HEAD = -I include/ -I /usr/local/include/ -L /usr/local/lib/ -lmlx -lm -lXext -lX11 -lbsd


SRCS_PATH = srcs/

OBJS_PATH = objs/

SRCS_NAME = parsing.c find_informations.c free_utils.c ft_cube_utils.c \
	    ft_error.c ft_identifiers.c ft_identifiers2.c get_next_line.c \
	    get_next_line_utils.c verif_argument.c main.c ft_identifiers3.c \
		ft_identifiers4.c ft_identifiers5.c verif_valid_map.c \
		make_bmp.c \

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir $(OBJS_PATH) 2> /dev/null || true
	gcc -c $(FLAGS) $(HEAD) -o $@ -c $<

$(NAME):  ${OBJS}
		${CC} ${CFLAGS} ${SRCS} ${HEAD} -o ${NAME}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re :	fclean all

.PHONY: all clean fclean re




