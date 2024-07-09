/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:53 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/09 16:09:35 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(t_cube *cube, double angle, int frame)
{
	double	n_x;
	double	n_y;
	double rad = (90) * (M_PI / 180.0);

	(void)angle;
	cube->player->prev_pos = (t_point){cube->player->pos.x, cube->player->pos.y};
	n_x = (cube->player->dir.x * cos(-rad)) - (cube->player->dir.y) * sin(-rad);
	n_y = cube->player->dir.x * sin(-rad) + (cube->player->dir.y) * cos(-rad);
	cube->player->pos.y += (n_y / (4 * frame));
	cube->player->pos.x += (n_x / (4 * frame));
}
void	move_right(t_cube *cube, double angle, int frame)
{
	double	n_x;
	double	n_y;
	double rad = (90) * (M_PI / 180.0);

	(void)angle;
	cube->player->prev_pos = (t_point){cube->player->pos.x, cube->player->pos.y};
	n_x = (cube->player->dir.x * cos(-rad)) - (cube->player->dir.y) * sin(-rad);
	n_y = cube->player->dir.x * sin(-rad) + (cube->player->dir.y) * cos(-rad);
	cube->player->pos.y -= (n_y / (4 * frame));
	cube->player->pos.x -= (n_x / (4 * frame));
}
void	move_up(t_cube *cube, double angle, int frame)
{
	(void)angle;
	cube->player->prev_pos = (t_point){cube->player->pos.x, cube->player->pos.y};
	cube->player->pos.y += (cube->player->dir.y / (4 * frame));
	cube->player->pos.x += (cube->player->dir.x / (4 * frame));
	// draw_doom(cube);
	// usleep(100000);
	// cube->player->pos.y += (cube->player->dir.y / 8);
	// cube->player->pos.x += (cube->player->dir.x / 8);
}
void	move_down(t_cube *cube, double angle, int frame)
{
	(void)angle;
	cube->player->prev_pos = (t_point){cube->player->pos.x, cube->player->pos.y};
	cube->player->pos.y -= (cube->player->dir.y / (4 * frame));
	cube->player->pos.x -= (cube->player->dir.x / (4 * frame));
	// draw_doom(cube);
	// usleep(100000);
	// cube->player->pos.y -= (cube->player->dir.y / 8);
	// cube->player->pos.x -= (cube->player->dir.x / 8);
}

void	turn(t_cube *cube, double angle, int frame)
{
	double	n_x;
	double	n_y;
	double rad = (angle / frame) * (M_PI / 180.0);

	// printf("dir.y = %f; dir.x = %f\n", cube->player->dir.y, cube->player->dir.x);
	n_x = (cube->player->dir.x * cos(-rad)) - (cube->player->dir.y) * sin(-rad);
	n_y = cube->player->dir.x * sin(-rad) + (cube->player->dir.y) * cos(-rad);
	cube->player->dir.y = n_y;
	cube->player->dir.x = n_x;
	// printf("new >>> dir.y = %f; dir.x = %f\n", cube->player->dir.y, cube->player->dir.x);
}