
NAME=	a.out

SRC=	src/main.cpp

OBJ=	$(SRC:.cpp=.o)

CXX=	g++

CXXFLAGS= -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

