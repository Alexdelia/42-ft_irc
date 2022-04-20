/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 20:21:52 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>

# include "utils/utils.hpp"

# define SEP	'='
# define FILE	"config/default.conf"

class Config
{
	public:
		Config();
		~Config();
	
		Config	&operator=(const Config &src);

		void				set(const std::string &key, const std::string &val);
		const std::string	&get(const std::string &key);

	private:
		std::map<std::string, std::string>	_m;
};

#endif
