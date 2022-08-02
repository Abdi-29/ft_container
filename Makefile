NAME = ft_container

SRC = 	srcs/main.cpp

INCLUDE = -I ./includes
OBJ = $(SRC:%.cpp=%.o)


CFLAGS = -Wall -Werror -Wextra -std=c++11 #-g -fsanitize=address

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