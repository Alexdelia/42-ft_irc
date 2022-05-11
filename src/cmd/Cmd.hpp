/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 17:06:47 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "../utils/utils.hpp"
//# include "../client/Client.hpp"
//# include "../server/Server.hpp"

# include <string>
# include <vector>

class Server;

class Client;

class Cmd
{
	public:
		Cmd(const std::string &line, Server *server, Client *client);
		~Cmd();

		Server	&get_server(void) const;
		Client	&get_client(void) const;

		const std::string				&get_cmd(void) const;
		const std::vector<std::string>	&get_arg(void) const;
		const std::string				&get_prefix(void) const;
	
	private:
		Server	*_server;
		Client	*_client;
		
		std::string					_cmd;
		std::vector<std::string>	_arg;
		std::string					_prefix;

		Cmd();	
		Cmd(const Cmd &src);	
		Cmd	&operator=(const Cmd &src);
};

std::ostream	&operator<<(std::ostream &o, const Cmd &src);

void	QUIT(void);
void	PASS(void);
void	NICK(void);

#endif
