CXX    =    g++

INCLUDE_DIR	=	./include/

SRC_DIR    =    ./src/
TEST_DIR	=	./tests/

TEST_SRC    =	$(TEST_DIR)testsEntity.cpp	\

SRC =	$(SRC_DIR)main.cpp    \

OBJ    =    $(SRC:.cpp=.o)

TEST_OBJ    = $(TEST_SRC:.cpp=.o)

CXXFLAGS =     -std=c++20 -Wall -Wextra -Werror

CPPFLAGS    =    -iquote $(INCLUDE_DIR)

LDFLAGS     = -lcriterion

NAME =    bootstrap_rtype

TEST_NAME   = unit_tests

all:    $(NAME)

$(NAME):    $(OBJ)
		$(CXX) -o $(NAME) $(MAIN) $(OBJ) $(CPPFLAGS) $(CXXFLAGS) -g3

tests: $(TEST_OBJ)
	$(CXX) -o $(TEST_NAME) $(TEST_OBJ) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)

test_run: tests
	./$(TEST_NAME)

clean:
	$(RM) src/*.o
	$(RM) tests/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re:    fclean all

.PHONY:    all clean fclean re name