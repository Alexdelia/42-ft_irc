/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handle.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:04:36 by adelille          #+#    #+#             */
/*   Updated: 2022/05/19 13:05:36 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

void	Server::_accept_client(void)
{
	// protection if max client

	struct sockaddr_in	addr;
	socklen_t			addr_len;
	int					fd;

	addr_len = sizeof(addr);
	fd = accept(this->_pfds[0].fd, (struct sockaddr *)&addr, &addr_len);
	if (fd == -1)
	{
		error("accept");
		return ;
	}

	this->_clients[fd] = new Client(fd, addr);

	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = fd;
	this->_pfds.back().events = POLLIN;

	std::cout << s_time(std::time(NULL) - this->_start_time)
		<< ANSI::bold << "\tnew client:\t| " << fd << "\t| "
		<< inet_ntoa(addr.sin_addr) << "\t| " << ntohs(addr.sin_port)
		<< ANSI::reset << std::endl;
}

void	Server::_delete_client(Client &client)
{
	// channel handle

	// might update fd that is writen on
	// still don't know which way to do that
	// and if will do it at all

	{
		std::vector<pollfd>::iterator	i = this->_pfds.begin();

		while (i != this->_pfds.end() && i->fd != client.get_fd())
			++i;
		if (i->fd == client.get_fd())
		{
			this->_pfds.erase(i);
			if (DEBUG)
				std::cerr << s_debug("SERVER", "pfds\t| ") << i->fd << "\t| erased"
					<< ANSI::reset << std::endl;
		}
	}

	this->_clients.erase(client.get_fd());
	delete	&client;

	// quit message to remaining client
}

void	Server::_handle_client_status(void)
{
	std::vector<Client *>			clients = this->get_clients();
	std::vector<Client *>::iterator	i = clients.begin();

	while (i != clients.end())
	{
		/*if ((*i)->get_status() == PASSWORD)
			(*i)->write_buffer("PASS " + this->_config.get("password"));*/
		/*if ((*i)->get_status() == PASSWORD)
			Server::reply(ERR_PASSWDMISMATCH, *(*i));
		else */if ((*i)->get_status() == REGISTER)
		{
			if (DEBUG)
				std::cerr << s_debug("SERVER", "| ") << (*i)->get_fd()
					<< "\t|" << (*i)->get_nickname() << "\t| REGISTER ("
					<< REGISTER << ')' << ANSI::reset << std::endl;
			debug("tmp register user");
			(*i)->set_status(ONLINE);
			reply(RPL_WELCOME, *(*i), std::vector<std::string>(1, (*i)->get_prefix()));
		}
		//reply(RPL_WELCOME, *(*i));
		++i;
	}
}

