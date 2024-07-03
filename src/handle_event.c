/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:04:25 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/03 23:52:14 by gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_handle(t_cube *cube)
{
	if (cube->win)
	{
		mlx_clear_window(cube->mlx, cube->win);
		mlx_destroy_window(cube->mlx, cube->win);
	}
	exit(0);
	return (0);
}

void	move_up(t_cube *cube)
{
		printf("pos.y = %f; pos.x = %f\n", cube->player->pos.y, cube->player->pos.x);
	cube->player->pos.y += (cube->player->dir.y / 4);
	cube->player->pos.x += (cube->player->dir.x / 4);
	printf("new >>> pos.y = %f; pos.x = %f\n", cube->player->pos.y, cube->player->pos.x);
}
void	move_down(t_cube *cube)
{
	printf("pos.y = %f; pos.x = %f\n", cube->player->pos.y, cube->player->pos.x);
	cube->player->pos.y -= (cube->player->dir.y / 4);
	cube->player->pos.x -= (cube->player->dir.x / 4);
	printf("new >>> pos.y = %f; pos.x = %f\n", cube->player->pos.y, cube->player->pos.x);
}

void	turn(t_cube *cube, double angle)
{
	double	n_x;
	double	n_y;
	double rad = angle * (M_PI / 180.0);

	printf("dir.y = %f; dir.x = %f\n", cube->player->dir.y, cube->player->dir.x);
	n_x = (cube->player->dir.x * cos(-rad)) - (cube->player->dir.y) * sin(-rad);
	n_y = cube->player->dir.x * sin(-rad) + (cube->player->dir.y) * cos(-rad);
	cube->player->dir.y = n_y;
	cube->player->dir.x = n_x;
	printf("new >>> dir.y = %f; dir.x = %f\n", cube->player->dir.y, cube->player->dir.x);
}

int	key_event(int keycode, t_cube *cube)
{
	printf("key = %d\n", keycode);
	if (keycode == ESC)
		esc_handle(cube);
	else if ((keycode >= 0 && keycode <= 2) || keycode == 13)
	{
		if (keycode == W)
			move_up(cube);
		if (keycode == S)
			move_down(cube);
		if (keycode == A)
			turn(cube, 11.25);
		if (keycode == D)
			turn(cube, -11.25);
	}
	draw_doom(cube);
	return (1);
}

int	mouse_event(int mcode, int x, int y, t_cube *cube)
{
	printf("%d %d %d %p\n", mcode, x, y, cube);
	return (0);
}

//void scroll_event(double xdelta, double ydelta, t_cube *cube)
// {
// 	// y : "puissance du scroll"
// 	// x : swipe vers gauche/droite ?
// 	t_cube *cube;

// 	cube = param;
// 	printf("x : %f, y : %f\n", xdelta, ydelta);
// }

// void add_event(t_cube *cube)
// {
// 	t_cube *cube;

// 	cube = param;
// 	printf("add_event\n");
// }