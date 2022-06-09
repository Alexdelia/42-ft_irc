/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:56:47 by adelille          #+#    #+#             */
/*   Updated: 2022/06/09 19:22:36 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::PRIVMSG(const Cmd &c)
{
	if (c.get_arg().size() < 1)
		return (Server::reply(Reply::ERR_NORECIPIENT, c.get_client(),
			std::vector<std::string>(1, c.get_cmd_name())));
	if (c.get_prefix().size() == 0)
		return (Server::reply(Reply::ERR_NOTEXTTOSEND, c.get_client()));
	
	std::vector<std::string>			cpy = ft_split(c.get_arg()[0], ",");
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		if (c.get_server().is_nickname_taken(*i))
			c.get_client().write_to(*c.get_server().get_client(*i), c.get_prefix());
		else
			Server::reply(Reply::ERR_NOSUCHNICK, c.get_client(),
				std::vector<std::string>(1, *i));
		++i;
	}
}
