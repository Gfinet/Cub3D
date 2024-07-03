/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/03 19:37:41 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
t_data	rcdda(t_cube *cube, char **map, t_player player);

static int check_format(char *file)
{
	size_t i;

	i = 0;
	while (file && i < ft_strlen(file) && file[i] != '.')
		i++;
	if (ft_strncmp(&file[i], ".cub", 5))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cube cube;
	t_maps level;
	t_data		screen;
	t_player	player = {(t_point){12., 12.}, (t_point){-1., 0.}};

	if (argc != 2 )
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	cube.mlx = mlx_init();
	cube.win = mlx_new_window(cube.mlx, WIN_WIDTH, WIN_HEIGHT, "DOOM3D");
	if (!get_maps(&level, argv[1]))
		return (write(2, "Error\nBad maps\n", 15), 0);
	if (!make_mini(&cube, &level))
		return (write(2, "Error\nAttempt for mini map failed\n", 34), 0);
	cube.texture = malloc(sizeof(t_data) * 4);
	cube.texture[0].img = mlx_xpm_file_to_image(cube.mlx, "/Users/lvodak/19/4th_Circle/Cub3d/nounours(1).xpm", &cube.texture[0].width, &cube.texture[0].height);
	cube.texture[1].img = mlx_xpm_file_to_image(cube.mlx, "/Users/lvodak/19/4th_Circle/Cub3d/nicpimp.xpm", &cube.texture[1].width, &cube.texture[1].height);
	cube.texture[2].img = mlx_xpm_file_to_image(cube.mlx, "/Users/lvodak/19/4th_Circle/Cub3d/eagle.xpm", &cube.texture[2].width, &cube.texture[2].height);
	cube.texture[3].img = mlx_xpm_file_to_image(cube.mlx, "/Users/lvodak/19/4th_Circle/Cub3d/minecraft(1).xpm", &cube.texture[3].width, &cube.texture[3].height);
	// if (!cube.texture[0].img || !cube.texture[3].img || !cube.texture[2].img || !cube.texture[1].img)
	// 	return (printf("urrrrgh\n"));
	cube.texture[0].addr = mlx_get_data_addr(cube.texture[0].img, &cube.texture[0].bits_per_pixel, &cube.texture[0].line_length, &cube.texture[0].endian);
	cube.texture[1].addr = mlx_get_data_addr(cube.texture[1].img, &cube.texture[1].bits_per_pixel, &cube.texture[1].line_length, &cube.texture[1].endian);
	cube.texture[2].addr = mlx_get_data_addr(cube.texture[2].img, &cube.texture[2].bits_per_pixel, &cube.texture[2].line_length, &cube.texture[2].endian);
	cube.texture[3].addr = mlx_get_data_addr(cube.texture[3].img, &cube.texture[3].bits_per_pixel, &cube.texture[3].line_length, &cube.texture[3].endian);
	printf("%s\n", cube.texture->addr);
	screen = rcdda(&cube, level.c_maps, player);
	mlx_put_image_to_window(cube.mlx, cube.win, level.mini.maps.img, 4 * WIN_WIDTH / 5, 0);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	mlx_mouse_hook(cube.win, &mouse_event, &cube);
	//mlx_scroll_hook(cube.mlx, scroll_event, &cube);
	//mlx_loop_hook(cube.mlx, add_event, &cube);
	mlx_loop(cube.mlx);
	return (0);
}