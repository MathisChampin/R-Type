INCLUDE_DIR      = ./include/
INCLUDE_SYSTEM   = ./include/system/
INCLUDE_COMPONENT = ./include/component/

SRC_DIR          = ./src/
SRC_SYSTEM       = ./src/system/

SRC =   $(SRC_SYSTEM)controllable_system.cpp \
        $(SRC_SYSTEM)position_system.cpp	\
		$(SRC_SYSTEM)level_system.cpp		\
		$(SRC_SYSTEM)collision_system.cpp		\
		$(SRC_SYSTEM)shoot_system.cpp		\
		$(SRC_SYSTEM)kill_system.cpp		\
		$(SRC_SYSTEM)win_system.cpp		\
		$(SRC_SYSTEM)lose_system.cpp		\
		$(SRC_SYSTEM)collision_power_up_move_system.cpp	\
		$(SRC_SYSTEM)collision_power_up_shoot_system.cpp	\

SRC_MAIN	=	$(SRC_DIR)main.cpp

SRC_TEST =  tests/system/testsPosition.cpp \
			tests/system/testsCollision.cpp	\
			tests/system/testsShoot.cpp		\
			tests/system/testsLevel.cpp		\
			tests/system/testsWin.cpp		\
			tests/system/testsLose.cpp		\
			tests/system/testsCollisionPowerUpMove.cpp	\
			tests/system/testsCollisionPowerUpShoot.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS = -std=c++20 -Wall -Wextra
CPPFLAGS = -iquote $(INCLUDE_DIR) -iquote $(INCLUDE_SYSTEM) -iquote $(INCLUDE_COMPONENT)

NAME = ecs
NAME_TESTS = unit_tests

TTFLAGS = -lcriterion
CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(SRC_MAIN) $(OBJ) $(CPPFLAGS) $(CXXFLAGS) -g3 -lgmp

tests_run:
	$(CC) $(SRC_TEST) $(SRC) -o $(NAME_TESTS) $(TTFLAGS) $(CPPFLAGS) $(CXXFLAGS)
	./$(NAME_TESTS)

clean:
	$(RM) $(SRC:.cpp=.o)
	$(RM) $(SRC_MAIN:.cpp=.o)
	$(RM) $(SRC_TEST:.cpp=.o)
	$(RM) *.gcno

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_TESTS)

re: fclean all

.PHONY: all clean fclean re tests_run
