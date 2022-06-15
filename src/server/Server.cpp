/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 23:39:00 by adelille         ###   ########.fr       */
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
	_init_m_oper();

	debug("SERVER", "created");
}

Server::~Server()
{
	{
		debug("SERVER", "delete all client:");

		std::map<int, Client *>::iterator	i = get_clients().begin();

		while (i != get_clients().end())
		{
			Client	*current = i->second;
			++i;
			_delete_client(*current);
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

		std::map<int, Client *>::iterator	i = _clients.begin();
		while (i != _clients.end())
		{
			Client* current = i->second;
			++i;
			if (current->get_status() == DELETE)
				_delete_client(*current);
			else if (current->get_status() == KILLED)
			{
				current->send_buffer();
				_delete_client(*current);
			}
		}

		_handle_client_status();	// need to take care if that function change the status

		for (i = _clients.begin(); i != _clients.end(); ++i)
		{
			//(*i)->write_buffer("[DEBUG]:\they"); //
			if (i->second->send_buffer() == -1)
				i->second->set_status(DELETE);	// not sure of that approach
		}
	}

	// might display client on server
}

void	Server::add_client(Client* client)
{
	this->_clients[client->get_fd()] = client;
	this->_clients_by_nick[irc_tolower(client->get_nickname())] = client;

	this->_pfds.push_back(pollfd());
	this->_pfds.back().fd = client->get_fd();
	this->_pfds.back().events = POLLIN;
}

Config				&Server::get_config(void)
{ return (this->_config); }

const int					&Server::get_start_time(void) const
{ return (this->_start_time); }

std::map<int, Client *>	&Server::get_clients(void)
{ return (this->_clients); }

Client	*Server::get_client(const std::string &nickname)
{
	if (!nick_exists(nickname))
		return (NULL);
	return (this->_clients_by_nick[irc_tolower(nickname)]);
}

Channel*					Server::get_channel(const std::string& chan_name)
{
	std::map<std::string, Channel>::iterator	it = _channels.find(irc_tolower(chan_name));
	if (it == _channels.end())
		return NULL;
	return &it->second;
}

std::map<std::string, std::string>	&Server::get_oper_login(void)
{ return (this->_oper_login); }

void	Server::_init_m_cmd(void)
{
	Cmd::cmds["QUIT"] = Cmd::QUIT;
	Cmd::cmds["PASS"] = Cmd::PASS;
	Cmd::cmds["NICK"] = Cmd::NICK;
	Cmd::cmds["USER"] = Cmd::USER;
	Cmd::cmds["PING"] = Cmd::PING;
	Cmd::cmds["PONG"] = Cmd::PONG;
	Cmd::cmds["WHOIS"] = Cmd::WHOIS;
	Cmd::cmds["PRIVMSG"] = Cmd::PRIVMSG;
	Cmd::cmds["NOTICE"] = Cmd::PRIVMSG;
	Cmd::cmds["JOIN"] = Cmd::JOIN;
	Cmd::cmds["PART"] = Cmd::PART;
	Cmd::cmds["OPER"] = Cmd::OPER;
	Cmd::cmds["KILL"] = Cmd::KILL;
	Cmd::cmds["DIE"] = Cmd::DIE;
}

void	Server::_init_m_reply(void)
{
	Server::replies[Reply::RPL_WELCOME] = Reply::r_RPL_WELCOME;
	Server::replies[Reply::RPL_NOTOPIC] = Reply::r_RPL_NOTOPIC;
	Server::replies[Reply::RPL_TOPIC] = Reply::r_RPL_TOPIC;
	Server::replies[Reply::RPL_NAMREPLY] = Reply::r_RPL_NAMREPLY;
	Server::replies[Reply::RPL_ENDOFNAMES] = Reply::r_RPL_ENDOFNAMES;
	Server::replies[Reply::RPL_YOUREOPER] = Reply::r_RPL_YOUREOPER;

	Server::replies[Reply::ERR_NEEDMOREPARAMS] = Reply::r_ERR_NEEDMOREPARAMS;
	Server::replies[Reply::ERR_NOSUCHNICK] = Reply::r_ERR_NOSUCHNICK;
	Server::replies[Reply::ERR_NOSUCHCHANNEL] = Reply::r_ERR_NOSUCHCHANNEL;
	Server::replies[Reply::ERR_NOORIGIN] = Reply::r_ERR_NOORIGIN;
	Server::replies[Reply::ERR_NOTONCHANNEL] = Reply::r_ERR_NOTONCHANNEL;
	Server::replies[Reply::ERR_NORECIPIENT] = Reply::r_ERR_NORECIPIENT;
	Server::replies[Reply::ERR_NOTEXTTOSEND] = Reply::r_ERR_NOTEXTTOSEND;
	Server::replies[Reply::ERR_UNKNOWNCOMMAND] = Reply::r_ERR_UNKNOWNCOMMAND;
	Server::replies[Reply::ERR_ERRONEUSNICKNAME] = Reply::r_ERR_ERRONEUSNICKNAME;
	Server::replies[Reply::ERR_NICKNAMEINUSE] = Reply::r_ERR_NICKNAMEINUSE;
	Server::replies[Reply::ERR_PASSWDMISMATCH] = Reply::r_ERR_PASSWDMISMATCH;
	Server::replies[Reply::ERR_NOPRIVILEGES] = Reply::r_ERR_NOPRIVILEGES;
}

void	Server::_init_m_oper(void)
{
	std::ifstream	ifs("./config/oper.conf", std::ifstream::in);

	if (!ifs.good())
		exit(error("ifstream config file\t(oper)", 1));

	std::string	line;

	while (!ifs.eof())
	{
		std::getline(ifs, line);

		std::stringstream	ss(line);
		std::string			key;
		std::string			val;

		std::getline(ss, key, SEP);
		std::getline(ss, val, '\n');

		this->_oper_login[key] = val;
	}

	ifs.close();
}

void						Server::join_channel(const std::string& chan_name, Client& client)
{
	Channel&	chan = _channels[irc_tolower(chan_name)];
	chan.add(client, chan.is_operator(client));
}

void						Server::leave_channel(const std::string& chan_name , Client& client)
{
	std::map<std::string, Channel>::iterator	it = _channels.find(irc_tolower(chan_name));
	if (it == _channels.end())
		return;
	it->second.del(client);
	if (!it->second.get_count())
		_channels.erase(it);
}

void	Server::bind_nick(const std::string &nickname, Client *client)
{
	this->_clients_by_nick[irc_tolower(nickname)] = client;
}

void	Server::unbind_nick(const std::string &nickname)
{
	this->_clients_by_nick.erase(irc_tolower(nickname));
}

bool	Server::nick_exists(const std::string &nickname)
{
	return (this->_clients_by_nick.find(irc_tolower(nickname)) != this->_clients_by_nick.end());
}

void	Server::write_all_buffers(const std::string &msg)
{
	for (std::map<std::string, Client*>::iterator i = _clients_by_nick.begin(); i != _clients_by_nick.end(); ++i)
		i->second->write_buffer(msg);
}
