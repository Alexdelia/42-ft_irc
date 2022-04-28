/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 16:03:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "../../utils/utils.hpp"
//# include "../User.hpp"

# include <string>
# include <vector>

class User;

class Cmd
{
	public:
		Cmd(const std::string &line, User *user);
		~Cmd();
		
		std::string					cmd;
		std::vector<std::string>	arg;
		std::string					prefix;

		User	&get_user(void) const;
	
	private:
		User	*_user;

		Cmd();	
		Cmd(const Cmd &src);	
		Cmd	&operator=(const Cmd &src);
};

std::ostream	&operator<<(std::ostream &o, const Cmd &src);

#endif
