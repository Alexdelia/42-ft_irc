/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:56:47 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 17:25:14 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::PRIVMSG(const Cmd &c)
{
	if (c.get_arg().size() < 1)
		return (Server::reply(Reply::ERR_NORECIPIENT, c.get_client(), c.get_cmd_name()));
	if (c.get_trailing().size() == 0)
		return (Server::reply(Reply::ERR_NOTEXTTOSEND, c.get_client()));

	std::vector<std::string>			cpy = ft_split(c.get_arg()[0], ",");
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		if ((*i)[0] == '#' && c.get_server().get_channel(*i) != NULL)
			c.get_server().get_channel(*i)->write_all_buffers(
				":" + c.get_client().get_prefix() + " " + c.get_cmd_name()
				+ " " + c.get_arg()[0] + " :" + c.get_trailing(),
				c.get_client().get_nickname());
		else if (c.get_server().nick_exists(*i))
			c.get_client().write_to(*c.get_server().get_client(*i),
				std::string(c.get_cmd_name() + " " + c.get_arg()[0] + " :" + c.get_trailing()));
		else
			Server::reply(Reply::ERR_NOSUCHNICK, c.get_client(), *i);
		++i;
	}
}
