/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/12 13:29:06 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "../utils/utils.hpp"
//# include "../client/Client.hpp"
//# include "../server/Server.hpp"

# include <string>
# include <vector>
# include <map>

class Server;

class Client;

class Cmd
{
	typedef	void	(*f_cmd)(const Cmd &c);
	
	public:
		Cmd(const std::string &line, Server *server, Client *client);
		~Cmd();
		
		static std::map<std::string, f_cmd>	cmds;

		Server	&get_server(void) const;
		Client	&get_client(void) const;

		const std::string				&get_cmd_name(void) const;
		const std::vector<std::string>	&get_arg(void) const;
		const std::string				&get_prefix(void) const;

	private:
		Server	*_server;
		Client	*_client;

		std::string					_cmd_name;
		std::vector<std::string>	_arg;
		std::string					_prefix;

		Cmd();	
		Cmd(const Cmd &src);	
		Cmd	&operator=(const Cmd &src);

	public:
		static void	QUIT(const Cmd &c);
		static void	PASS(const Cmd &c);
		static void	NICK(const Cmd &c);
};

std::ostream	&operator<<(std::ostream &o, const Cmd &src);

#endif
