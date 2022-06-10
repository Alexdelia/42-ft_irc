/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:56:47 by adelille          #+#    #+#             */
/*   Updated: 2022/06/10 18:51:52 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::PRIVMSG(const Cmd &c)
{
	if (c.get_arg().size() < 1)
		return (Server::reply(Reply::ERR_NORECIPIENT, c.get_client(), c.get_cmd_name()));
	if (c.get_prefix().size() == 0)
		return (Server::reply(Reply::ERR_NOTEXTTOSEND, c.get_client()));

	std::vector<std::string>			cpy = ft_split(c.get_arg()[0], ",");
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		if ((*i)[0] == '#' && c.get_server().get_channel(*i) != NULL)
			c.get_server().get_channel(*i)->send_msg(c.get_prefix());
		else if (c.get_server().nick_exists(*i))
			c.get_client().write_to(*c.get_server().get_client(*i),
				std::string("PRIVMSG " + c.get_arg()[0] + " :" + c.get_prefix()));
		else
			Server::reply(Reply::ERR_NOSUCHNICK, c.get_client(), *i);
		++i;
	}
}
