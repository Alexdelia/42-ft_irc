/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:30:51 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 20:29:56 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

int	error(const std::string &str, const int ret)
{
	std::cerr << C_RED << C_BOLD << "ERROR: " << C_RESET << C_RED
		<< str << C_RESET << std::endl;
	return (ret);
}
