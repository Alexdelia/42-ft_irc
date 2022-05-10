/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/10 16:05:48 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "../utils/utils.hpp"
# include "../cmd/Cmd.hpp"
# include "../cmd/map_cmd.hpp"

# include <map>
# include <string>
# include <vector>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>

# define INIT		-1
# define DELETE		0
# define ONLINE		1
# define PASSWORD	2
# define REGISTER	3

# define BUFFER_SIZE	2048	// apparently, max length is 512

class Server;

class Client
{
	public:
		Client(const int fd, struct sockaddr_in addr);
		~Client();

		void	write_buffer(const std::string &str);
		ssize_t	send_buffer(void);
		void	receive(Server *server);

		void	set_status(const int status);
		void	set_last_ping(const int last_ping);

		int		get_fd(void) const;
		int		get_status(void) const;
		int		get_last_ping(void) const;
	
	private:
		int			_fd;
		int			_status;
		int			_last_ping;

		std::string	_buffer_to_send;

		// name
		// addr

		// command
		
		Client();	
		Client(const Client &src);	
		Client	&operator=(const Client &src);
};

#endif