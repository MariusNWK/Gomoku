##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Gomoku
##

SRC	=	$(wildcard src/*.cpp)

OBJ	=	$(SRC:.cpp=.o)

NAME	=	pbrain-gomoku-ai

CXXFLAGS	=	-g -fPIC

all:	$(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS) -W -Wall -Wextra

clean:
ifeq ($(OS),Windows_NT)
	del src\*.o
else
	$(RM) $(OBJ)
endif

fclean:	clean
ifeq ($(OS),Windows_NT)
	del $(NAME).exe
else
	$(RM) $(NAME)
endif

re:	fclean all

.PHONY: all clean fclean re
