NAME = bin
SANNAME = $(addprefix san_,$(NAME))
VALNAME = $(addprefix val_,$(NAME))

VPATH =.:.

FLAGS = -Wall -Wextra -std=c++98
ASANFLAGS = -Wall -Wextra \
			-Wformat-security -Werror=format-security -Werror=array-bounds -g \
			-fsanitize=address
VALFLAGS = -Wall -Wextra -ggdb3

SRCS += main.cpp

INCLUDES += includes.hpp
INCLUDES += utils.hpp
INCLUDES += iterator_base_types.hpp
INCLUDES += iterator_base_funcs.hpp

OBJSPATH = objs
SANOBJSPATH = sanobjs
VALOBJSPATH = valobjs

OBJSNAMES = $(SRCS:.cpp=.o)

OBJS = $(addprefix $(OBJSPATH)/,$(OBJSNAMES))
SANOBJS = $(addprefix $(SANOBJSPATH)/,$(OBJSNAMES))
VALOBJS = $(addprefix $(VALOBJSPATH)/,$(OBJSNAMES))

GREEN = \033[32m
CYAN = \033[0;36m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m

CLEAR = \033[0m

# Clear line
CLRLINE = \033[K

# Go back to line
BTOLINE = \033[A

$(NAME): $(OBJS)
	@clang++ $(FLAGS) -o $(NAME) $(OBJS)

$(OBJS): $(OBJSPATH)/%.o: %.cpp
	@mkdir $(OBJSPATH) 2> /dev/null || true
	@clang++ $(FLAGS) -o $@ -c $<
	@echo "$(CYAN) Compiling $<$(CLEAR)$(CLRLINE)$(BTOLINE)"

san: $(SANOBJS)
	@clang++ $(ASANFLAGS) -o $(SANNAME) $(SANOBJS)

$(SANOBJS): $(SANOBJSPATH)/%.o: %.cpp
	@mkdir $(SANOBJSPATH) 2> /dev/null || true
	@clang++ $(ASANFLAGS) -o $@ -c $<
	@echo "$(CYAN) Compiling $<$(CLEAR)$(CLRLINE)$(BTOLINE)"

val:  $(VALOBJS)
	@clang++ $(VALFLAGS) -o $(VALNAME) $(VALOBJS)

$(VALOBJS): $(VALOBJSPATH)/%.o: %.cpp
	@mkdir $(VALOBJSPATH) 2> /dev/null || true
	@clang++ $(VALFLAGS) -o $@ -c $<
	@echo "$(CYAN) Compiling $<$(CLEAR)$(CLRLINE)$(BTOLINE)"

all: $(NAME)

clean:
	@rm -r $(OBJSPATH) 2> /dev/null || true

sanclean:
	@rm -r $(SANOBJSPATH) 2> /dev/null || true

valclean:
	@rm -r $(VALOBJSPATH) 2> /dev/null || true

fclean: clean
	@rm -f $(NAME) 2> /dev/null || true

sanfclean: sanclean
	@rm -f $(SANNAME) 2> /dev/null || true

valfclean: valclean
	@rm -f $(VALNAME) 2> /dev/null || true

re : fclean all

sanre : sanfclean
	@make san

valre : valfclean
	@make val

fcleanall: fclean sanfclean valfclean
