/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/06/09 17:41:54 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::map<std::string, Server::f_reply>	Server::replies
	= std::map<std::string, Server::f_reply>();

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
	_init_m_reply();

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
		_ping();
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

void	Server::_init_m_cmd(void)
{
	Cmd::cmds["QUIT"] = Cmd::QUIT;
	Cmd::cmds["PASS"] = Cmd::PASS;
	Cmd::cmds["NICK"] = Cmd::NICK;
	Cmd::cmds["USER"] = Cmd::USER;
	Cmd::cmds["PING"] = Cmd::PING;
	Cmd::cmds["PONG"] = Cmd::PONG;
	Cmd::cmds["WHOIS"] = Cmd::WHOIS;
}

void	Server::_init_m_reply(void)
{
	Server::replies[Reply::RPL_WELCOME] = Reply::r_RPL_WELCOME;

	Server::replies[Reply::ERR_NEEDMOREPARAMS] = Reply::r_ERR_NEEDMOREPARAMS;
}

Channel*					Server::channel(const std::string& chan_name)
{
	std::map<std::string, Channel>::iterator	it = _channels.find(chan_name);
	if (it == _channels.end())
		return NULL;
	return &it->second;
}

void						Server::join_channel(const std::string& chan_name, Client& client)
{
	Channel&	chan = _channels[chan_name];
	chan.add(client, !chan.get_count());
}

void						Server::leave_channel(const std::string& chan_name , Client& client)
{
	std::map<std::string, Channel>::iterator	it = _channels.find(chan_name);
	if (it == _channels.end())
		return;
	it->second.del(client);
	if (!it->second.get_count())
		_channels.erase(it);
}
