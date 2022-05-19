/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:29:35 by adelille          #+#    #+#             */
/*   Updated: 2022/05/19 12:41:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

# include "../utils/utils.hpp"

# include <map>
# include <string>
# include <vector>

# define RPL_WELCOME            "001"
# define ERR_NOORIGIN			"409"
# define ERR_NONICKNAMEGIVEN    "431"
# define ERR_NICKCOLLISION      "436"
# define ERR_NOTREGISTERED      "451"
# define ERR_NEEDMOREPARAMS     "461"
# define ERR_ALREADYREGISTRED   "462"
# define ERR_PASSWDMISMATCH     "464"

class Reply
{
	public:
		static const std::string	r_RPL_WELCOME(const std::vector<std::string> &av);

		static const std::string	r_ERR_NEEDMOREPARAMS(const std::vector<std::string> &av);
	
	private:
		Reply();
		~Reply();
		Reply(const Reply &src);
		Reply	&operator=(const Reply &src);
};

#endif
