/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/14 19:29:16 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::OPER(const Cmd &c)
{
	if (c.get_arg().size() < 2)
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client(), c.get_cmd_name()));
	if (c.get_server().get_oper_login().find(c.get_arg()[0])
			== c.get_server().get_oper_login().end())
		return (Server::reply(Reply::ERR_PASSWDMISMATCH, c.get_client()));
	
	if (c.get_server().get_oper_login()[c.get_arg()[0]] != c.get_arg()[1])
		return (Server::reply(Reply::ERR_PASSWDMISMATCH, c.get_client()));
	
	c.get_client().promote_as_op();
	return (Server::reply(Reply::RPL_YOUREOPER, c.get_client()));
}
