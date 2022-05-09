/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 14:17:53 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "../user/User.hpp"
# include "../server/Server.hpp"

void	PASS(const Cmd &c)
{
	if (!c.arg.size())
		return (debug("CMD", "PASS:\tno arg")); // need to send an error to client
	if (c.get_user().get_status() != PASSWORD)
	{
		if (DEBUG)
			std::cerr << s_debug("CMD", "PASS:\twrong status\t(")
				<< c.get_user().get_status() << ")" << ANSI::reset << std::endl;
		return ; // need to send an error to client
	}
	
	if (c.get_server().get_config().get("password") == c.arg[0])
	{
		debug("CMD", "PASS:\tcorrect");
		c.get_user().set_status(REGISTER);
	}
	else
		std::cerr << ANSI::bold << ANSI::yellow << "[WARNING]:\t" << ANSI::reset
			<< ANSI::yellow << "PASS: \"" << c.arg[0]
			<< "\" wrong password" << ANSI::reset << std::endl;
}