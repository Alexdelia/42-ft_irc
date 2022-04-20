/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/20 15:43:20 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

// config	// map(string key, string val)
// user

#include <map>
//#include <string>
//#include <vector>

class User;

class Server
{
	public:
		Server();
		~Server();
	
		Server	&operator=(const Server &src);

		// user
		
		// channel
		
		// get config
		// get uptime
	
	private:
		Config						config;
		std::map<size_t, User *>	users;	// list of users with index
		// channel
		// uptime
		// last_ping
		// fd

		// ping

		// display (user/channel)
};

#endif
