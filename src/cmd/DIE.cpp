/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DIE.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:59:46 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 13:16:59 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

extern bool	g_shutdown;

void	Cmd::DIE(const Cmd &c)
{
	if (!c.get_client().is_operator())
		return (Server::reply(Reply::ERR_NOPRIVILEGES, c.get_client()));
	
	c.get_server().write_all_buffers(c.get_cmd_name());
	g_shutdown = true;
}
