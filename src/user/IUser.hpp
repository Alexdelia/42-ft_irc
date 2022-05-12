/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IUser.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraffin <jraffin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:36:01 by jraffin           #+#    #+#             */
/*   Updated: 2022/05/12 13:40:55 by jraffin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#ifndef IUSER_HPP
# define IUSER_HPP

class IUser
{
	public:
		IUser(void);
		IUser(** replace parameters **);
		IUser(IUser const &instance);
		IUser &operator=(IUser const &rhs);
		~IUser(void);

	private:
		std::string	_nickname
};

#endif
