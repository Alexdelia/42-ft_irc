/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:23:23 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 20:31:18 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

void	ft_prgb(const std::string &str, const int r, const int g, const int b)
{
	std::cout << "\033[38;2;" << r << ';' << g << ';' << b << ';' << 'm'
		<< str << "\033[0m" << std::endl;
}
