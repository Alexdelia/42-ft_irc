/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/22 13:49:50 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

Server::Server(const std::string &port, const std::string &password)
{
	if (DEBUG)
		debug("server start");
	this->get_config().set("port", port);
	this->get_config().set("password", password);

	this->_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd == 0)
		exit(error("socket", 1));
	int	enable = 1;
	if (setsockopt(this->_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)))
		exit(error("setsockopt", 1));
	if (fcntl(this->_fd, F_SETFL, O_NONBLOCK) < 0)
		exit(error("fcntl", 1));
	
	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(this->get_config().get("port").c_str()));

	if (bind(this->_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		exit(error("bind", 1));
	if (listen(this->_fd, addr.sin_port) < 0)
		exit(error("listen", 1));
}

Server::~Server() {}

Config	&Server::get_config(void)
{ return (this->_config); }
