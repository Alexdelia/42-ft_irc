/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 16:15:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() {}

User::User(const int fd, struct sockaddr_in addr):
	_fd(fd), _status(INIT), _last_ping(std::time(NULL))
{
	fcntl(fd, F_SETFL, O_NONBLOCK);

	(void)addr; //
	// host addr = addr.sin_addr; //
	// host name
	// getnameinfo

	// command

	// put right status
	this->_status = ONLINE;

	debug("USER", "created");
}

User::~User()
{
	close(this->_fd);

	if (DEBUG)
		std::cerr << s_debug("USER", "\t| ") << this->_fd << "\t| deleted"
			<< C_RESET << std::endl;
}

void	User::write_buffer(const std::string &str)
{
	this->_buffer_to_send += str + "\r\n";
	
	if (DEBUG)
		std::cerr << s_debug("USER", "_buffer_to_send += ")
			<< C_ITALIC << "\"" << str << "\"" << C_RESET << std::endl;
}

ssize_t	User::send_buffer(void)
{
	ssize_t	res;

	if (!this->_buffer_to_send.length())
		return (0);
	
	if (DEBUG)
		std::cerr << s_debug("USER", "sending ...\t") << C_RESET;

	res = send(this->_fd, this->_buffer_to_send.c_str(),
				this->_buffer_to_send.length(), 0);
	if (res == -1)
	{
		if (DEBUG)
			std::cerr << C_RED << "failed" << C_RESET << std::endl;
		return (res);
	}
	
	if (DEBUG)
		std::cerr << C_RED << "sent" << C_RESET << std::endl;

	this->_buffer_to_send.clear();
	this->_last_ping = std::time(NULL);

	return (res);
}

void	User::receive(void)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	res;

	res = recv(this->_fd, &buffer, BUFFER_SIZE, 0);

	if (res == -1)
	{
		debug("USER", "receive == -1");
		return ;
	}
	else if (res == 0)
	{
		debug("USER", "receive == 0, status = DELETE");
		this->_status = DELETE;
		return ;
	}

	buffer[res] = '\0';

	std::vector<std::string>			lines = ft_split(buffer, "\r\n");

	std::vector<std::string>::iterator	i = lines.begin();

	if (DEBUG)
		std::cerr << s_debug("USER", "| ") << this->_fd << "\t| receive:" << std::endl;
	
	while (i != lines.end())
	{
		if (DEBUG)
			std::cerr << s_debug("\t\t\t") << *i << std::endl;
		const Cmd	c(*i, this);
		if (g_m_cmd.count(c.cmd))
			g_m_cmd[c.cmd](c);
		else
			std::cerr << C_BOLD << C_YELLOW << "[WARNING]:\t" << C_RESET
				<< C_YELLOW << "command \"" << c.cmd
				<< "\" isn't supported" << C_RESET << std::endl;
		++i;
	}
}

void	User::set_status(const int status)
{ this->_status = status; }

void	User::set_last_ping(const int last_ping)
{ this->_last_ping = last_ping; }

int		User::get_fd(void) const
{ return (this->_fd); }

int		User::get_status(void) const
{ return (this->_status); }

int		User::get_last_ping(void) const
{ return (this->_last_ping); }
