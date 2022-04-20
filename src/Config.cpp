/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 19:50:03 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config()
{
	// open config file

	std::string	line;

	while (/*file*/)
	{
		std::string	key;

		std::getline(line, key, SEP);
	}

	// close file
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
