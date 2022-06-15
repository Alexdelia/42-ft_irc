/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KILL.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:50:35 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 17:25:14 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::KILL(const Cmd &c)
{
	if (!c.get_client().is_operator())
		return (Server::reply(Reply::ERR_NOPRIVILEGES, c.get_client()));
	if (!c.get_arg().size() || !c.get_trailing().size())
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client(), c.get_cmd_name()));
	if (!c.get_server().nick_exists(c.get_arg()[0]))
		return (Server::reply(Reply::ERR_NOSUCHNICK, c.get_client(), c.get_arg()[0]));

	c.get_server().get_client(c.get_arg()[0])->set_status(KILLED);
	c.get_server().get_client(c.get_arg()[0])->write_buffer(
		std::string(c.get_cmd_name() + " " + c.get_arg()[0] + " :" + c.get_trailing()));
}
