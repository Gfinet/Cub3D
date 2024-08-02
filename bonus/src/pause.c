/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:36:42 by Gfinet            #+#    #+#             */
/*   Updated: 2024/08/02 17:30:49 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	init_pause_screen(t_cube *cube)
{
	//int		it[2];
	t_pause	*sc;

	sc = &cube->pause_sc;
	sc->title.width = WIN_WIDTH;
	sc->title.height = WIN_HEIGHT;
	// if (!new_img(cube, &sc->bg, WIN_WIDTH, WIN_HEIGHT))
	// 	return (0);
	//it[0] = -1;
	// while (++it[0] < WIN_HEIGHT)
	// {
	// 	it[1] = -1;
	// 	while (++it[1] < WIN_WIDTH)
	// 		my_mlx_pixel_put(&sc->bg, it[1], it[0], 0x00000000);
	// }
	if (!xpm_to_img(cube, &sc->bg, "./bonus/pause/bg.xpm"))
		return (0);
	if (!xpm_to_img(cube, &sc->title, "./bonus/pause/pause-cafe.xpm"))
		return (0);
	if (!xpm_to_img(cube, &sc->arrow, "./bonus/pause/arrow.xpm"))
		return (0);
	printf("load pause ok\n");
	return (1);
}

void	pause_screen(t_cube *cube)
{
	int		*pos[2];
	t_pause	*sc;

	sc = &cube->pause_sc;
	pos[0] = (int [2]){(WIN_WIDTH / 2) - 70, 240};
	pos[1] = (int [2]){(WIN_WIDTH / 2) - 70, 273};
	mlx_clear_window(cube->mlx, cube->win);
	mlx_put_image_to_window(cube->mlx, cube->win, sc->bg.img, 0, 0);
	mlx_put_image_to_window(cube->mlx, cube->win, sc->title.img,
		(WIN_WIDTH / 2) - 175, 0);
	mlx_string_put(cube->mlx, cube->win,
		(WIN_WIDTH / 2) - 40, 258, 0x00FF0000, "RESUME");
	mlx_string_put(cube->mlx, cube->win,
		(WIN_WIDTH / 2) - 40, 290, 0x00FF0000, "QUIT");
	mlx_put_image_to_window(cube->mlx, cube->win, sc->arrow.img,
		pos[sc->choice][0], pos[sc->choice][1]);
}

int	choose_pause(int keycode, t_cube *cube)
{
	mlx_mouse_show();
	if (keycode == UP || keycode == DW)
		cube->pause_sc.choice = !cube->pause_sc.choice;
	else if (cube->pause_sc.choice == 1 && keycode == ENTER)
		esc_handle(cube);
	if (keycode == ESC || (!cube->pause_sc.choice && keycode == ENTER))
	{
		cube->pause = !cube->pause;
		cube->pause_sc.choice = 0;
	}
	if (!cube->pause)
		draw_doom(cube);
	return (1);
}

void	game_over(t_cube *cube)
{
	mlx_string_put(cube->mlx, cube->win, 0, 0, 0x00FF0000, "GAME OVER");
}
