/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/06/14 15:36:14 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cmd.hpp"
#include "../../client/Client.hpp"

void	Cmd::QUIT(const Cmd &c)
{
	// might set delete reason
	c.get_client().set_status(DELETE);
	c.get_server().write_all_buffers(std::string(":" + c.get_client().get_prefix()
		+ " " + c.get_cmd_name() + ))
}
