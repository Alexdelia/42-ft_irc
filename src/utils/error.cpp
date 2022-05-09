/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:30:51 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 12:01:40 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int	error(const std::string &str, const int ret)
{
	std::cerr << ANSI::red << ANSI::bold << "ERROR:\t" << ANSI::reset << ANSI::red
		<< str << ANSI::reset << std::endl;
	return (ret);
}

void	error(const std::string &str)
{
	std::cerr << ANSI::red << ANSI::bold << "ERROR:\t" << ANSI::reset << ANSI::red
		<< str << ANSI::reset << std::endl;
}
