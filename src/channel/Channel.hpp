/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:21:44 by jraffin           #+#    #+#             */
/*   Updated: 2022/05/23 19:14:35 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <vector>

#include "Client.hpp"

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel
{
public:
	Channel(const std::string& name);

	~Channel(void);

	void	add(const Client& member, bool as_operator);
	void	del(const Client& member);

	void	send_msg(const std::string& msg);

	void	promote(const Client& member);		// set member as operator.
	void	demote(const Client& member);		// set member as regular member.
	bool	is_operator(const Client& member);

	const std::string&		get_name();
	const std::string&		get_topic();
	void					set_topic(const std::string& topic);

	const std::string		get_names();		// space separated names of the channel members, operators first (and prefixed with a @).
	size_t					get_member_count();	// number of members in this channel.

private:
	const std::string		_name;
	std::string				_topic;
	std::vector<Client *>	_operators;
	std::vector<Client *>	_members;

	Channel(void);
	Channel(Channel const &instance);
	Channel &operator=(const Channel& rhs);
};


#endif
