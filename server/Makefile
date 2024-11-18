CXX    =    g++

SRC_DIR    =    ./src/

SRC =    $(SRC_DIR)main.cpp    \

OBJ    =    $(SRC:.cpp=.o)

CXXFLAGS =     -std=c++20 -Wall -Wextra -Werror

NAME =     r-type_server

all:    $(NAME)

$(NAME):    $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	$(RM) src/*.o

fclean: clean
	rm -f $(NAME)

re:    fclean all

.PHONY:    all clean fclean re
