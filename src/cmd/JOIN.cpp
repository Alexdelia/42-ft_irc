/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:19:09 by adelille          #+#    #+#             */
/*   Updated: 2022/06/14 15:52:52 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::JOIN(const Cmd &c)
{
	// check if channel is full

	if (c.get_arg().size() < 1)
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client(), c.get_cmd_name()));

	std::vector<std::string>			cpy = ft_split(c.get_arg()[0], ",");
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		if ((*i)[0] != '#')
			Server::reply(Reply::ERR_NOSUCHCHANNEL, c.get_client(), *i);
		else
		{
			c.get_server().join_channel(*i, c.get_client());
			c.get_server().get_channel(*i)->write_all_buffers(
				std::string(":" + c.get_client().get_nickname() + " " + c.get_cmd_name() + " " + *i));	
			if (c.get_server().get_channel(*i)->get_topic().size() < 1)
				Server::reply(Reply::RPL_NOTOPIC, c.get_client(), *i);
			else
			{
				std::vector<std::string>	v;
				v.push_back(*i);
				v.push_back(c.get_server().get_channel(*i)->get_topic());
				Server::reply(Reply::RPL_TOPIC, c.get_client(), v);
			}
			{
				std::vector<std::string>	v;
				v.push_back(*i);
				v.push_back(c.get_server().get_channel(*i)->get_names());
				Server::reply(Reply::RPL_NAMREPLY, c.get_client(), v);
				Server::reply(Reply::RPL_ENDOFNAMES, c.get_client(), *i);
			}
		}
		++i;
	}
}