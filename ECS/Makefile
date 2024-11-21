CXX    =    g++

INCLUDE_DIR	=	./include/

INCLUDE_COMPONENT	=	./include/component/

INCLUDE_SYSTEM	=	./include/system/

SRC_DIR    =    ./src/

SRC_SYSTEM	=	./src/system/

TEST_DIR	=	./tests/

TEST_SYS	=	./tests/system/

SRC =	$(SRC_DIR)main.cpp    \
		$(SRC_SYSTEM)position_system.cpp	\
		$(SRC_SYSTEM)controllable_system.cpp	\

TEST_SRC    =	$(TEST_DIR)testsEntity.cpp	\
				$(TEST_DIR)testsSparseArray.cpp	\
				$(TEST_DIR)testsRegistry.cpp	\
				$(SRC_SYSTEM)position_system.cpp	\
				$(SRC_SYSTEM)controllable_system.cpp	\
				$(TEST_SYS)testsControllable.cpp	\
				$(TEST_SYS)testsPosition.cpp	\

OBJ    =    $(SRC:.cpp=.o)

TEST_OBJ    = $(TEST_SRC:.cpp=.o)

CXXFLAGS =     -std=c++20 -Wall -Wextra -Werror

CPPFLAGS    =    -iquote $(INCLUDE_DIR) -iquote $(INCLUDE_COMPONENT) -iquote $(INCLUDE_SYSTEM)

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
	$(RM) tests/system/*.o
	$(RM) src/system/*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re:    fclean all

.PHONY:    all clean fclean re name