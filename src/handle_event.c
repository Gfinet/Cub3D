/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:04:25 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/09 18:21:07 by lvodak           ###   ########.fr       */
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

void fps(t_cube	*cube, double angle, int fps, void (*f)(t_cube *, double, int))
{
	int	i;

	i = 0;
	while (i < fps)
	{
		f(cube, angle, fps);
		draw_doom(cube);
		mlx_do_sync(cube->mlx);
		// usleep(10000 / fps);
		i++;
	}
}

int key_maj(int keycode, t_cube *cube)
{
	static int on = 0;
	if (keycode == L_SH)
		on = !on;
	if (on)
		cube->frame = FRAME / 2;
	else
		cube->frame = FRAME;
	// if (keycode == SPACE && !cube->player->jump)
	// 	cube->player->jump = 1;
	// if (cube->player->jump)
	// {
	// 	draw_doom(cube);
	// 	mlx_do_sync(cube->mlx);
	// }
	return (1);
}

int	key_event(int keycode, t_cube *cube)
{
	int pressed;

	pressed = 0;
	// printf("key = %d\n", keycode);
	if (keycode == ESC)
		esc_handle(cube);
	if (keycode == W && is_not_wall(cube, W))
		fps(cube, 11.25, cube->frame, &move_up);
	if (keycode == S && is_not_wall(cube, S))
		fps(cube, 11.25, cube->frame, &move_down);
	if (keycode == A && is_not_wall(cube, A))
		fps(cube, 11.25, cube->frame, &move_left);
	if (keycode == D && is_not_wall(cube, D))
		fps(cube, 11.25, cube->frame, &move_right);
	if (keycode == LEFT || keycode == Q)
		fps(cube, 11.25, cube->frame, &turn);
	if (keycode == RIGHT || keycode == E)
		fps(cube, -11.25, cube->frame, &turn);
	// printf("cube->frame = %i\n", cube->frame);
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

// if (jump > 0.5)
// while (jump > 0 && jump <= 0.5)