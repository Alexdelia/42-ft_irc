/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:30:51 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 14:38:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	debug(const std::string &str)
{
	if (!DEBUG)
		return ;

	std::cerr << C_RED << C_BOLD << "[ DEBUG ]:\t" << C_RESET << C_RED
		<< str << C_RESET << std::endl;
}

void	debug(const std::string &src, const std::string &str)
{
	if (!DEBUG)
		return ;
	
	std::cerr << C_RED << C_BOLD << "[ DEBUG ]:\t"
		<< C_RESET << C_SRC << C_BOLD << '[' << src << "]:"
		<< std::string((INDENT_SRC - src.length() >= 0 ?
					INDENT_SRC - src.length() : 0), ' ')
		<< C_RESET << C_RED << "\t" << str
		<< C_RESET << std::endl;
}

std::string	s_debug(const std::string &str)
{
	std::stringstream	o;

	o << C_RED << C_BOLD << "[ DEBUG ]:\t" << C_RESET << C_RED << str;

	return (o.str());
}

std::string	s_debug(const std::string &src, const std::string &str)
{
	std::stringstream	o;

	o << C_RED << C_BOLD << "[ DEBUG ]:\t"
		<< C_RESET << C_SRC << C_BOLD << '[' << src << "]:"
		<< std::string((INDENT_SRC - src.length() >= 0 ?
					INDENT_SRC - src.length() : 0), ' ')
		<< C_RESET << C_RED << "\t" << str;

	return (o.str());
}
