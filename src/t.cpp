/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 19:58:02 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
//#include <fstream>
//#include <cstdlib>


int	main(void)
{
	// open config file

	std::string	file = "Hello h=World!";
	
	std::stringstream	line(file);

	std::string	key;
	
	std::getline(line, key, '=');

	std::cout << "LINE: " << line.str() << std::endl;
	std::cout << "KEY: " << key << std::endl;
	
	std::getline(line, key, '=');

	std::cout << "LINE: " << line.str() << std::endl;
	std::cout << "KEY: " << key << std::endl;

	// close file
}
