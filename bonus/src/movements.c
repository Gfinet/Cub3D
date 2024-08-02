/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:53 by lvodak            #+#    #+#             */
/*   Updated: 2024/08/02 20:25:56 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	update_player(t_cube *cb, t_player *play)
{
	t_point	n_pos;
	double	n_x;
	double	n_y;
	double	rad;

	rad = (90) * (M_PI / 180.0);
	cb->player->prev_pos = (t_point){cb->player->pos.x, cb->player->pos.y};
	n_x = (cb->player->dir.x * cos(-rad)) - (cb->player->dir.y) * sin(-rad);
	n_y = cb->player->dir.x * sin(-rad) + (cb->player->dir.y) * cos(-rad);
	n_pos.x = play->pos.x + play->move_v * (play->dir.x / (4 * cb->frame));
	n_pos.y = play->pos.y + play->move_v * (play->dir.y / (4 * cb->frame));
	n_pos.x += play->move_h * (n_x / (4 * cb->frame));
	n_pos.y += play->move_h * (n_y / (4 * cb->frame));
	if (play->turn)
		turn(cb, 11.25 * play->turn, cb->frame);
	if (!impassable(cb->lvl->c_maps, cb, n_pos.x, play->pos.y))
		play->pos.x = n_pos.x;
	if (!impassable(cb->lvl->c_maps, cb, play->pos.x, n_pos.y))
		play->pos.y = n_pos.y;
}

void	turn(t_cube *cube, double angle, int frame)
{
	double	n_x;
	double	n_y;
	double	rad;

	rad = (angle / frame) * (M_PI / 180.0);
	n_x = (cube->player->dir.x * cos(-rad)) - (cube->player->dir.y) * sin(-rad);
	n_y = cube->player->dir.x * sin(-rad) + (cube->player->dir.y) * cos(-rad);
	cube->player->dir.y = n_y;
	cube->player->dir.x = n_x;
}
