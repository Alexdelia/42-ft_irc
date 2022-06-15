/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 18:02:39 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../utils/utils.hpp"
# include "Config.hpp"
# include "../client/Client.hpp"
# include "../channel/Channel.hpp"
# include "../cmd/Cmd.hpp"
# include "Reply.hpp"

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
	public:
		Server(const std::string &port, const std::string &password);
		~Server();

		void		process(void);

		void		add_client(Client* client);

		typedef	const std::string	(*f_reply)(const std::vector<std::string> &av);
		static std::map<std::string, f_reply>	replies;
		static void		reply(const std::string &code, Client &c);
		static void		reply(const std::string &code, Client &c, const std::string &av);
		static void		reply(const std::string &code, Client &c, const std::vector<std::string> &av);
		static void		reply(const std::string &code, Client &c, Client &dst, const std::vector<std::string> &av);
		static const std::string	get_custom_reply(const std::string &code, const std::vector<std::string> &av);

		Channel*					get_channel(const std::string& chan_name);
		void						join_channel(const std::string& chan_name, Client& client);
		void						leave_channel(const std::string& chan_name, Client& client);

		void						bind_nick(const std::string &nickname, Client *client);
		void						unbind_nick(const std::string &nickname);
		bool						nick_exists(const std::string &nickname);

		void						write_all_buffers(const std::string &msg);

		Config								&get_config(void);
		const int							&get_start_time(void) const;
		std::map<int, Client *>				&get_clients(void);
		Client								*get_client(const std::string &nickname);
		std::map<std::string, std::string>	&get_oper_login(void);

	private:
		Config								_config;
		std::map<std::string, std::string>	_oper_login;
		std::map<int, Client *>				_clients;	// list of clients by fd
		std::map<std::string, Client *>		_clients_by_nick;
		std::vector<pollfd>					_pfds;
		int									_start_time;
		int									_last_ping;

		std::map<std::string, Channel>		_channels;

		Server();
		Server(const Server &src);
		Server	&operator=(const Server &src);

		void	_init_m_cmd(void);
		void	_init_m_reply(void);
		void	_init_m_oper(void);

		void	_accept_client(void);
		void	_ping(void);
		void	_delete_client(Client &client);
		void	_handle_client_status(void);

		// display (client/channel)
};

#endif
