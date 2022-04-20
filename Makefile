# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adelille <adelille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 19:21:49 by adelille          #+#    #+#              #
#    Updated: 2022/04/20 16:21:34 by adelille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	ircserv
CC = 	c++
RM = 	rm -rf

CFLAGS =	-Wall -Werror -Wextra
CFLAGS +=	-std=c++98

CFLAGS +=	-g3
# CFLAGS +=	-fsanitize=address

LKFLAGS =	-MMD -MP


# **************************************************************************** #
#	MAKEFILE	#

#MAKEFLAGS += --silent

SHELL := bash

B =		$(shell tput bold)
BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)
D =		$(shell tput sgr0)
BEL =	$(shell tput bel)
CLR =	$(shell tput el 1)

# **************************************************************************** #
#	SRCS	#

SRCSPATH =	./src/
OBJSPATH =	./obj/
INC =		./inc/

SRCS =		$(wildcard $(SRCSPATH)*.cpp) $(wildcard $(SRCSPATH)**/*.cpp)
SRCSNAME =	$(subst $(SRCSPATH), , $(SRCS))

OBJSNAME =	$(SRCSNAME:.cpp=.o)
OBJS =		$(addprefix $(OBJSPATH), $(OBJSNAME))

# *************************************************************************** #

define	progress_bar
	@i=0
	@while [[ $$i -le $(words $(SRCS)) ]] ; do \
		printf " " ; \
		((i = i + 1)) ; \
	done
	@printf "$(B)]\r[$(D)"
endef

# *************************************************************************** #
#	RULES	#

$(OBJSPATH)%.o: $(SRCSPATH)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LKFLAGS) -I$(INC) -c $< -o $@
	@printf "$(B)$(GRE)█$(D)"


all:		launch $(NAME)
	@printf "\n$(B)$(MAG)$(NAME) compiled$(D)\n"

test:		all
	@./$(NAME)

cfdebug:
	$(eval CFLAGS += -DDEBUG=1)

debug: fclean cfdebug all

quiet:
	$(eval MAKEFLAGS += --silent)
	@$(MAKE)

launch:
	$(call progress_bar)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
clean:
	@$(RM) $(OBJSPATH)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re launch test cfdebug debug quiet

# **************************************************************************** #
