/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:30:51 by adelille          #+#    #+#             */
/*   Updated: 2022/06/14 15:43:31 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

using namespace ANSI;

void	debug(const std::string &str)
{
	if (!DEBUG)
		return ;

	std::cerr << red << bold << "[ DEBUG ]:\t" << reset << red
		<< str << reset << std::endl;
}

void	debug(const std::string &src, const std::string &str)
{
	if (!DEBUG)
		return ;
	
	std::cerr << red << bold << "[ DEBUG ]:\t"
		<< reset << ANSI::src << bold << '[' << src << "]:"
		<< std::string(((long)(INDENT_SRC - src.length()) >= 0 ?
					INDENT_SRC - src.length() : 0), ' ')
		<< reset << red << "\t" << str
		<< reset << std::endl;
}

std::string	s_debug(const std::string &str)
{
	std::stringstream	o;

	o << red << bold << "[ DEBUG ]:\t" << reset << red << str;

	return (o.str());
}

std::string	s_debug(const std::string &src, const std::string &str)
{
	std::stringstream	o;

	o << red << bold << "[ DEBUG ]:\t"
		<< reset << ANSI::src << bold << '[' << src << "]:"
		<< std::string(((long)(INDENT_SRC - src.length()) >= 0 ?
					INDENT_SRC - src.length() : 0), ' ')
		<< reset << red << "\t" << str;

	return (o.str());
}
