/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/09 22:21:58 by gfinet           ###   ########.fr       */
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

static int	init_cube(t_cube *cube)
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
	{
		txt[i].img = mlx_xpm_file_to_image(cube->mlx, cube->lvl->c_text[i],
				&txt[i].width, &txt[i].height);
		if (!txt[i].img)
			return (-i);
		txt[i].addr = mlx_get_data_addr(txt[i].img, &txt[i].bits_per_pixel,
				&txt[i].line_length, &txt[i].endian);
	}
	if (!new_img(cube, cube->screen, WIN_WIDTH, WIN_HEIGHT))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cube		cube;
	t_maps		level;
	t_player	player;

	cube.lvl = &level;
	cube.player = &player;
	cube.frame = FRAME;
	if (argc != 2)
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	if (!init_cube(&cube))
		return (write(2, "Error\nMalloc error\n", 19), 0);
	if (!get_maps(&cube, argv[1]))
		return (write(2, "Error\nBad maps\n", 15), 0);
	if (!get_textures(&cube))
		return (write(2, "Error\nBad textures\n", 19), 0);
	if (!make_mini(&cube, &level))
		return (write(2, "Error\nAttempt for mini map failed\n", 34), 0);
	draw_doom(&cube);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_key_hook(cube.win, &key_maj, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
