/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:04:25 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/24 23:29:14 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
	int			i;
	t_player	*p;
	t_door		*d;

	i = 0;
	p = cube->player;
	d = find_door(cube, p->pos.x + p->dir.x, p->pos.y + p->dir.y);
	if (!cube->player->move_h && !cube->player->move_v && !cube->player->turn)
		i = cube->frame;
	if (d && d->on_going)
	{
		draw_doom(cube);
		mlx_do_sync(cube->mlx);
	}
	while (i < cube->frame)
	{
		update_player(cube, cube->player);
		draw_doom(cube);
		mlx_do_sync(cube->mlx);
		i++;
	}
	if (cube->mouse)
	{
		cube->mouse = 0;
		cube->player->turn = 0;
	}
	return (1);
}

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
	if (keycode == F)
		find_and_open_door(cube->doors, cube->player);
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
	if (keycode == F)
		find_and_open_door(cube->doors, cube->player);
	return (1);
}

int	mouse_event(int x, int y, t_cube *cube)
{
	cube->mouse = 1;
	(void)y;
	mlx_mouse_hide();
	mlx_mouse_move(cube->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if (x >= WIN_WIDTH * 0.49 && x <= WIN_WIDTH * 0.51)
		cube->player->turn = 0;
	if (x < WIN_WIDTH * 0.49)
		cube->player->turn = 1;
	if (x > WIN_WIDTH * 0.51)
		cube->player->turn = -1;
	mlx_mouse_move(cube->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
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