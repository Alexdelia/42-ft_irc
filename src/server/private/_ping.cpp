/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _ping.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:03:34 by adelille          #+#    #+#             */
/*   Updated: 2022/05/19 13:03:48 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

void	Server::_ping(void)
{
	if (DEBUG)
		std::cerr << s_debug("PING", "")
			<< s_time(std::time(NULL) - this->_start_time) << std::endl;

	const int							time = std::time(NULL);
	const int							timeout = atoi(_config.get("ping").c_str());
	std::map<int, Client *>::iterator	i = this->_clients.begin();

	while (i != this->_clients.end())
	{
		if (time - i->second->get_last_ping() >= timeout * 2 + 1)
		{
			// set reason of delete // to do later
			i->second->set_status(DELETE);
			if (DEBUG)
			std::cerr << ANSI::bold << " timeout";
		}
		else if (i->second->get_status() == ONLINE)
			i->second->write_buffer("PING " + i->second->get_nickname());
		++i;
	}

	this->_last_ping = std::time(NULL);

	if (DEBUG)
		std::cerr << s_debug("PONG", "")
			<< s_time(std::time(NULL) - this->_start_time) << std::endl;
}
