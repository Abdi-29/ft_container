NAME = ft_container

SRC = 	test/test_capacity.cpp \
		test/catch_amalgamated.cpp

INCLUDE = -I ./includes
OBJ = $(SRC:%.cpp=%.o)


CFLAGS = -Wall -std=c++17 #-g -fsanitize=address

all: build

build:
	$(MAKE) -j4 $(NAME)

$(NAME): $(OBJ)
	clang++ $(OBJ) -o $(NAME)

%.o: %.cpp
	clang++ -c  $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all