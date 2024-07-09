/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:12:12 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/09 20:36:58 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_side_wall(t_cube *c, t_point dir, t_point dir_s, int keycode)
{
	(void)c;
	(void)dir;
	(void)dir_s;
	(void)keycode;
	// player -/+ dir_s / 4 + dir == up / right;
	// player -/+ dir_s / 4 - dir == down / left;
	// if ((keycode == S || keycode == D) && (c->maps->c_maps[(int)(c->player->pos.y -
	// 	dir_s.y - dir.y / 2)][(int)(c->player->pos.x + dir_s.x - dir.x / 2)] == '1' || (c->maps->c_maps[(int)(c->player->pos.y -
	// 	dir_s.y - dir.y / 8)][(int)(c->player->pos.x + dir_s.x - dir.x / 8)] == '1')))
	// 	return (1);
	// else if ((keycode == W || keycode == A) && (c->maps->c_maps[(int)(c->player->pos.y -
	// 	dir_s.y + dir.y / 2)][(int)(c->player->pos.x + dir_s.x + dir.x / 2)] == '1' || (c->maps->c_maps[(int)(c->player->pos.y -
	// 	dir_s.y + dir.y / 8)][(int)(c->player->pos.x + dir_s.x + dir.x / 8)] == '1')))
	// 	return (1);
	return (0);
}

int	check_front_wall(t_cube *c, t_point dir, int keycode)
{
	if ((keycode == W || keycode == A) && ((c->lvl->c_maps[(int)(c->player->pos.y + dir.y)]
		[(int)(c->player->pos.x + dir.x)] == '1') || (c->lvl->c_maps[(int)
		(c->player->pos.y + dir.y / 2)][(int)(c->player->pos.x + dir.x / 2)]
		== '1')))
		return (1);
	else if ((keycode == S || keycode == D) && ((c->lvl->c_maps[(int)(c->player->pos.y - dir.y)]
		[(int)(c->player->pos.x - dir.x)] == '1') || (c->lvl->c_maps[(int)
		(c->player->pos.y - dir.y / 2)][(int)(c->player->pos.x - dir.x / 2)]
		== '1')))
		return (1);
	return (0);
}
int	is_not_wall(t_cube *c, int keycode)
{
	t_point	dir;
	t_point	dir_side;
	double	n_x;
	double	n_y;
	double rad = (90) * (M_PI / 180.0);

	n_x = (c->player->dir.x * cos(-rad)) - (c->player->dir.y) * sin(-rad);
	n_y = c->player->dir.x * sin(-rad) + (c->player->dir.y) * cos(-rad);
	if (keycode == W || keycode == S)
		dir = (t_point){c->player->dir.x * 0.255, c->player->dir.y * 0.255};
	else
		dir = (t_point){n_x * 0.255, n_y * 0.255};
	if (keycode == W || keycode == S)
		dir_side = (t_point){n_x * 0.255, n_y * 0.255};
	else
		dir_side = (t_point){c->player->dir.x * 0.255, c->player->dir.y * 0.255};
	if (check_front_wall(c, dir, keycode) || check_side_wall(c, dir, dir_side, keycode))
		return (0);
	return (1);
}
