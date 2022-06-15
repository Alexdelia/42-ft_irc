/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 16:07:36 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(const int fd, struct sockaddr_in addr)
	: _op(false)
	, _fd(fd)
	, _status(INIT)
	, _last_ping(std::time(NULL))
	, _nickname()
	, _username()
	, _realname()
{
	fcntl(fd, F_SETFL, O_NONBLOCK);

	this->_hostaddr = inet_ntoa(addr.sin_addr);

	{
		char	tmp[NI_MAXHOST];
		if (getnameinfo((struct sockaddr *)&addr, sizeof(addr), tmp, NI_MAXHOST,
				NULL, 0, NI_NUMERICSERV))
			error("getnameinfo");
		else
			this->_hostname = tmp;
	}

	// put right status	// might not
	//this->_status = PASSWORD;
	//this->_status = ONLINE;

	debug("CLIENT", "created");
}

Client::~Client()
{
	close(this->_fd);

	if (DEBUG)
		std::cerr << s_debug("CLIENT", "\t| ") << this->_fd << "\t| deleted"
			<< ANSI::reset << std::endl;
}

void	Client::write_buffer(const std::string &str)
{
	this->_buffer_to_send += str + "\r\n";

	if (DEBUG)
		std::cerr << s_debug("CLIENT", "_buffer_to_send += ")
			<< ANSI::italic << "\"" << str << "\"" << ANSI::reset << std::endl;
}

void	Client::write_to(Client &c, const std::string &msg)
{
	c.write_buffer(":" + this->get_prefix() + " " + msg);
}

ssize_t	Client::send_buffer(void)
{
	ssize_t	res;

	if (!this->_buffer_to_send.length())
		return (0);

	if (DEBUG)
		std::cerr << s_debug("CLIENT", "sending ...\t") << ANSI::reset;

	res = send(this->_fd, this->_buffer_to_send.c_str(),
				this->_buffer_to_send.length(), 0);
	if (res == -1)
	{
		if (DEBUG)
			std::cerr << ANSI::red << "failed" << ANSI::reset << std::endl;
		return (res);
	}

	if (DEBUG)
		std::cerr << ANSI::red << "sent" << ANSI::reset << std::endl;

	this->_buffer_to_send.clear();
	this->_last_ping = std::time(NULL);

	return (res);
}

void	Client::receive(Server *server)
{
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		res;

	res = recv(this->_fd, &buffer, BUFFER_SIZE, 0);

	if (res == -1)
	{
		debug("CLIENT", "receive == -1");
		return ;
	}
	else if (res == 0)
	{
		debug("CLIENT", "receive == 0, status = DELETE");
		this->_status = DELETE;
		return ;
	}

	buffer[res] = '\0';

	this->_buffer_receive += buffer;

	if (this->_buffer_receive.find("\n") == std::string::npos)
	{
		if (DEBUG)
			std::cerr << s_debug("CLIENT", "| ") << this->_fd
				<< "\t| receiving: " << buffer << std::endl;
		return ;
	}

	std::vector<std::string>			lines = ft_split(this->_buffer_receive, "\r\n");
	std::vector<std::string>::iterator	i = lines.begin();
	std::size_t							to_clear = 0;

	if (DEBUG)
		std::cerr << s_debug("CLIENT", "| ") << this->_fd
			<< "\t| received:" << std::endl;

	while (i != lines.end())
	{
		to_clear += i->size() + 2;

		if (*(i->end() - 1) == '\n')
			*i = i->substr(0, i->find("\n"));
		if (DEBUG)
			std::cerr << s_debug("\t\t\t") << *i << std::endl;
		const Cmd	c(*i, server, this);
		++i;
	}

	this->_buffer_receive.erase(0, to_clear);
}

std::ostream	&operator<<(std::ostream &o, const Client &src)
{
	o << "| " << src.get_fd() << "\t|";

	if (src.get_nickname().size())
		o << ' ' << src.get_nickname() << "\t|";

	return (o);
}

void	Client::set_status(const int status)
{
	if (DEBUG)
		std::cerr << s_debug("CLIENT", "set_status\t(")
			<< this->_status << " -> " << status << ')'
			<< ANSI::reset << std::endl;
	this->_status = status;
}

void	Client::set_last_ping(const int last_ping)
{ this->_last_ping = last_ping; }

void	Client::set_nickname(const std::string &nickname)
{ this->_nickname = nickname; }

void	Client::set_username(const std::string &username)
{ this->_username = username; }

void	Client::set_realname(const std::string &realname)
{ this->_realname = realname; }

int		Client::get_fd(void) const
{ return (this->_fd); }

int		Client::get_status(void) const
{ return (this->_status); }

int		Client::get_last_ping(void) const
{ return (this->_last_ping); }

const std::string	&Client::get_nickname(void) const
{ return (this->_nickname); }

const std::string	&Client::get_username(void) const
{ return (this->_username); }

const std::string	&Client::get_realname(void) const
{ return (this->_realname); }

const std::string	&Client::get_host(void) const
{
	if (!this->_hostname.size())
		return (this->_hostaddr);
	return (this->_hostname);
}

std::string	Client::get_prefix(void) const
{
	if (this->_status != ONLINE
			|| !this->get_host().length())
	{
		if (this->_nickname.size())
			return (this->_nickname);
		else
			return (std::string(""));
	}

	std::string	prefix = this->_nickname;

	if (this->_username.length())
		prefix += "!" + this->_username;
	prefix += "@" + this->get_host();

	return (prefix);
}

bool	Client::is_operator()
{
	return _op;
}

void	Client::promote_as_op()
{
	_op = true;
}
