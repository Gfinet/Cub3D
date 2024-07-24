/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:53 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/13 18:41:04 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	update_player(t_cube *cb, t_player *play)
{
	t_point	new_pos;
	double	n_x;
	double	n_y;
	double	rad;

	rad = (90) * (M_PI / 180.0);
	cb->player->prev_pos = (t_point){cb->player->pos.x, cb->player->pos.y};
	n_x = (cb->player->dir.x * cos(-rad)) - (cb->player->dir.y) * sin(-rad);
	n_y = cb->player->dir.x * sin(-rad) + (cb->player->dir.y) * cos(-rad);
	new_pos.x = play->pos.x + play->move_v * (play->dir.x / (4 * cb->frame));
	new_pos.y = play->pos.y + play->move_v * (play->dir.y / (4 * cb->frame));
	new_pos.y += play->move_h * (n_y / (4 * cb->frame));
	new_pos.x += play->move_h * (n_x / (4 * cb->frame));
	if (play->turn)
		turn(cb, 11.25 * play->turn, cb->frame);
	if (is_not_wallz(cb, new_pos, play))
	{
		cb->player->pos.x = new_pos.x;
		cb->player->pos.y = new_pos.y;
	}
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
