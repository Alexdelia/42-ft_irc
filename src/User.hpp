/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/04/24 11:59:28 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include "utils/utils.hpp"

# include <map>
# include <string>
# include <vector>
# include <netinet/in.h>

# define DELETE		0

class Server;

class User
{
	public:
		User(const int fd, struct sockaddr_in addr);
		~User();
	
		User	&operator=(const User &src);

		// send
	
		// set

		// get
	
	private:
		int		_fd;
		int		_status;

		// name
		// addr


		User();
};

#endif
