NAME := ft_container
INCLUDE = -I ./includes
CXX := clang++
CFLAGS := -Wall -Wextra -Werror -pedantic -std=c++98
TFLAGS := -Wall -Werror -Wextra -Wpedantic -std=c++11
SRCS = main.cpp

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

OBJ = $($(SRCS):%.cpp=%.o)
DEP = $(OBJ:.o=.d)
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

TESTFILES := test_capacity.cpp

test:
	g++ $(TFLAGS) tests/$(TESTFILES) $(INCLUDE) -o catch2 && ./catch2

re: fclean all re clean test
-include $(DEP)
