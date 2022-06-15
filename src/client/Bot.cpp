/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:02:13 by jraffin           #+#    #+#             */
/*   Updated: 2022/06/15 18:35:43 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Bot.hpp"
#include "Cmd.hpp"

Bot::Bot(const std::string name) throw (PipeErrorException)
{
	int pipefd[2];

	srand(std::time(NULL));
	if (pipe2(pipefd, O_NONBLOCK))
		throw Bot::PipeErrorException();

	_fd = pipefd[0];
	_status = ONLINE;
	_pipe_fd = pipefd[1];
	_nickname = name;
	_username = name;
	_realname = name;
	_hostname = name;
}

Bot::~Bot() {
	close(this->_pipe_fd);
	close(this->_fd);
	if (DEBUG)
	std::cerr << s_debug("BOT", "\t| ") << this->_fd << "\t| deleted"
		<< ANSI::reset << std::endl;
}

ssize_t	Bot::send_buffer(void)
{
	if (!this->_buffer_to_send.length())
		return (0);

	std::vector<std::string>			lines = ft_split(this->_buffer_to_send, "\r\n");
	std::vector<std::string>::iterator	i = lines.begin();

	while (i != lines.end())
	{
		if (*(i->rbegin()) == '\n')
			i->resize(i->size() - 1);
		const Cmd	c(*i, this);
		if (c.get_cmd_name() == "PING")
		{
			std::string buf("PONG " + c.get_arg()[0] + "\r\n");
			write(_pipe_fd, buf.c_str(), buf.size());
		}
		else if (c.get_cmd_name() == "PRIVMSG" && c.get_arg()[0][0] != '#')
		{
			std::string nick = c.get_prefix().substr(0, c.get_prefix().find('!'));
			std::string msg = c.get_trailing();
			for (size_t i = 0; i < msg.size(); ++i)
				msg[i] = tolower(msg[i]);
			if (c.get_trailing() == "rock" || c.get_trailing() == "paper" || c.get_trailing() == "scissor")
			{
				switch (rand()%3)
				{
					case 0:
						msg = "rock";
						break;
					case 1:
						msg = "rock";
						break;
					case 2:
						msg = "rock";
						break;
				}
			}
			else
				msg = "You have to play either \"rock\", \"paper\" or \"scissor\".";
			std::string buf("PRIVMSG " + nick + " :" + msg + "\r\n");
			write(_pipe_fd, buf.c_str(), buf.size());
		}
		++i;
	}
	ssize_t size = this->_buffer_to_send.size();
	this->_buffer_to_send.clear();
	return size;
}
