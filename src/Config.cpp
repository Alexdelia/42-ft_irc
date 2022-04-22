/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/22 14:01:56 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config()
{
	std::ifstream	ifs(FILE, std::ifstream::in);
	
	if (!ifs.good())
		exit(error("ifstream config file", 1));

	std::string	line;

	while (!ifs.eof())
	{
		std::getline(ifs, line);

		std::stringstream	ss(line);
		std::string			key;
		std::string			val;

		std::getline(ss, key, SEP);
		std::getline(ss, val, '\n');

		this->_m[key] = val;
	}

	ifs.close();
}

Config::~Config() {}

Config	&Config::operator=(const Config &src)
{
	this->_m = src._m;

	return (*this);
}

const std::map<std::string, std::string>	&Config::get_map(void) const
{ return (this->_m); }

void	Config::set(const std::string &key, const std::string &val)
{ this->_m[key] = val; }

const std::string	&Config::get(const std::string &key)
{ return (this->_m[key]); }

std::ostream	&operator<<(std::ostream &o, const Config &src)
{
	std::map<std::string, std::string>::const_iterator	i = src.get_map().begin();

	while (++i != src.get_map().end())
		o << i->first << "=" << i->second << std::endl;

	return (o);
}

