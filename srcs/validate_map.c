/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:42:37 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/22 08:54:54 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**  Crawl Map to find a valid path from begin to end
**  Mark Rooms as they are checked.
*/

int		lm_all_crawled(t_rooms *room)
{
	t_tunnels	*tmp_tun;

	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit->marked == 0)
			return (0);
		tmp_tun = tmp_tun->next;
	}
	return (1);
}

void	lm_valid_path(t_map *maps, t_rooms *prev, t_rooms *room)
{
	t_tunnels	*tmp_tun;

	if (lm_all_crawled(room))
		return ;
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit != maps->begin)
			tmp_tun->exit->marked = 1;
		else if (tmp_tun->exit == maps->begin)
			maps->valid = 1;
		tmp_tun = tmp_tun->next;
	}
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit != prev)
			lm_valid_path(maps, room, tmp_tun->exit);
		tmp_tun = tmp_tun->next;
	}
}
