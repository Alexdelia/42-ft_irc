/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:05 by adelille          #+#    #+#             */
/*   Updated: 2022/04/28 16:02:58 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CMD_HPP
# define MAP_CMD_HPP

# include "Cmd.hpp"

# include <map>
# include <string>

typedef	void	(*f_cmd)(const Cmd &c);
extern std::map<std::string, f_cmd>	g_m_cmd;

void	QUIT(const Cmd &c);

#endif