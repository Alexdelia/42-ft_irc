/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 17:01:40 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void Cmd::_NICK(void)
{
	if (this->_arg[0].size())
		return ;	// error, no nickname in arg

	{
		std::vector<Client *>			u = this->_server->get_clients();
		std::vector<Client *>::iterator i = u.begin();

		while (i != u.end())
		{
			if (this->_arg[0] == (*i)->get_nickname())
				return (debug("CMD", "nickname taken"));	// error, nickname taken
			++i;
		}
	}

	this->_client->set_nickname(this->_arg[0]);
}