/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:52:44 by adelille          #+#    #+#             */
/*   Updated: 2022/06/15 20:02:35 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Reply.hpp"

void	Server::reply(const std::string &code, Client &c, Client &dst, const std::vector<std::string> &av)
{
	int	tmp = atoi(code.c_str());
	if (tmp <= 0 || tmp > 502)
		return (debug("SERVER", "you dumbass, you use an illegal reply number"));

	if (DEBUG)
		std::cerr << s_debug("REPLY", "") << ANSI::reply << '(' << code << ") "
			<< ANSI::reset << ANSI::red << c << ANSI::reset << std::endl;

	std::string	to;
	if (c.get_status() == ONLINE)
		to = c.get_nickname();
	else
		to = "*";
	c.write_to(dst, code + " " + to + Server::get_custom_reply(code, av));
}

void	Server::reply(const std::string &code, Client &c, const std::vector<std::string> &av)
{
	Server::reply(code, c, c, av);
}

void	Server::reply(const std::string &code, Client &c, const std::string &av)
{
	Server::reply(code, c, c, std::vector<std::string>(1, av));
}

void	Server::reply(const std::string &code, Client &c)
{
	std::vector<std::string>	empty;
	Server::reply(code, c, c, empty);
}

const std::string	Server::get_custom_reply(const std::string &code, const std::vector<std::string> &av)
{
	if (Server::replies.find(code) == Server::replies.end())
	{
		debug("REPLY", "custom replies not found\t(" + code + ")");
		return ("");
	}

	return (std::string(" " + Server::replies[code](av)));
}

const std::string	Reply::r_RPL_WELCOME(const std::vector<std::string> &av)
{ return (std::string(":Welcome to the Internet Relay Network " + av[0])); }

const std::string	Reply::r_RPL_NOTOPIC(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :No topic is set")); }

const std::string	Reply::r_RPL_TOPIC(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :" + av[1])); }

const std::string	Reply::r_RPL_NAMREPLY(const std::vector<std::string> &av)
{ return (std::string("= " + av[0] + " :" + av[1])); }

const std::string	Reply::r_RPL_ENDOFNAMES(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :End of NAMES list")); }

const std::string	Reply::r_RPL_YOUREOPER(const std::vector<std::string> &av)
{ return (":You are now an IRC operator"); (void)av; }

const std::string	Reply::r_ERR_NEEDMOREPARAMS(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :Not enough parameters")); }

const std::string	Reply::r_ERR_NOSUCHNICK(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :No such nick/channel")); }

const std::string	Reply::r_ERR_NOSUCHCHANNEL(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :No such channel")); }

const std::string	Reply::r_ERR_NOORIGIN(const std::vector<std::string> &av)
{ return (std::string(":No origin specified")); (void)av; }

const std::string	Reply::r_ERR_NOTONCHANNEL(const std::vector<std::string> &av)
{ return (std::string(av[0] + " :You're not on that channel")); }

const std::string	Reply::r_ERR_NORECIPIENT(const std::vector<std::string> &av)
{ return (":No recipient given (" + std::string(av[0]) + ')'); }

const std::string	Reply::r_ERR_NOTEXTTOSEND(const std::vector<std::string> &av)
{ return (":No text to send"); (void)av; }

const std::string	Reply::r_ERR_UNKNOWNCOMMAND(const std::vector<std::string> &av)
{ return (av[0] + " :Unknown command"); }

const std::string	Reply::r_ERR_ERRONEUSNICKNAME(const std::vector<std::string> &av)
{ return (av[0] + " :Erroneous nickname"); }

const std::string	Reply::r_ERR_NICKNAMEINUSE(const std::vector<std::string> &av)
{ return (av[0] + " :Nickname is already in use"); }

const std::string	Reply::r_ERR_PASSWDMISMATCH(const std::vector<std::string> &av)
{ return (":Password incorrect"); (void)av; }

const std::string	Reply::r_ERR_NOPRIVILEGES(const std::vector<std::string> &av)
{ return (":Permission Denied- You're not an IRC operator"); (void)av; }