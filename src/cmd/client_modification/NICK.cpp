/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/10 18:51:52 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::NICK(const Cmd &c)
{
	if (!c.get_arg()[0].size())
		return (Server::reply(Reply::ERR_NONICKNAMEGIVEN, c.get_client()));	// error, no nickname in arg

	if (c.get_server().nick_exists(c.get_arg()[0]))
		return (debug("CMD", "nickname taken"),
			Server::reply(Reply::ERR_NICKCOLLISION, c.get_client()));	// error, nickname taken

	if (c.get_client().get_nickname().size())
	{
		c.get_server().unbind_nick(c.get_client().get_nickname());
		c.get_client().write_buffer(std::string(":" + c.get_client().get_nickname() + " NICK " + c.get_arg()[0]));
	}

	c.get_client().set_nickname(c.get_arg()[0]);
	c.get_server().bind_nick(c.get_arg()[0], &c.get_client());
}
