/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/12 12:12:13 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "../client/Client.hpp"
# include "../server/Server.hpp"

void	Cmd::PASS(const Cmd &c)
{
	if (!c.get_arg().size())
		return (debug("CMD", "PASS:\tno arg")); // need to send an error to client
	if (c.get_client().get_status() != PASSWORD)
	{
		if (DEBUG)
			std::cerr << s_debug("CMD", "PASS:\twrong status\t(")
				<< c.get_client().get_status() << ")" << ANSI::reset << std::endl;
		return ; // need to send an error to client
	}
	
	if (c.get_server().get_config().get("password") == c.get_arg()[0])
	{
		debug("CMD", "PASS:\tcorrect");
		c.get_client().set_status(REGISTER);
	}
	else
		std::cerr << ANSI::bold << ANSI::yellow << "[WARNING]:\t" << ANSI::reset
			<< ANSI::yellow << "PASS: \"" << c.get_arg()[0]
			<< "\" wrong password" << ANSI::reset << std::endl;
}
