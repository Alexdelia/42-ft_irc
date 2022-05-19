/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/18 18:49:17 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "../utils/utils.hpp"
# include "../client/Client.hpp"

# include <map>
# include <string>
# include <vector>

class Client;

class Channel
{
	public:
		Channel();
		~Channel();

	private:
		Channel(const Channel &src);
		Channel	&operator=(const Channel &src);

		std::string				_name;
		// mode
		
		std::map<int, Client *>	_clients;

};

#endif
