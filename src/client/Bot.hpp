/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/06/16 14:06:26 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <exception>
# include "Client.hpp"

class Bot : public Client
{
	class PipeErrorException : std::exception { virtual const char* what() const throw() { return "Bot(): PipeErrorException"; } };

	public:
		Bot(const std::string &name) throw (PipeErrorException);
		virtual ~Bot();

		virtual ssize_t	send_buffer(void);
		virtual void	receive(Server *server);

	private:
		int	_pipe_fd;

		Bot();
		Bot(const Bot &src);
		Bot	&operator=(const Bot &src);
};

#endif
