/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:04:24 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 13:47:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cmd.hpp"

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

Cmd::Cmd(const std::string &line, Server *server, User *user):
	prefix(""), _server(server), _user(user)
{

	std::vector<std::string>			e = ft_split(line + " ", " ");

	this->cmd = *e.begin();
	e.erase(e.begin());

	while (!e.empty())
	{
		if ((*e.begin())[0] == ':')
			this->prefix = std::string(&(*e.begin())[1]);
		else
			this->arg.push_back((*e.begin()));
		e.erase(e.begin());
	}

	// possibly fully wrong
	std::cout << ANSI::reset << ANSI::bold << "[  CMD  ]:\t" << ANSI::reset << (*this) << std::endl;
}

Cmd::~Cmd()
{
	debug("CMD", "done");
}

std::ostream	&operator<<(std::ostream &o, const Cmd &src)
{
	if (src.prefix.length())
		o << ANSI::prefix << ':' << src.prefix << ANSI::reset << ' ';
	
	o << ANSI::cmd << src.cmd << ANSI::reset;

	std::vector<std::string>			cpy = src.arg;
	std::vector<std::string>::iterator	i = cpy.begin();

	while (i != cpy.end())
	{
		o << ' ' << ANSI::arg << *i << ANSI::reset;
		++i;
	}

	return (o);
}

User	&Cmd::get_user(void) const
{ return (*this->_user); }
Server	&Cmd::get_server(void) const
{ return (*this->_server); }
