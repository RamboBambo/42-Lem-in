/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 16:42:27 by kcheung           #+#    #+#             */
/*   Updated: 2017/04/22 15:07:06 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		lm_all_scored(t_rooms *room)
{
	t_tunnels	*tmp_tun;

	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit->points == 0)
			return (0);
		tmp_tun = tmp_tun->next;
	}
	return (1);
}

void	lm_calcpoints_r(t_rooms *prev, t_rooms *room, int pts)
{
	t_tunnels	*tmp_tun;

	if (lm_all_scored(room))
		return ;
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit->points == 0)
			tmp_tun->exit->points = pts;
		tmp_tun = tmp_tun->next;
	}
	tmp_tun = room->tun_list;
	while (tmp_tun)
	{
		if (tmp_tun->exit != prev)
			lm_calcpoints_r(room, tmp_tun->exit, pts - 1);
		tmp_tun = tmp_tun->next;
	}
}

void	lm_calcpoints(t_map *map)
{
	t_rooms		*temp;
	t_tunnels	*tmp_tun;

	if (!map->begin)
		lm_error("ERROR", "No starting point", *map);
	temp = map->begin;
	tmp_tun = map->begin->tun_list;
	map->begin->points = 1;
	map->end->points = map->all_count;
	map->end->marked = 1;
	while (tmp_tun)
	{
		tmp_tun->exit->points = 2;
		tmp_tun = tmp_tun->next;
	}
	lm_valid_path(map, map->end, map->end);
	if (!map->valid)
		lm_error("ERROR", "No Valid Path", *map);
	lm_calcpoints_r(map->end, map->end, map->all_count - 1);
}
