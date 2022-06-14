/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:19:09 by adelille          #+#    #+#             */
/*   Updated: 2022/06/14 15:53:28 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::PART(const Cmd &c)
{
	if (c.get_arg().size() < 1)
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client(), c.get_cmd_name()));

	std::vector<std::string>			cpy = ft_split(c.get_arg()[0], ",");
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		if (!c.get_server().get_channel(*i))
			return (Server::reply(Reply::ERR_NOSUCHCHANNEL, c.get_client(), *i));
		if (!c.get_server().get_channel(*i)->is_member(c.get_client()))
			return (Server::reply(Reply::ERR_NOTONCHANNEL, c.get_client(), *i));
		
		c.get_server().get_channel(*i)->write_all_buffers(
			std::string(":" + c.get_client().get_nickname() + " " + c.get_cmd_name() + " " + *i));

		c.get_server().leave_channel(*i, c.get_client());
		
		++i;
	}
}