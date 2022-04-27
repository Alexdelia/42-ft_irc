/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/27 14:46:26 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ostream>

# include "../utils/utils.hpp"

# define SEP	'='
# define FILE	"config/default.conf"
//# define FILE	"config/faulty.conf"

class Config
{
	public:
		Config();
		~Config();

		const std::map<std::string, std::string>	&get_map(void) const;

		void				set(const std::string &key, const std::string &val);
		const std::string	&get(const std::string &key);

	private:
		std::map<std::string, std::string>	_m;
	
		Config	&operator=(const Config &src);
		Config(const Config &src);
};

std::ostream	&operator<<(std::ostream &o, const Config &src);

#endif
