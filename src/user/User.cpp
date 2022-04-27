/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/27 15:17:43 by adelille         ###   ########.fr       */
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

	if (DEBUG)
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
		std::cerr << s_debug("USER", "add to _buffer_send:\t")
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
