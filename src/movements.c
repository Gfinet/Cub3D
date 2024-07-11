/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:08:53 by lvodak            #+#    #+#             */
/*   Updated: 2024/07/11 22:03:35 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_player(t_cube *cube, t_player *player)
{
	t_point	new_pos;

	player->prev_pos = (t_point){player->pos.x, player->pos.y};
	new_pos.x = player->pos.x + player->move_v * (player->dir.x / (4 * cube->frame));
	new_pos.y = player->pos.x + player->move_v * (player->dir.x / (4 * cube->frame));
	new_pos.x += player->move_h * cos(player->dir.x);
	new_pos.y += player->move_h * sin(player->dir.y);
	if (player->turn)
		turn(cube, 11.25 * player->turn, cube->frame);
	printf("player pos [%f;%f]\n", cube->player->pos.y, cube->player->pos.x);		
	cube->player->pos.x = new_pos.x;
	cube->player->pos.y = new_pos.y;
	printf("player pos [%f;%f]\n", cube->player->pos.y, cube->player->pos.x);	
}

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