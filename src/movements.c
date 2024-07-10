/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:53 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/10 15:14:52 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(t_cube *cube, double angle, int frame)
{
	double		n_x;
	double		n_y;
	double		rad;
	t_player	*play;

	(void)angle;
	play = cube->player;
	rad = (90) * (M_PI / 180.0);
	play->prev_pos = (t_point){play->pos.x, play->pos.y};
	n_x = (play->dir.x * cos(-rad)) - (play->dir.y) * sin(-rad);
	n_y = play->dir.x * sin(-rad) + (play->dir.y) * cos(-rad);
	play->pos.y += (n_y / (4 * frame));
	play->pos.x += (n_x / (4 * frame));
}

void	move_right(t_cube *cube, double angle, int frame)
{
	double		n_x;
	double		n_y;
	double		rad;
	t_player	*play;

	(void)angle;
	play = cube->player;
	rad = (90) * (M_PI / 180.0);
	play->prev_pos = (t_point){play->pos.x, play->pos.y};
	n_x = (play->dir.x * cos(-rad)) - (play->dir.y) * sin(-rad);
	n_y = play->dir.x * sin(-rad) + (play->dir.y) * cos(-rad);
	cube->player->pos.y -= (n_y / (4 * frame));
	cube->player->pos.x -= (n_x / (4 * frame));
}

void	move_up(t_cube *cube, double angle, int frame)
{
	t_player	*play;

	(void)angle;
	play = cube->player;
	play->prev_pos = (t_point){play->pos.x, play->pos.y};
	cube->player->pos.y += (cube->player->dir.y / (4 * frame));
	cube->player->pos.x += (cube->player->dir.x / (4 * frame));
	// draw_doom(cube);
	// usleep(100000);
	// cube->player->pos.y += (cube->player->dir.y / 8);
	// cube->player->pos.x += (cube->player->dir.x / 8);
}

void	move_down(t_cube *cube, double angle, int frame)
{
	t_player	*play;

	(void)angle;
	play = cube->player;
	play->prev_pos = (t_point){play->pos.x, play->pos.y};
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
	double	rad;
	
	rad = (angle / frame) * (M_PI / 180.0);
	// printf("dir.y = %f; dir.x = %f\n", cube->player->dir.y, cube->player->dir.x);
	n_x = (cube->player->dir.x * cos(-rad)) - (cube->player->dir.y) * sin(-rad);
	n_y = cube->player->dir.x * sin(-rad) + (cube->player->dir.y) * cos(-rad);
	cube->player->dir.y = n_y;
	cube->player->dir.x = n_x;
	// printf("new >>> dir.y = %f; dir.x = %f\n", cube->player->dir.y, cube->player->dir.x);
}