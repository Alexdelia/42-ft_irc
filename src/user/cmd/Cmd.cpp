/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 13:52:07 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

Cmd::Cmd(const std::string &line)
{
	// https://datatracker.ietf.org/doc/html/rfc1459#section-2.3
	// COMMAND ARG1 ARG2 :PREFIX
	// (up to 15 ARG)

	/*size_t	pos = line.find(" ");
	this->cmd = line.substr(0, pos);
	line.erase(0, pos + 1);*/

	std::vector<std::string>	tmp = ft_split(line, " ");
}

Cmd::~Cmd()
{
	if (DEBUG)
		debug("CMD", "done");
}

std::ostream	&operator<<(std::ostream &o, const Cmd &src)
{
	return (o);
}
