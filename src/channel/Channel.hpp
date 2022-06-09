/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:21:44 by jraffin           #+#    #+#             */
/*   Updated: 2022/06/09 18:42:55 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <set>
#include <functional>

#include "../client/Client.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel
{
	class MemberCompare : public std::binary_function<Client*, Client*, bool>
	{
		bool	operator()(Client* cl1, Client* cl2)
		{
			return cl1->get_nickname() < cl2->get_nickname();
		}
	};

public:
	Channel();
	Channel(Channel const &instance);
	~Channel(void);
	Channel&	operator=(const Channel& rhs);

	void	add(Client& member, bool as_operator);
	void	del(Client& member);

	void	send_msg(const std::string& msg) const;

	void	promote(Client& member);		// set member as operator.
	void	demote(Client& member);			// set member as regular member.
	bool	is_operator(Client& client) const;
	bool	is_member(Client& client) const;

	const std::string&		get_topic() const;
	void					set_topic(const std::string& topic);

	const std::string		get_names() const;	// space separated names of the channel members, operators first (and prefixed with a @).
	size_t					get_count() const;	// number of members in this channel.

private:
	std::string				_topic;
	std::set<Client*>		_operators;
	std::set<Client*>		_members;
};

#endif
