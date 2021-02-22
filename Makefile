CC			= clang++
CFLAGS		= -Wall -Wextra -Werror -std=c++98

VPATH 		= .:.:test

INCLUDES	+= includes.hpp
INCLUDES	+= iterators.hpp
INCLUDES	+= enable_if.hpp.hpp
INCLUDES	+= list.hpp
INCLUDES	+= random_access_iterator.hpp
INCLUDES	+= vector.hpp
INCLUDES	+= bst.hpp
INCLUDES	+= stack.hpp
INCLUDES	+= queue.hpp
INCLUDES	+= my_nullptr.hpp

NAME		= $C

SRCS		= $(addprefix ./unit_tests/, $(addsuffix _test.cpp, $(NAME)) utils.cpp)

$(NAME):
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@./$C
		@rm $C
		@rm -f *.o || true
