/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_tolower.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:21:17 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 19:33:54 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

const std::string	irc_tolower(const std::string &str)
{
	std::string	res(str);

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (res[i] >= 'A' && res[i] <= ']')
			res[i] = str[i] + 32;
	}
	return (res);
}
