/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/24 12:03:39 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User() {}

User::User(const int fd, struct sockaddr_in addr):
	_fd(fd)
{
	if (DEBUG)
		debug("[USER]:\tcreated");
}

User::~User()
{
	if (DEBUG)
		debug("[USER]:\tdeleted");
}

void	User::set_status(const int status)
{ this->_status = status }

int		User::get_fd(void) const
{ return (this->_fd); }

int		User::get_status(void) const
{ return (this->_status); }
