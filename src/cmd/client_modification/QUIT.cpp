/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/14 15:41:32 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"
#include "../../server/Server.hpp"

void	Cmd::QUIT(const Cmd &c)
{
	c.get_client().set_status(DELETE);
	std::string	msg_to_all(":" + c.get_client().get_prefix()
		+ " " + c.get_cmd_name());
	if (c.get_prefix().size())
		msg_to_all += " " + c.get_prefix();
	c.get_server().write_all_buffers(msg_to_all);
}
