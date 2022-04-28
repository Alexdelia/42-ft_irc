/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 12:26:21 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "../utils/utils.hpp"

# include <map>
# include <string>
# include <vector>
# include <netinet/in.h>
# include <fcntl.h>
# include <unistd.h>

# define INIT		-1
# define DELETE		0
# define ONLINE		1

# define BUFFER_SIZE	2048	// apparently, max length is 512

class Server;

class User
{
	public:
		User(const int fd, struct sockaddr_in addr);
		~User();

		void	write_buffer(const std::string &str);
		ssize_t	send_buffer(void);
		void	receive(void);

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
		
		User();	
		User(const User &src);	
		User	&operator=(const User &src);

		std::vector<std::string>	_recv_split(std::string buffer);
};

#endif
