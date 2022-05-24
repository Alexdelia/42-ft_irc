/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/17 19:45:42 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "../client/Client.hpp"
# include "../server/Server.hpp"

void	Cmd::PING(const Cmd &c)
{
	if (c.get_arg().empty() || !c.get_arg()[0].size())
		return (Server::reply(ERR_NOORIGIN, c.get_client()));

	c.get_client().write_to(c.get_client(), "PONG :" + c.get_arg()[0]);
}