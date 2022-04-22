/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:22:04 by adelille          #+#    #+#             */
/*   Updated: 2022/04/22 14:49:19 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "Server.hpp"

#include <iostream>
#include <csignal>

#include <unistd.h> //

bool	g_shutdown = false;

static void	shutdown(int)
{
	g_shutdown = true;
}

int	main(int ac, char **av)
{
	if (DEBUG)
		debug("start");

	if (ac != 3)
	{
		std::cout << "./ircserv <port> <poassword>" << std::endl;
		return (1);
	}

	signal(SIGINT, shutdown);

	Server	server(av[1], av[2]);
	if (DEBUG)
		std::cerr << s_debug("[CONFIG]:") << std::endl
			<< server.get_config() << C_RESET;


	std::cout << C_BOLD << "launched" << C_RESET << std::endl;

	while (!g_shutdown)
	{
		sleep(5); // tmp
		if (DEBUG)
			debug("loop");
	}
	
	std::cout << std::endl << C_BOLD << "shutdown" << C_RESET << std::endl;

	return (0);
}
