/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/09 17:00:00 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::USER(const Cmd &c)
{
	if (c.get_arg().size() < 3)
		return (Server::reply(ERR_NEEDMOREPARAMS, c.get_client(),
			std::vector<std::string>(1, c.get_cmd_name())));
	if (c.get_client().get_status() == REGISTER)
		return (Server::reply(ERR_ALREADYREGISTRED, c.get_client()));

	c.get_client().set_username(c.get_arg()[0]);
	c.get_client().set_realname(c.get_prefix());
}