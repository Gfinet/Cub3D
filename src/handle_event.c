/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:04:25 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/13 16:42:08 by Gfinet           ###   ########.fr       */
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
	system("leaks cub3D");
	exit(0);
	return (0);
}

int	fps(t_cube	*cube)
{
	int	i;

	i = 0;
	if (!cube->player->move_h && !cube->player->move_v && !cube->player->turn)
		i = cube->frame;
	while (i < cube->frame)
	{
		update_player(cube, cube->player);
		draw_doom(cube);
		mlx_do_sync(cube->mlx);
		i++;
	}
	return (1);
}

// int key_maj(int keycode, t_cube *cube)
// {
// 	if (keycode == L_SH)
// 	{
// 		cube->player->run = 1;
// 		cube->frame = FRAME / 2;
// 	}
// 	// if (keycode == SPACE && !cube->player->jump)
// 	// 	cube->player->jump = 1;
// 	// if (cube->player->jump)
// 	// {
// 	// 	draw_doom(cube);
// 	// 	mlx_do_sync(cube->mlx);
// 	// }
// 	return (1);
// }

int	key_event(int keycode, t_cube *cube)
{
	if (keycode == ESC)
		esc_handle(cube);
	if (keycode == W)
		cube->player->move_v = 1;
	if (keycode == S)
		cube->player->move_v = -1;
	if (keycode == D)
		cube->player->move_h = -1;
	if (keycode == A)
		cube->player->move_h = 1;
	if (keycode == RIGHT || keycode == E)
		cube->player->turn = -1;
	if (keycode == LEFT || keycode == Q)
		cube->player->turn = 1;
	if (keycode == L_SH)
	{
		cube->player->run = 1;
		cube->frame = FRAME / 2;
	}
	return (1);
}

int	key_event_release(int keycode, t_cube *cube)
{
	if (keycode == W || keycode == S)
		cube->player->move_v = 0;
	if (keycode == D || keycode == A)
		cube->player->move_h = 0;
	if (keycode == Q || keycode == E || keycode == LEFT || keycode == RIGHT)
		cube->player->turn = 0;
	if (keycode == L_SH)
	{
		cube->player->run = 0;
		cube->frame = FRAME;
	}
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

// if (jump > 0.5)
// while (jump > 0 && jump <= 0.5)