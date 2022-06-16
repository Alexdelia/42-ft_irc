/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:02:13 by jraffin           #+#    #+#             */
/*   Updated: 2022/06/16 15:28:55 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Bot.hpp"
#include "Cmd.hpp"

Bot::Bot(const std::string &name) throw (PipeErrorException)
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

static int	rps_to_int(const std::string &rps)
{
	if (rps == "rock")
		return (0);
	else if (rps == "paper")
		return (1);
	else if (rps == "scissors")
		return (2);
	else
		return (-1);
}

static std::string	int_to_rps(const int move)
{
	switch (move)
	{
		case 0:
			return ("rock");
		case 1:
			return ("paper");
		case 2:
			return ("scissors");
	}
	return ("");
}

static std::string	rps_win_msg(const int client, const int bot)
{
	int	winner = (3 + client - bot) % 3;

	if (winner == 1)
		return ("You won!");
	else if (winner == 2)
		return ("You lose");
	else
		return ("It's a draw");
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
			std::string	nick = c.get_prefix().substr(0, c.get_prefix().find('!'));
			std::string	msg = c.get_trailing();
			int			client_move;
			int			bot_move;

			for (size_t i = 0; i < msg.size(); ++i)
				msg[i] = tolower(msg[i]);

			client_move = rps_to_int(msg);
			if (client_move >= 0)
			{
				bot_move = rand() % 3;
				msg = int_to_rps(bot_move);
			}
			else
				msg = "You have to play either \"rock\", \"paper\" or \"scissors\".";
			std::string	buf("NOTICE " + nick + " :" + msg + "\r\n");
			if (msg.size() <= 8)
			{
				msg = rps_win_msg(client_move, bot_move);
				buf += "NOTICE " + nick + " :" + msg + "\r\n";
			}
			write(_pipe_fd, buf.c_str(), buf.size());
		}
		++i;
	}
	ssize_t size = this->_buffer_to_send.size();
	this->_buffer_to_send.clear();
	return size;
}

void	Bot::receive(Server *server)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		res;

	res = read(this->_fd, &buffer, BUFFER_SIZE);

	if (res == -1)
	{
		debug("BOT", "read == -1");
		return ;
	}
	else if (res == 0)
	{
		debug("BOT", "read == 0, status = DELETE");
		this->_status = DELETE;
		return ;
	}

	buffer[res] = '\0';

	this->_buffer_receive += buffer;

	if (this->_buffer_receive.find("\n") == std::string::npos)
	{
		if (DEBUG)
			std::cerr << s_debug("BOT", "| ") << this->_fd
				<< "\t| receiving: " << buffer << std::endl;
		return ;
	}

	if (DEBUG)
		std::cerr << s_debug("BOT", "| ") << this->_fd
			<< "\t| received:" << std::endl;

	std::size_t	pos = this->_buffer_receive.find("\r\n");
	if (pos == std::string::npos)
		pos = this->_buffer_receive.find("\n");

	while (pos != std::string::npos)
	{
		std::string	line = this->_buffer_receive.substr(0, pos);

		if (DEBUG)
			std::cerr << s_debug("\t\t\t") << line << std::endl;
		Cmd	c(line, this);
		c.exec(server);

		this->_buffer_receive.erase(0, this->_buffer_receive.find("\n") + 1);
		pos = this->_buffer_receive.find("\r\n");
		if (pos == std::string::npos)
			pos = this->_buffer_receive.find("\n");
	}
}
