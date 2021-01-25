NAME	= $N
CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98 #-fsanitize=address,undefined

VPATH = .:.:test

INCLUDES += includes.hpp
INCLUDES += iterators.hpp
INCLUDES += list.hpp

SRCS	= $(addprefix ./test/, $(addsuffix _test.cpp, $(NAME)) test.cpp)

$(NAME):
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@./$N
		@rm $N
