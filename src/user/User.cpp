/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/27 00:08:50 by adelille         ###   ########.fr       */
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

	if (DEBUG)
		debug("USER", "created");
}

User::~User()
{
	close(this->_fd);

	if (DEBUG)
		debug("USER", "deleted");
}

void	User::write_buffer(const std::string &str)
{
	this->_buffer_send += str + "\r\n";
	
	if (DEBUG)
		std::cerr << s_debug("USER", "add to _buffer_send:\t")
			<< C_ITALIC << "\"" << str << "\"" << C_RESET << std::endl;
}

void	User::send_buffer(void)
{
	if (DEBUG)
		std::cerr << s_debug("USER", "sending ...\t") << C_RESET;
	if (!this->_buffer_send.length())
		return ;

	if (send(this->_fd, this->_buffer_send.c_str(),
				this->_buffer_send.length(), 0))
		error("[USER]:  \tsend failed");
	else if (DEBUG)
		std::cerr << C_RED << "sent" << C_RESET << std::endl;
}

void	User::set_status(const int status)
{ this->_status = status; }

int		User::get_fd(void) const
{ return (this->_fd); }

int		User::get_status(void) const
{ return (this->_status); }

int		User::get_last_ping(void) const
{ return (this->_last_ping); }
