/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/23 16:17:08 by adelille         ###   ########.fr       */
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

	if (atoi(this->_m["timeout"].c_str()) <= 0)
		this->_m["timeout"] = "5000";			// timeout of 5s
	if (atoi(this->_m["ping"].c_str()) <= 0)
		this->_m["ping"] = "60";				// ping of 1min
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
		o << "\t\t\t" << i->first << "=" << i->second << std::endl;

	return (o);
}

