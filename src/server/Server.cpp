/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/04/26 20:01:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

Server::Server(const std::string &port, const std::string &password):
	_start_time(std::time(NULL)), _last_ping(std::time(NULL))
{
	if (DEBUG)
		debug("[SERVER]:\tstart");
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

	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = this->_fd;
	this->_pfds.back().events = POLLIN;

	if (DEBUG)
		debug("[SERVER]:\tcreated");
}

Server::~Server()
{
	{
		if (DEBUG)
			debug("[SERVER]:\tdelete all user:");

		std::vector<User *>				users = get_users();
		std::vector<User *>::iterator	i = users.begin();

		while (i != users.end())
		{
			delete_user(*(*i));
			++i;
		}
	}

	if (DEBUG)
		debug("[SERVER]:\tdeleted");
}

void	Server::process(void)
{
	// load user

	if (poll(&this->_pfds[0], this->_pfds.size(),
				atoi(get_config().get("timeout").c_str())) == -1)
		return ;	// timeout

	if (std::time(NULL) - this->_last_ping >= atoi(get_config().get("ping").c_str()))
	{
		if (DEBUG)
			std::cerr << s_debug("[PING]:\t")
				<< s_time(std::time(NULL) - this->_start_time) << std::endl;

		// send ping
		this->_last_ping = std::time(NULL);

		if (DEBUG)
			std::cerr << s_debug("[PONG]:\t")
				<< s_time(std::time(NULL) - this->_start_time) << std::endl;
	}
	else
	{
		if (this->_pfds[0].revents == POLLIN)
			accept_user();
		else
			sleep(2); //
	}

	// delete users that need to be deleted

	// update user
	// send message to rest of user

	// might display user on server

	if (DEBUG)
		debug("[SERVER]:\tprocessed");
}

void	Server::accept_user(void)
{
	// protection if max user

	struct sockaddr_in	addr;
	socklen_t			addr_len;
	int					fd;

	addr_len = sizeof(addr);
	fd = accept(this->_fd, (struct sockaddr *)&addr, &addr_len);
	if (fd == -1)
	{
		error("accept", 0);
		return ;
	}

	this->_users[fd] = new User(fd, addr);

	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = fd;
	this->_pfds.back().events = POLLIN;

	if (DEBUG)
		std::cerr << s_debug("[SERVER]:\tnew user:\t| ") << fd << "\t| "
			<< inet_ntoa(addr.sin_addr) << "\t| " << ntohs(addr.sin_port)
			<< C_RESET << std::endl;
}

void	Server::delete_user(User &user)
{
	// channel handle

	// might update fd that is writen on
	// still don't know which way to do that
	// and if will do it at all

	{
		std::vector<pollfd>::iterator	i = this->_pfds.begin();

		while (i != this->_pfds.end() && (*i).fd != user.get_fd())
			++i;
		if ((*i).fd == user.get_fd())
		{
			this->_pfds.erase(i);
			if (DEBUG)
				std::cerr << s_debug("[SERVER]:\tpfds |") << (*i).fd << "| erased"
					<< C_RESET << std::endl;
		}
	}

	this->_users.erase(user.get_fd());
	delete	&user;

	// quit message to remaining user
}

Config	&Server::get_config(void)
{ return (this->_config); }

int		Server::get_start_time(void) const
{ return (this->_start_time); }

std::vector<User *>	Server::get_users(void)
{
	std::vector<User *>	users;

	std::map<size_t, User *>::iterator i = this->_users.begin();

	while (i != this->_users.end())
	{
		users.push_back(i->second);
		i++;
	}

	return (users);
}
