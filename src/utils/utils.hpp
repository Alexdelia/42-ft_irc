/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:34:12 by adelille          #+#    #+#             */
/*   Updated: 2022/04/23 16:40:11 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# ifndef DEBUG
#  define DEBUG	0
# endif

# define INDENT	7

# include "color.hpp"

# include <string>
# include <iostream>
# include <sstream>
# include <ctime>

int			error(const std::string &str, const int ret);
void		debug(const std::string &str);
std::string	s_debug(const std::string &str);
void		time(const int time);
std::string	s_time(const int time);

#endif
