NAME	= $N
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 -ferror-limit=5 *.hpp
#-fsanitize=address,undefined

VPATH = .:.:test

INCLUDES += includes.hpp
INCLUDES += iterators.hpp
INCLUDES += enable_if.hpp.hpp
INCLUDES += list.hpp
INCLUDES += vector.hpp

SRCS	= $(addprefix ./test/, $(addsuffix _test.cpp, $(NAME)) test.cpp)

$(NAME):
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@./$N
		@rm $N
