NAME := ft_container
INCLUDE = -I ./includes
CXX := clang++
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++98
TFLAGS := -Wall -Werror -Wextra -Wpedantic -std=c++11

SRCS = main.cpp

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

OBJ	=$(addprefix obj/, $(SRC:.cpp=.o))
OBJ_DIR = obj
DEP = $(OBJ:.o=.d)
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: srcs/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

TESTFILES := vector.cpp

test:
	g++ $(TFLAGS) tests/$(TESTFILES) $(INCLUDE) -o catch2 && ./catch2

re: fclean all re clean test
-include $(DEP)
