/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:55:48 by adelille          #+#    #+#             */
/*   Updated: 2022/05/09 11:33:21 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Cmd.hpp"
# include "../client/Client.hpp"

void	QUIT(const Cmd &c)
{
	// might set delete reason
	c.get_client().set_status(DELETE);
}
