/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:30:51 by adelille          #+#    #+#             */
/*   Updated: 2022/04/26 23:07:15 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int	error(const std::string &str, const int ret)
{
	std::cerr << C_RED << C_BOLD << "ERROR:\t" << C_RESET << C_RED
		<< str << C_RESET << std::endl;
	return (ret);
}

void	error(const std::string &str)
{
	std::cerr << C_RED << C_BOLD << "ERROR:\t" << C_RESET << C_RED
		<< str << C_RESET << std::endl;
}
