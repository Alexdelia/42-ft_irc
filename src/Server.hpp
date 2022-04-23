/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/23 16:14:47 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "utils/utils.hpp"
// config	// map(string key, string val)
# include "Config.hpp"
// user

# include <map>
# include <string>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <fcntl.h>
# include <poll.h>

# include <unistd.h> //

class User;

class Server
{
	public:
		Server(const std::string &port, const std::string &password);
		~Server();
	
		Server	&operator=(const Server &src);

		void	process(void);

		// user
		
		// channel
	
		Config	&get_config(void);
		int		get_start_time(void) const;
	
	private:
		Config						_config;
		std::map<size_t, User *>	_users;	// list of users with index
		int							_fd;
		std::vector<pollfd>			_pfds;
		int							_start_time;
		int							_last_ping;
		// channel
		
		Server();

		// ping

		// display (user/channel)
};

#endif
