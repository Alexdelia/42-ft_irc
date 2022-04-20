/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 20:03:03 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config()
{
	std::ifstream	ifs(FILE, std::ifstream::in);
	
	if (!ifs.good())
		exit(error("ifstream config file", 1));

	std::stringstream	line;

	while (!ifs.eof())
	{
		std::getline(ifs, line);

		std::string	key;
		std::string	val;

		std::getline(line, key, SEP);
		std::getline(line, val, '');

		m[key] = val;
	}

	ifs(close);
}

Config::~Config() {}

void	Config::set(const std::string &key, const std::string &val)
{
	m[key] = val;
}

const std::string	&Config::get(const std::string &key) const
{
	return (m[key]);
}
