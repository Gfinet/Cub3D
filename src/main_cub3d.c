/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/04 00:21:14 by gfinet           ###   ########.fr       */
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

static int init_cube(t_cube *cube)
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

int	main(int argc, char **argv)
{
	t_cube cube;
	t_maps level;
	t_player	player = {(t_point){11., 11.}, (t_point){0., -1.}};

	cube.lvl = &level;
	cube.player = &player;
	if (argc != 2)
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	if (!init_cube(&cube))
		return (write(2, "Error\nmalloc error\n", 19), 0);
	if (!get_maps(&cube, argv[1]))
		return (write(2, "Error\nBad maps\n", 15), 0);
	make_background(&cube);
	if (!make_mini(&cube, &level))
		return (write(2, "Error\nAttempt for mini map failed\n", 34), 0);
	cube.texture = malloc(sizeof(t_data) * 4);
	cube.texture[0].img = mlx_xpm_file_to_image(cube.mlx, "./texture/nounours(1).xpm", &cube.texture[0].width, &cube.texture[0].height);
	cube.texture[1].img = mlx_xpm_file_to_image(cube.mlx, "./texture/nicpimp.xpm", &cube.texture[1].width, &cube.texture[1].height);
	cube.texture[2].img = mlx_xpm_file_to_image(cube.mlx, "./texture/eagle.xpm", &cube.texture[2].width, &cube.texture[2].height);
	cube.texture[3].img = mlx_xpm_file_to_image(cube.mlx, "./texture/minecraft(1).xpm", &cube.texture[3].width, &cube.texture[3].height);
	cube.texture[0].addr = mlx_get_data_addr(cube.texture[0].img, &cube.texture[0].bits_per_pixel, &cube.texture[0].line_length, &cube.texture[0].endian);
	cube.texture[1].addr = mlx_get_data_addr(cube.texture[1].img, &cube.texture[1].bits_per_pixel, &cube.texture[1].line_length, &cube.texture[1].endian);
	cube.texture[2].addr = mlx_get_data_addr(cube.texture[2].img, &cube.texture[2].bits_per_pixel, &cube.texture[2].line_length, &cube.texture[2].endian);
	cube.texture[3].addr = mlx_get_data_addr(cube.texture[3].img, &cube.texture[3].bits_per_pixel, &cube.texture[3].line_length, &cube.texture[3].endian);
	printf("%s\n", cube.texture->addr);
	cube.screen = NULL;
	cube.maps = &level;
	cube.player = &player;
	rcdda(&cube, cube.maps->c_maps, player);
	mlx_put_image_to_window(cube.mlx, cube.win, level.mini.maps.img, 4 * WIN_WIDTH / 5, 0);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	// mlx_loop_hook(cube.mlx, &key_event, &cube);
	// mlx_mouse_hook(cube.win, &mouse_event, &cube);
	//mlx_scroll_hook(cube.mlx, scroll_event, &cube);
	//mlx_loop_hook(cube.mlx, add_event, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
