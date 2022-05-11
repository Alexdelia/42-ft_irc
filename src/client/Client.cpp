/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 16:41:03 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() {}

Client::Client(const int fd, struct sockaddr_in addr):
	_fd(fd), _status(INIT), _last_ping(std::time(NULL))
{
	fcntl(fd, F_SETFL, O_NONBLOCK);

	(void)addr; //
	// host addr = addr.sin_addr; //
	// host name
	// getnameinfo

	// put right status
	this->_status = PASSWORD;
	//this->_status = ONLINE;

	this->_nickname = "";

	debug("CLIENT", "created");
}

Client::~Client()
{
	close(this->_fd);

	if (DEBUG)
		std::cerr << s_debug("CLIENT", "\t| ") << this->_fd << "\t| deleted"
			<< ANSI::reset << std::endl;
}

void	Client::write_buffer(const std::string &str)
{
	this->_buffer_to_send += str + "\r\n";
	
	if (DEBUG)
		std::cerr << s_debug("CLIENT", "_buffer_to_send += ")
			<< ANSI::italic << "\"" << str << "\"" << ANSI::reset << std::endl;
}

ssize_t	Client::send_buffer(void)
{
	ssize_t	res;

	if (!this->_buffer_to_send.length())
		return (0);
	
	if (DEBUG)
		std::cerr << s_debug("CLIENT", "sending ...\t") << ANSI::reset;

	res = send(this->_fd, this->_buffer_to_send.c_str(),
				this->_buffer_to_send.length(), 0);
	if (res == -1)
	{
		if (DEBUG)
			std::cerr << ANSI::red << "failed" << ANSI::reset << std::endl;
		return (res);
	}
	
	if (DEBUG)
		std::cerr << ANSI::red << "sent" << ANSI::reset << std::endl;

	this->_buffer_to_send.clear();
	this->_last_ping = std::time(NULL);

	return (res);
}

void	Client::receive(Server *server)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	res;

	res = recv(this->_fd, &buffer, BUFFER_SIZE, 0);

	if (res == -1)
	{
		debug("CLIENT", "receive == -1");
		return ;
	}
	else if (res == 0)
	{
		debug("CLIENT", "receive == 0, status = DELETE");
		this->_status = DELETE;
		return ;
	}

	buffer[res] = '\0';

	std::vector<std::string>			lines = ft_split(buffer, "\r\n");

	std::vector<std::string>::iterator	i = lines.begin();

	if (DEBUG)
		std::cerr << s_debug("CLIENT", "| ") << this->_fd << "\t| receive:" << std::endl;
	
	while (i != lines.end())
	{
		if (DEBUG)
			std::cerr << s_debug("\t\t\t") << *i << std::endl;
		const Cmd	c(*i, server, this);
		++i;
	}
}

void	Client::set_status(const int status)
{
	if (DEBUG)
		std::cerr << s_debug("CLIENT", "set_status\t(")
			<< this->_status << " -> " << status << ')'
			<< ANSI::reset << std::endl;
	this->_status = status;
}

void	Client::set_last_ping(const int last_ping)
{ this->_last_ping = last_ping; }

void	Client::set_nickname(const std::string &nickname)
{ this->_nickname = nickname; }

int		Client::get_fd(void) const
{ return (this->_fd); }

int		Client::get_status(void) const
{ return (this->_status); }

int		Client::get_last_ping(void) const
{ return (this->_last_ping); }

const std::string	&Client::get_nickname(void) const
{ return (this->_nickname); }
