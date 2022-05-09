/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:30:51 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 12:00:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

static int	ft_nbrlen(const int nb)
{
	unsigned int	n;
	size_t			i;

	if (nb == 0)
		return (1);
	i = 0;
	if (nb < 0)
	{
		n = -nb;
		i++;
	}
	else
		n = nb;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	time(const int time)
{
	int	indent;
	int	size;

	size = ft_nbrlen(time);
	indent = (INDENT_TIME - size) / 2;
	if (indent < 0)
		indent = 0;

	std::cout << ANSI::time << ANSI::bold << ANSI::italic <<
		'<' << std::string(indent, ' ') << time
		<< std::string((size % 2 == 0 ? indent + 1 : indent), ' ') << '>'
		<< ANSI::reset << std::endl;
}

std::string	s_time(const int time)
{
	std::stringstream	o;
	int					indent;
	int					size;

	size = ft_nbrlen(time);
	indent = (INDENT_TIME - size) / 2;
	if (indent < 0)
		indent = 0;

	o << ANSI::time << ANSI::bold << ANSI::italic <<
		'<' << std::string(indent, ' ') << time
		<< std::string((size % 2 == 0 ? indent + 1 : indent), ' ') << '>'
		<< ANSI::reset;

	return (o.str());
}
