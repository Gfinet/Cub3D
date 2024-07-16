/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/17 00:15:58 by Gfinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	check_format(char *file)
{
	size_t	i;

	i = 0;
	while (file && i < ft_strlen(file) && file[i] != '.')
		i++;
	if (ft_strncmp(&file[i], ".cub", 5))
		return (0);
	return (1);
}

static int	init_cube(t_cube *cube, t_player *play, t_maps *level)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
		return (0);
	cube->win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, "DOOM3D");
	if (!cube->win)
		return (0);
	cube->bg = malloc(sizeof(t_data));
	if (!cube->bg)
		return (0);
	cube->screen = malloc(sizeof(t_data));
	if (!cube->screen)
		return (free(cube->bg), 0);
	cube->bg = malloc(sizeof(t_data));
	if (!cube->bg)
		return (free(cube->bg), free(cube->screen), free(cube->texture), 0);
	cube->lvl = level;
	cube->player = play;
	return (1);
}

static int	get_textures(t_cube *cube)
{
	int		i;
	t_data	*txt;

	cube->texture = malloc(sizeof(t_data) * 4);
	if (!cube->texture)
		return (0);
	txt = cube->texture;
	i = -1;
	while (++i < 4)
		if (!xpm_to_img(cube, &txt[i], cube->lvl->c_text[i]))
			return (-i);
	if (!get_weapon(cube))
		return (0);
	if (!new_img(cube, cube->screen, WIN_WIDTH, WIN_HEIGHT))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cube		cube;
	t_maps		level;
	t_player	player;

	cube.frame = FRAME;
	if (argc != 2)
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	if (!init_cube(&cube, &player, &level))
		return (write(2, "Error\nMalloc error\n", 19), 0);
	if (!get_maps(&cube, argv[1]))
		return (write(2, "Error\nBad maps\n", 15), 0);
	if (!get_textures(&cube))
		return (write(2, "Error\nBad textures\n", 19), 0);
	if (!make_mini(&cube, &level))
		return (write(2, "Error\nAttempt for mini map failed\n", 34), 0);
	draw_doom(&cube);
	mlx_loop_hook(cube.mlx, &fps, &cube);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	mlx_hook(cube.win, 3, 10, &key_event_release, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
