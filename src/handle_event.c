/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:04:25 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/07 23:04:59 by lvodak           ###   ########.fr       */
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
	if (keycode == L_SH)
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
	if (keycode == W)
		fps(cube, 11.25, cube->frame, &move_up);
	if (keycode == S)
		fps(cube, 11.25, cube->frame, &move_down);
	if (keycode == A)
		fps(cube, 11.25, cube->frame, &turn);
	if (keycode == D)
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