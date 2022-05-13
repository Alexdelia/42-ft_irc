/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:22:04 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 13:59:42 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.hpp"
#include "server/Server.hpp"

#include <iostream>
#include <csignal>

bool	g_shutdown = false;

static void	shutdown(int)
{
	g_shutdown = true;
}

int	main(int ac, char **av)
{
	debug("start");

	if (ac != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}

	signal(SIGINT, shutdown);

	Server	server(av[1], av[2]);
	if (DEBUG)
		std::cerr << s_debug("CONFIG", "") << std::endl
			<< server.get_config() << ANSI::reset;

	std::cout << ANSI::bold << "launched" << ANSI::reset << std::endl;

	while (!g_shutdown)
	{
		server.process();
		if (DEBUG)
			std::cerr << s_debug("")
				<< s_time(std::time(NULL) - server.get_start_time())
				<< ANSI::red << "\tloop" << ANSI::reset << std::endl;
	}
	
	std::cout << std::endl << ANSI::bold << "shutdown" << ANSI::reset << std::endl;

	return (0);
}
