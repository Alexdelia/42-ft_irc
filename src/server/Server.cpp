/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/05/11 17:09:52 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}

Server::Server(const std::string &port, const std::string &password):
	_start_time(std::time(NULL)), _last_ping(std::time(NULL))
{
	debug("SERVER", "start");
	this->get_config().set("port", port);
	this->get_config().set("password", password);

	int	fd;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == 0)
		exit(error("socket", 1));
	int	enable = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &enable, sizeof(enable)))
		exit(error("setsockopt", 1));
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		exit(error("fcntl", 1));

	struct sockaddr_in	addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(this->get_config().get("port").c_str()));

	if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		exit(error("bind", 1));
	if (listen(fd, addr.sin_port) < 0)
		exit(error("listen", 1));

	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = fd;
	this->_pfds.back().events = POLLIN;

	_init_m_cmd();

	debug("SERVER", "created");
}

Server::~Server()
{
	{
		debug("SERVER", "delete all client:");

		std::vector<Client *>				clients = get_clients();
		std::vector<Client *>::iterator	i = clients.begin();

		while (i != clients.end())
		{
			_delete_client(*(*i));
			++i;
		}
	}

	debug("SERVER", "deleted");
}

void	Server::process(void)
{
	if (poll(&this->_pfds[0], this->_pfds.size(),
				atoi(get_config().get("timeout").c_str())) == -1)
		return (debug("poll"));

	if (std::time(NULL) - this->_last_ping >= atoi(get_config().get("ping").c_str()))
	{
		_ping();
		this->_last_ping = std::time(NULL);
	}
	else
	{
		if (this->_pfds[0].revents == POLLIN)
			_accept_client();
		else
		{
			std::vector<pollfd>::iterator	i = this->_pfds.begin();

			while (i != this->_pfds.end())
			{
				if (i->revents == POLLIN)
					this->_clients[i->fd]->receive(this);
				++i;
			}
		}
	}

	{	// delete clients that need to be deleted
		// and send buffer to all remaining clients

		std::vector<Client *>				clients = get_clients();
		std::vector<Client *>::iterator	i = clients.begin();

		while (i != clients.end())
		{
			if ((*i)->get_status() == DELETE)
				_delete_client(*(*i));
			++i;
		}

		_handle_client_status();	// need to take care if that function change the status

		clients = get_clients();
		i = clients.begin();

		while (i != clients.end())
		{
			//(*i)->write_buffer("[DEBUG]:\they"); //
			if ((*i)->send_buffer() == -1)
				(*i)->set_status(DELETE);	// not sure of that approach
			++i;
		}
	}

	// might display client on server

	debug("SERVER", "processed");
}

void	Server::_handle_client_status(void)
{
	std::vector<Client *>			clients = this->get_clients();
	std::vector<Client *>::iterator	i = clients.begin();

	while (i != clients.end())
	{
		/*if ((*i)->get_status() == PASSWORD)
			(*i)->write_buffer("PASS " + this->_config.get("password"));
		else */if ((*i)->get_status() == REGISTER)
		{
			if (DEBUG)
				std::cerr << s_debug("SERVER", "| ") << (*i)->get_fd()
					<< "\t|" << (*i)->get_nickname() << "\t| REGISTER ("
					<< REGISTER << ')' << ANSI::reset << std::endl;
		}
		++i;
	}
}

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

// ping work the wrong way
// will recode it by sending a "PING <nick>" to each client
void	Server::_ping(void)
{
	if (DEBUG)
		std::cerr << s_debug("PING", "")
			<< s_time(std::time(NULL) - this->_start_time) << std::endl;

	//const int							time = std::time(NULL);
	//const int							timeout = atoi(_config.get("ping").c_str());
	std::map<int, Client *>::iterator	i = this->_clients.begin();

	while (i != this->_clients.end())
	{
		if (DEBUG)
			std::cerr << s_debug("\t\t\t| ") << i->second->get_fd() << "\t|";
		/*if (time - (*i).second->get_last_ping() >= timeout * 2 + 1)
		  {
		// set reason of delete // to do later
		(*i).second->set_status(DELETE);
		if (DEBUG)
		std::cerr << C_BOLD << " timeout";
		}*/
		// else if
		if (i->second->get_status() == ONLINE)
		{
			int			err = 0;
			socklen_t	len = sizeof(err);

			if (getsockopt(i->second->get_fd(), SOL_SOCKET, SO_ERROR,
						&err, &len) != 0)
				exit(error("getsockopt in ping", 1));
			else if (err != 0)
			{
				if (DEBUG)
					std::cerr << " failed";
			}
			else
			{
				i->second->set_last_ping(std::time(NULL));
				if (DEBUG)
					std::cerr << ' ' << err;
			}

			/*else
			{
				// set reason of delete // to do later // maybe
				(*i).second->set_status(DELETE);
				if (DEBUG)
					std::cerr << C_BOLD << " timeout";
			}*/
		}
		if (DEBUG)
			std::cerr << ANSI::reset << std::endl;
		++i;
	}

	if (DEBUG)
		std::cerr << s_debug("PONG", "")
			<< s_time(std::time(NULL) - this->_start_time) << std::endl;
}

Config				&Server::get_config(void)
{ return (this->_config); }

const int					&Server::get_start_time(void) const
{ return (this->_start_time); }

std::vector<Client *>	Server::get_clients(void)
{
	std::vector<Client *>	clients;

	std::map<int, Client *>::iterator i = this->_clients.begin();

	while (i != this->_clients.end())
	{
		clients.push_back(i->second);
		++i;
	}

	return (clients);
}

const	std::map<std::string, Server::f_cmd>	&Server::get_cmds(void) const
{ return (this->_cmds); }

void	Server::_init_m_cmd(void)
{
	this->_cmds["QUIT"] = Cmd::QUIT;
	this->_cmds["PASS"] = PASS;
	this->_cmds["NICK"] = NICK;
}
