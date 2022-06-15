/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 17:25:14 by adelille         ###   ########.fr       */
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
	if (c.get_trailing().size())
		msg_to_all += " " + c.get_trailing();
	c.get_server().write_all_buffers(msg_to_all);
}
