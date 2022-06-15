/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 22:00:12 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::PASS(const Cmd &c)
{
	if (!c.get_arg().size())
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client()));
	if (c.get_client().get_status() == ONLINE)
	{
		if (DEBUG)
			std::cerr << s_debug("CMD", "PASS:\twrong status\t(")
				<< c.get_client().get_status() << ")" << ANSI::reset << std::endl;
		return (Server::reply(Reply::ERR_ALREADYREGISTRED, c.get_client()));
	}
	
	if (c.get_server().get_config().get("password") == c.get_arg()[0])
	{
		debug("CMD", "PASS:\tcorrect");
		if (c.get_client().get_status() != REGISTER)
			c.get_client().set_status(PASSWORD);
		else
		{
			c.get_client().set_status(ONLINE);
			Server::reply(Reply::RPL_WELCOME, c.get_client(), c.get_client().get_prefix());
		}
	}
	else
		std::cerr << ANSI::bold << ANSI::yellow << "[WARNING]:\t" << ANSI::reset
			<< ANSI::yellow << "PASS: \"" << c.get_arg()[0]
			<< "\" wrong password" << ANSI::reset << std::endl;
}
