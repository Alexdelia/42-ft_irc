/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHOIS.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/18 15:03:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::WHOIS(const Cmd &c)
{
	if (!c.get_arg().size())
		return (Server::reply(ERR_NONICKNAMEGIVEN, c.get_client()));

	// need channel
}