/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 13:49:55 by adelille         ###   ########.fr       */
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
		
		std::string					cmd;
		std::vector<std::string>	arg;
		std::string					prefix;

		Server	&get_server(void) const;
		Client	&get_client(void) const;
	
	private:
		Server	*_server;
		Client	*_client;

		Cmd();	
		Cmd(const Cmd &src);	
		Cmd	&operator=(const Cmd &src);
};

std::ostream	&operator<<(std::ostream &o, const Cmd &src);

#endif
