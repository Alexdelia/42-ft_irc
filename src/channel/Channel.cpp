/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:56:05 by jraffin           #+#    #+#             */
/*   Updated: 2022/06/15 14:01:03 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <algorithm>

#include "Channel.hpp"

Channel::Channel() {}

Channel::Channel(Channel const &instance)
{
	*this = instance;
}

Channel::~Channel(void) {}

Channel&	Channel::operator=(const Channel& rhs)
{
	_topic = rhs._topic;
	_operators = rhs._operators;
	_members = rhs._members;
	return *this;
}

void	Channel::add(Client& member, bool as_operator)
{
	if (!_operators.size())
		as_operator = true;
	if (as_operator)
	{
		if(_operators.insert(&member).second)
			_members.erase(&member);
	}
	else
	{
		if(_members.insert(&member).second)
			_operators.erase(&member);
	}
}

void	Channel::del(Client& member)
{
	if (_operators.erase(&member))
	{
		if (!_operators.size() && _members.size())
			add(**_members.begin(), true);
		return;
	}
	_members.erase(&member);
}

void	Channel::write_all_buffers(const std::string& msg) const
{
	for (std::set<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it)
		(*it)->write_buffer(msg);
	for (std::set<Client*>::iterator it = _members.begin(); it != _members.end(); ++it)
		(*it)->write_buffer(msg);
}

void	Channel::write_all_buffers(const std::string& msg,
		const std::string &exclude_nick) const
{
	for (std::set<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if (exclude_nick != (*it)->get_nickname())
			(*it)->write_buffer(msg);
	}
	for (std::set<Client*>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (exclude_nick != (*it)->get_nickname())
			(*it)->write_buffer(msg);
	}
}

bool	Channel::is_operator(Client& client) const
{
	return _operators.find(&client) != _operators.end();
}

bool	Channel::is_member(Client& client) const
{
	return is_operator(client) || _members.find(&client) != _members.end();
}

const std::string&		Channel::get_topic() const
{
	return _topic;
}

void					Channel::set_topic(const std::string& topic)
{
	_topic = topic;
}

const std::string		Channel::get_names() const
{
	std::string		names;

	std::set<Client*>::iterator it = _operators.begin();
	names += "@" + (*it)->get_nickname();
	for (++it; it != _operators.end(); ++it)
		names += " @" + (*it)->get_nickname();
	for (it = _members.begin(); it != _members.begin(); ++it)
		names += " " + (*it)->get_nickname();

	return names;
}

size_t					Channel::get_count() const
{
	return _operators.size() + _members.size();
}
