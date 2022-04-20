/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:22:04 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 20:32:05 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "Server.hpp"
#include <iostream>
// signal

#ifndef DEBUG
# define DEBUG	0
#endif

int	main(int ac, char **av)
{
	if (DEBUG)
		std::cout << "[DEBUG]" << std::endl;

	if (ac != 3)
	{
		std::cout << "./ircserv <port> <poassword>" << std::endl;
		return (1);
	}
	
	std::cout << av[1] << std::endl;	// debug

	//Server	server(av[1], av[2]);
	// possibly handle SIGINT
	
	// init
	
	// do things
	

	return (0);
}
