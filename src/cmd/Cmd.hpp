/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 17:39:38 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
# define CMD_HPP

# include "../utils/utils.hpp"
//# include "../client/Client.hpp"
//# include "../server/Server.hpp"
# include "../server/Reply.hpp"

# include <string>
# include <vector>
# include <map>

class Server;

class Client;

class Cmd
{
	typedef	void	(*f_cmd)(const Cmd &c);
	
	public:
		Cmd(const std::string &line, Client *sender);
		~Cmd();
		
		static std::map<std::string, f_cmd>	cmds;

		void	exec(Server *server);

		Server	&get_server(void) const;
		Client	&get_client(void) const;

		const std::string				&get_prefix(void) const;
		const std::string				&get_cmd_name(void) const;
		const std::vector<std::string>	&get_arg(void) const;
		const std::string				&get_trailing(void) const;

	private:
		Server	*_server;
		Client	*_client;

		std::string					_prefix;
		std::string					_cmd_name;
		std::vector<std::string>	_arg;
		std::string					_trailing;

		Cmd();
		Cmd(const Cmd &src);
		Cmd	&operator=(const Cmd &src);

	public:
		static void	QUIT(const Cmd &c);
		static void	PASS(const Cmd &c);
		static void	NICK(const Cmd &c);
		static void	USER(const Cmd &c);
		static void	PING(const Cmd &c);
		static void	PONG(const Cmd &c);
		static void	WHOIS(const Cmd &c);
		static void	PRIVMSG(const Cmd &c);
		static void	JOIN(const Cmd &c);
		static void	PART(const Cmd &c);
		static void	OPER(const Cmd &c);
		static void	KILL(const Cmd &c);
		static void	DIE(const Cmd &c);
};

std::ostream	&operator<<(std::ostream &o, const Cmd &src);

#endif
