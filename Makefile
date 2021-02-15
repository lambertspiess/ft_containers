NAME	= $N
CC		= clang++
#CFLAGS	= -Wall -Wextra -std=c++98 -ferror-limit=1 #-fsanitize=address,undefined
CFLAGS	= -Wall -Wextra -std=c++98 -ferror-limit=1 -fsanitize=address,undefined
#CFLAGS	= -Wall -Wextra -Werror -std=c++98 -ferror-limit=1 #-fsanitize=address,undefined

VPATH = .:.:test

INCLUDES += includes.hpp
INCLUDES += iterators.hpp
INCLUDES += enable_if.hpp.hpp
INCLUDES += list.hpp
INCLUDES += random_access_iterator.hpp
INCLUDES += vector.hpp
INCLUDES += bst.hpp
INCLUDES += stack.hpp

SRCS	= $(addprefix ./test/, $(addsuffix _test.cpp, $(NAME)) test.cpp)

$(NAME):
		@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
		@./$N
		@rm $N
