/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:12:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/09 22:26:15 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_side_wall(t_cube *c, t_point dir, int keycode)
{
	int	y;
	int	y0;
	int	x;
	int	x0;

	y = c->player->pos.y + (dir.y > 0) * 0.26 - (dir.y < 0) * 0.26;
	x = c->player->pos.x + (dir.x > 0) * 0.26 - (dir.x < 0) * 0.26;
	y0 = c->player->pos.y;
	x0 = c->player->pos.x;
	if ((keycode == W || keycode == A) && c->lvl->c_maps[y0][x] == '1'
		&& c->lvl->c_maps[y][x0] == '1')
		return (1);
	y = c->player->pos.y + (-1 * dir.y > 0) * 0.26 - (-1 * dir.y < 0) * 0.26;
	x = c->player->pos.x + (-1 * dir.x > 0) * 0.26 - (-1 * dir.x < 0) * 0.26;
	if ((keycode == S || keycode == D) && c->lvl->c_maps[y0][x] == '1'
		&& c->lvl->c_maps[y][x0] == '1')
		return (1);
	return (0);
}

int	check_front_wall(t_cube *c, t_point dir, int key)
{
	double	yp;
	double	ym;
	double	xm;
	double	xp;

	yp = (c->player->pos.y + dir.y);
	xp = (c->player->pos.x + dir.x);
	ym = (c->player->pos.y - dir.y);
	xm = c->player->pos.x - dir.x;
	if ((key == W || key == A) && ((c->lvl->c_maps[(int)yp][(int)xp] == '1')
		|| (c->lvl->c_maps[(int)(yp - dir.y / 2)][(int)(xp - dir.x / 2)]
		== '1')))
		return (1);
	else if ((key == S || key == D) && ((c->lvl->c_maps[(int)ym][(int)xm]
			== '1') || (c->lvl->c_maps[(int)(ym + dir.y / 2)][(int)(xm + dir.x
		/ 2)] == '1')))
		return (1);
	return (0);
}

int	is_not_wall(t_cube *c, int keycode)
{
	t_point	dir;
	t_point	dir_side;
	double	n_x;
	double	n_y;
	double	rad;

	rad = (90) * (M_PI / 180.0);
	n_x = (c->player->dir.x * cos(-rad)) - (c->player->dir.y) * sin(-rad);
	n_y = c->player->dir.x * sin(-rad) + (c->player->dir.y) * cos(-rad);
	if (keycode == W || keycode == S)
		dir = (t_point){c->player->dir.x * 0.255, c->player->dir.y * 0.255};
	else
		dir = (t_point){n_x * 0.255, n_y * 0.255};
	if (keycode == W || keycode == S)
		dir_side = (t_point){n_x * 0.255, n_y * 0.255};
	else
		dir_side = (t_point){c->player->dir.x * 0.255, c->player->dir.y
			* 0.255};
	if (check_front_wall(c, dir, keycode) || check_side_wall(c, dir, keycode))
		return (0);
	return (1);
}
