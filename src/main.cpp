/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:22:04 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 15:28:55 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
// signal

int	main(int ac, char *av)
{
	if (ac != 3)
		std::cout << "./ircserv <port> <poassword>" << std::endl; return (1);

	Server	server;
	// possibly handle SIGINT
	
	// set port
	// set password
	
	// init
	
	// do things
	

	return (0);
}
