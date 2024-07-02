/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfinet <gfinet@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 20:25:20 by gfinet           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_cube	cube;
	t_maps	level;
	int		x = 0;
	int		y = 0;
	t_data		*screen;
	t_player	player = {(t_point){6., 9.}, (t_point){0., 1.}};

	cube.lvl = &level;
	if (argc != 2)
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	cube.mlx = mlx_init();
	cube.win = mlx_new_window(cube.mlx, WIN_WIDTH, WIN_HEIGHT, "DOOM3D");
	if (!get_maps(&cube, argv[1]))
		return (write(2, "Error\nBad maps\n", 15), 0);
	if (!make_mini(&cube, &level))
		return (write(2, "Error\nAttempt for mini map failed\n", 34), 0);
	cube.texture = malloc(sizeof(t_data));
	cube.texture->img = mlx_xpm_file_to_image(cube.mlx, "./minecraft.xpm", &x, &y);
	if (!cube.texture->img)
		return (printf("urrrrgh\n"));
	cube.texture->addr = mlx_get_data_addr(cube.texture->img, &cube.texture->bits_per_pixel, &cube.texture->line_length, &cube.texture->endian);
	//printf("%s\n", cube.texture->addr);
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
