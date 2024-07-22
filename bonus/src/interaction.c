/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:12:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/22 19:33:45 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	find_and_open_door(t_door *door, t_player *pl)
{
	t_point	pos;

	while (door)
	{
		pos = door->coord;
		if (((int)pos.x <= (int)fmax(pl->pos.x + pl->dir.x, pl->pos.x)
			&& (int)pos.x >= (int)fmin(pl->pos.x + pl->dir.x, pl->pos.x))
			&& ((int)pos.y <= (int)fmax(pl->pos.y + pl->dir.y, pl->pos.y)
			&& (int)pos.y >= (int)fmin(pl->pos.y + pl->dir.y, pl->pos.y))
			&& !((int)pl->pos.x == (int)pos.x && (int)pl->pos.y == (int)pos.y))
		{
			if (door->open == 0)
			{
				door->open = 1;
				door->on_going = 1;
			}
			else if (door->open == 75)
			{
				door->open = 74;
				door->on_going = -1;
			}
			return ;
		}
		door = door->next;
	}
}

static int	impassable(char **map, t_cube *cb, int x, int y)
{
	t_door	*door;

	if (map[y][x] == '1' || map[y][x] == '2')
		return (1);
	if (map[y][x] == 'D')
	{
		door = find_door(cb, x, y);
		if (door->open != 75)
			return (1);
	}
	return (0);
}

int	is_not_wallz(t_cube *c, t_point n, t_player *p)
{
	double	n_x;
	double	n_y;
	double	rad;
	char	**map;

	map = c->lvl->c_maps;
	rad = (90) * (M_PI / 180.0);
	n_x = (p->dir.x * cos(-rad)) - (p->dir.y) * sin(-rad);
	n_y = p->dir.x * sin(-rad) + (p->dir.y) * cos(-rad);
	if (p->move_v
		&& (impassable(map, c, n.x + (p->move_v * 0.15 * p->dir.x), p->pos.y)
			|| impassable(map, c, p->pos.x, n.y + (p->move_v * 0.15 * p->dir.y))
			|| impassable(map, c, n.x, n.y)))
		return (0);
	if (p->move_h
		&& (impassable(map, c, n.x + (p->move_h * 0.15 * n_x), p->pos.y)
			|| impassable(map, c, p->pos.x, n.y + (p->move_h * 0.15 * n_y))
			|| impassable(map, c, n.x, n.y)))
		return (0);
	return (1);
}
