/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 19:19:09 by adelille          #+#    #+#             */
/*   Updated: 2022/06/09 19:28:54 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Cmd.hpp"
#include "../client/Client.hpp"
#include "../server/Server.hpp"

void	Cmd::JOIN(const Cmd &c)
{
	// channel is full

	if (c.get_arg().size() < 1)
		return (Server::reply(Reply::ERR_NEEDMOREPARAMS, c.get_client(),
			std::vector<std::string>(1, c.get_cmd_name())));
	
	std::vector<std::string>			cpy = ft_split(c.get_arg()[0], ",");
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		c.get_server().join_channel(&(*i)[1], c.get_client());
		++i;
	}
}