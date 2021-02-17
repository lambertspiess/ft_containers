NAME	= $N
CC		= clang++
#CFLAGS	= -Wall -Wextra -std=c++98 -ferror-limit=1
CFLAGS	= -Wall -Wextra -std=c++98 -ferror-limit=1 -fsanitize=address,undefined

VPATH = .:.:test

INCLUDES += includes.hpp
INCLUDES += iterators.hpp
INCLUDES += enable_if.hpp.hpp
INCLUDES += list.hpp
INCLUDES += random_access_iterator.hpp
INCLUDES += vector.hpp
INCLUDES += bst.hpp
INCLUDES += stack.hpp
INCLUDES += queue.hpp

SRCS	= $(addprefix ./unit_tests/, $(addsuffix _test.cpp, $(NAME)) utils.cpp)

$(NAME):
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@./$N
		@rm $N
