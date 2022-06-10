/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/10 17:36:40 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::USER(const Cmd &c)
{
	if (c.get_arg().size() < 3)
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client(),
			std::vector<std::string>(1, c.get_cmd_name())));
	if (c.get_client().get_status() != PASSWORD)
		return (Server::reply(Reply::ERR_ALREADYREGISTRED, c.get_client()));

	c.get_client().set_username(c.get_arg()[0]);
	c.get_client().set_realname(c.get_prefix());
	c.get_client().set_status(REGISTER);
	//Server::reply(Reply::RPL_WELCOME, c.get_client(), c.get_client().get_prefix());
}