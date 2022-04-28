/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:42:18 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 13:47:35 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

std::vector<std::string>	ft_split(const std::string &str, const std::string &sep)
{
	std::string					cpy = str;
	std::vector<std::string>	ret;
	size_t						pos;

	pos = cpy.find(sep);
	while (pos != std::string::npos)
	{
		ret.push_back(cpy.substr(0, pos));
		cpy.erase(0, pos + sep.length());
		pos = cpy.find(sep);
	}

	return (ret);
}
