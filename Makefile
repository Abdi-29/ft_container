NAME = ft_container

SRC = 	srcs/main.cpp

INCLUDE = -I ./includes
OBJ = $(SRC:%.cpp=%.o)


CFLAGS = -Wall -std=c++98

all: build

build:
	$(MAKE) -j4 $(NAME)

$(NAME): $(OBJ)
	clang++ -g -fsanitize=address $(OBJ) -o $(NAME)

%.o: %.cpp
	clang++ -c  $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all