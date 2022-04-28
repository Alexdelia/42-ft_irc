/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 13:51:58 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "../../utils/utils.hpp"
// user
// server

# include <string>
# include <vector>


class Cmd
{
	public:
		Cmd(const std::string &line);
		~Cmd();
		
		std::string					cmd;
		std::vector<std::string>	arg;
		std::string					prefix;
	
	private:

		Cmd();	
		Cmd(const Cmd &src);	
		Cmd	&operator=(const Cmd &src);
};

std::ostream	&operator<<(std::ostream &o, const Cmd &src);

#endif
