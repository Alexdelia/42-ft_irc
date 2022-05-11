/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 12:29:19 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void NICK(const Cmd &c)
{
	if (c.arg[0].size())
		return ;	// error, no nickname in arg

	{
		std::vector<Client *>			u = c.get_server().get_clients();
		std::vector<Client *>::iterator i = u.begin();

		while (i != u.end())
		{
			if (c.arg[0] == (*i)->get_nickname())
				return (debug("CMD", "nickname taken"));	// error, nickname taken
			++i;
		}
	}

	c.get_client().set_nickname(c.arg[0]);
}