/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 17:07:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../utils/utils.hpp"
# include "Config.hpp"
# include "../client/Client.hpp"
# include "../cmd/Cmd.hpp"

# include <map>
# include <string>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <poll.h>

class Client;

class Server
{
	typedef	void	(*f_cmd)(void);
	
	public:
		Server(const std::string &port, const std::string &password);
		~Server();

		void	process(void);

		// channel
	
		Config								&get_config(void);
		const int							&get_start_time(void) const;
		std::vector<Client *>				get_clients(void);
		const std::map<std::string, f_cmd>	&get_cmds(void) const;
	
	private:
		Config							_config;
		std::map<std::string, f_cmd>	_cmds;
		std::map<int, Client *>			_clients;	// list of clients with index
											// don't use vector because might have hole in index
		std::vector<pollfd>				_pfds;
		int								_start_time;
		int								_last_ping;
		// channel
		
		Server();
		Server(const Server &src);
		Server	&operator=(const Server &src);

		void	_accept_client(void);
		void	_ping(void);
		void	_delete_client(Client &client);
		void	_init_m_cmd(void);
		void	_handle_client_status(void);


		// display (client/channel)
};

#endif
