/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:22:04 by adelille          #+#    #+#             */
/*   Updated: 2022/04/22 13:55:49 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
// signal

#ifndef DEBUG
# define DEBUG	0
#endif

int	main(int ac, char **av)
{
	if (DEBUG)
		debug("start");

	if (ac != 3)
	{
		std::cout << "./ircserv <port> <poassword>" << std::endl;
		return (1);
	}

	Server	server(av[1], av[2]);
	if (DEBUG)
		std::cerr << s_debug("[CONFIG]:") << std::endl
			<< server.get_config() << C_RESET << std::endl;

	// possibly handle SIGINT
	
	// init
	
	// do things
	

	return (0);
}
