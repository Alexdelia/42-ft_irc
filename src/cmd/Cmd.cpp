/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 18:04:59 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"
#include "../server/Server.hpp"
#include <algorithm>

std::map<std::string, Cmd::f_cmd>	Cmd::cmds
	= std::map<std::string, Cmd::f_cmd>();

// https://datatracker.ietf.org/doc/html/rfc1459#section-2.3
//
// line max_len == 510	(512 - "\r\n")
//	<message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
//	<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
//	<command>  ::= <letter> { <letter> } | <number> <number> <number>
//	<SPACE>    ::= ' ' { ' ' }
//	<params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
//
//	<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
//			or NUL or CR or LF, the first of which may not be ':'>
//	<trailing> ::= <Any, possibly *empty*, sequence of octets not including
//			NUL or CR or LF>
//
//	<crlf>     ::= CR LF

Cmd::Cmd(const std::string &line, Client *sender):
	_server(NULL), _client(sender)
{

	std::vector<std::string>			e = ft_split(line + " ", " ");

	if ((*e.begin())[0] == ':')
	{
		this->_prefix = std::string(&(*e.begin())[1]);
		e.erase(e.begin());
	}

	this->_cmd_name = *e.begin();
	std::transform(this->_cmd_name.begin(), this->_cmd_name.end(), this->_cmd_name.begin(), ::toupper);
	e.erase(e.begin());

	while (!e.empty())
	{
		if ((*e.begin())[0] == ':')
		{
			this->_trailing = std::string(&(*e.begin())[1]);
			e.erase(e.begin());
			while (!e.empty())
			{
				this->_trailing += " " + std::string(&(*e.begin())[0]);
				e.erase(e.begin());
			}
		}	
		else
		{
			this->_arg.push_back((*e.begin()));
			e.erase(e.begin());
		}
	}
}

Cmd::~Cmd()
{
	debug("CMD", "done");
}

void	Cmd::exec(Server *server)
{
	this->_server = server;

	std::cout << ANSI::reset << ANSI::bold << "[  CMD  ]:\t" << ANSI::reset << (*this) << std::endl;

	if (this->cmds.count(this->_cmd_name))
		this->cmds[this->_cmd_name](*this);
	else if (this->_cmd_name != "CAP"
			&& this->_cmd_name != "MODE")
	{
		std::cerr << ANSI::bold << ANSI::yellow << "[WARNING]:\t" << ANSI::reset
			<< ANSI::yellow << "command \"" << this->_cmd_name
			<< "\" isn't supported" << ANSI::reset << std::endl;
		Server::reply(Reply::ERR_UNKNOWNCOMMAND, this->get_client(), this->get_cmd_name());
	}
}

std::ostream	&operator<<(std::ostream &o, const Cmd &src)
{
	o << ANSI::cmd << src.get_cmd_name() << ANSI::reset;

	std::vector<std::string>			cpy = src.get_arg();
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		o << ' ' << ANSI::arg << *i << ANSI::reset;
		++i;
	}
	
	if (src.get_trailing().length())
		o << ' ' << ANSI::trailing << ':' << src.get_trailing() << ANSI::reset;

	return (o);
}

Client	&Cmd::get_client(void) const
{ return (*this->_client); }
Server	&Cmd::get_server(void) const
{ return (*this->_server); }
const std::string				&Cmd::get_prefix(void) const
{ return (this->_prefix); }
const std::string				&Cmd::get_cmd_name(void) const
{ return (this->_cmd_name); }
const std::vector<std::string>	&Cmd::get_arg(void) const
{ return (this->_arg); }
const std::string				&Cmd::get_trailing(void) const
{ return (this->_trailing); }
