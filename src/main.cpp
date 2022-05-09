/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:22:04 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 10:38:09 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "server/Server.hpp"

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

	std::cout << C_TEST << "hi" << C_RESET << std::endl;

	if (ac != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}

	signal(SIGINT, shutdown);

	Server	server(av[1], av[2]);
	if (DEBUG)
		std::cerr << s_debug("CONFIG", "") << std::endl
			<< server.get_config() << C_RESET;

	std::cout << C_BOLD << "launched" << C_RESET << std::endl;

	while (!g_shutdown)
	{
		server.process();
		if (DEBUG)
			std::cerr << s_debug("")
				<< s_time(std::time(NULL) - server.get_start_time())
				<< C_RED << "\tloop" << C_RESET << std::endl;
	}
	
	std::cout << std::endl << C_BOLD << "shutdown" << C_RESET << std::endl;

	return (0);
}
