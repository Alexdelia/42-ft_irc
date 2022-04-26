/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/26 20:38:18 by adelille         ###   ########.fr       */
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

class Server;

class User
{
	public:
		User(const int fd, struct sockaddr_in addr);
		~User();

		void	set_status(const int status);

		int		get_fd(void) const;
		int		get_status(void) const;
	
	private:
		int			_fd;
		int			_status;

		std::string	_buffer_send;

		// name
		// addr

		// command
		
		User();	
		User	&operator=(const User &src);

		void	write_buffer(const std::string &str);
		void	send_buffer(void);
};

#endif
