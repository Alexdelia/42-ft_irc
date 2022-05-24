/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PONG.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/17 19:43:42 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "../client/Client.hpp"
# include "../server/Server.hpp"

void	Cmd::PONG(const Cmd &c)
{
	if (!c.get_prefix().size())
		return (Server::reply(ERR_NOORIGIN, c.get_client()));

	c.get_client().set_last_ping(std::time(NULL));
}