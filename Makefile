##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## make files idk
##

SRC	= 		d13.c \
			itoa.c \
			move.c \

OBJ = 		$(SRC:.c=.o)

NAME = 		my_hunter

$(NAME): 		$(OBJ) 
		ar rc hunter.a $(OBJ)
		gcc hunter.a -lcsfml-graphics -lcsfml-audio -lcsfml-system -lm -o $(NAME)
		rm -f hunter.a

all: 		$(NAME) clean 

clean:
		rm -f $(wildcard *.o)
		rm -f $(wildcard *~)

fclean: clean
		rm -f $(NAME)

re:		fclean all