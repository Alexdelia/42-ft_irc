/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 20:01:12 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

static bool	valid_nick(const std::string &nick)
{
	for (std::string::const_iterator i = nick.begin(); i != nick.end(); ++i)
	{
		if (!((*i >= '0' && *i <= '9') || (*i >= 'A' && *i <= '}')))
			return (false);
	}
	return (true);
}

void	Cmd::NICK(const Cmd &c)
{
	if (!c.get_arg()[0].size())
		return (Server::reply(Reply::ERR_NONICKNAMEGIVEN, c.get_client()));	// error, no nickname in arg
	if (!valid_nick(c.get_arg()[0]))
		return (Server::reply(Reply::ERR_ERRONEUSNICKNAME, c.get_client(), c.get_arg()[0]));
	if (c.get_server().nick_exists(c.get_arg()[0]))
		return (debug("CMD", "nickname taken"),
			Server::reply(Reply::ERR_NICKNAMEINUSE, c.get_client(), c.get_arg()[0]));	// error, nickname taken

	if (c.get_client().get_nickname().size())
	{
		c.get_server().unbind_nick(c.get_client().get_nickname());
		c.get_server().write_all_buffers(std::string(":" + c.get_client().get_nickname() 
		+ " " + c.get_cmd_name() + " " + c.get_arg()[0]));
	}

	c.get_client().set_nickname(c.get_arg()[0]);
	c.get_server().bind_nick(c.get_arg()[0], &c.get_client());
}
