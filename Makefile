# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adelille <adelille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/30 19:21:49 by adelille          #+#    #+#              #
#    Updated: 2022/06/10 15:40:42 by adelille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL				=	/bin/sh

PROGNAME			:=	ircserv

INCLUDEDIR			:=	src
SRCDIR				:=	src

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

COMMONSRCS			:=	main.cpp							\
						utils/debug.cpp						\
						utils/ft_split.cpp					\
						utils/error.cpp						\
						utils/time.cpp						\
						server/Config.cpp					\
						server/Server.cpp					\
						server/Reply.cpp					\
						server/private/_ping.cpp			\
						server/private/client_handle.cpp	\
						channel/Channel.cpp					\
						client/Client.cpp					\
						cmd/Cmd.cpp							\
						cmd/PING.cpp						\
						cmd/PONG.cpp						\
						cmd/WHOIS.cpp						\
						cmd/PRIVMSG.cpp						\
						cmd/JOIN.cpp						\
						cmd/PART.cpp						\
						cmd/client_modification/USER.cpp	\
						cmd/client_modification/QUIT.cpp	\
						cmd/client_modification/PASS.cpp	\
						cmd/client_modification/NICK.cpp	\

CXX					:=	c++
RM					:=	rm

CXXFLAGS			:=	-Wall -Wextra -Werror -std=c++98
OPTFLAG				:=	-DDEBUG=1
LIBFLAGS			:=

NAME				:=	$(PROGNAME)

OUTDIR				:=	$(OBJDIR)

DEBUGNAME			:= $(addsuffix .debug,$(PROGNAME))

ifdef DEBUG
	OPTFLAG 		+=	-g
	NAME			:=	$(DEBUGNAME)
	OUTDIR			:=	$(DEBUGDIR)
endif

$(OUTDIR)/%.o		:	$(SRCDIR)/%.cpp | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CXX) -c -MMD -MP $(CXXFLAGS) $(OPTFLAG) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.cpp=.o))
	$(CXX) $(CXXFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(COMMONSRCS:.cpp=.o)) $(LIBFLAGS)

all					:	$(NAME)

ifdef DEBUG
debug				:	all
else
$(DEBUGNAME)		:
	$(MAKE) $(DEBUGNAME) DEBUG=1
debug				:
	$(MAKE) DEBUG=1 debug
endif

$(OUTDIR)			:
	mkdir $(OUTDIR)

clean				:
	$(RM) -rf $(OBJDIR) $(DEBUGDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME) $(DEBUGNAME)

re					:	fclean
	$(MAKE)

.PHONY				:	all debug clean fclean re

-include	$(addprefix $(OUTDIR)/,$(COMMONSRCS:.cpp=.d))
