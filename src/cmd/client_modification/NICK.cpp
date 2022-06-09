/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/09 18:21:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::NICK(const Cmd &c)
{
	if (!c.get_arg()[0].size())
		return (Server::reply(Reply::ERR_NONICKNAMEGIVEN, c.get_client()));	// error, no nickname in arg

	{
		std::vector<Client *>			u = c.get_server().get_clients();
		std::vector<Client *>::iterator i = u.begin();

		while (i != u.end())
		{
			if (c.get_arg()[0] == (*i)->get_nickname())
				return (debug("CMD", "nickname taken"), Server::reply(Reply::ERR_NICKCOLLISION, c.get_client()));	// error, nickname taken
			++i;
		}
	}

	c.get_client().set_nickname(c.get_arg()[0]);
	c.get_server().insert_nickname(c.get_arg()[0], &c.get_client());
}