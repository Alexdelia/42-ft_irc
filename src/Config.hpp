/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 19:44:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

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
		const std::string	&get(const std::string &key) const;

	private:
		std::map<std::string, std::string>	m;
};

#endif
