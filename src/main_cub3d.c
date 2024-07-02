/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/02 17:42:46 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
t_data*	rcdda(t_cube *cube, char **map, t_player player);

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
	// t_img img;
	t_maps level;
	t_data		*screen;
	t_player	player = {(t_point){6., 22.}, (t_point){0., 1.}};
	int x = 0;
	int y = 0;

	// img.path = ft_strdup("/Users/gfinet/Desktop/Cub3D/minecraft.xpm");
	if (argc != 2 )
		return (write(2, "Error\nBad Arg\n", 14), 0);
	if (!check_format(argv[1]))
		return (write(2, "Error\nBad format\n", 17), 0);
	cube.mlx = mlx_init();
	cube.win = mlx_new_window(cube.mlx, WIN_WIDTH, WIN_HEIGHT, "DOOM3D");
	if (!get_maps(&level, argv[1]))
		return (write(2, "Error\nBad maps\n", 15), 0);
	// if (!make_mini(&cube, &level))
	// 	return (write(2, "Error\nAttempt for mini map failed\n", 34), 0);
	// img.height = 12;
	// img.witdh = 12;
	// img.img = mlx_xpm_file_to_image(cube.mlx, img.path, &img.witdh, &img.height);
	// if (img.img)
	// 	mlx_put_image_to_window(cube.mlx, cube.win, img.img, 0, 0);
	// else
	// 	printf("%p\n", img.img);
	// mlx_close_hook(cube.mlx, esc_handle, &cube);
	cube.texture = malloc(sizeof(t_data));
	cube.texture->img = mlx_xpm_file_to_image(cube.mlx, "/Users/lvodak/19/4th_Circle/Cub3d/minecraft.xpm", &x, &y);
	if (!cube.texture->img)
		return (printf("urrrrgh\n"));
	cube.texture->addr = mlx_get_data_addr(cube.texture->img, &cube.texture->bits_per_pixel, &cube.texture->line_length, &cube.texture->endian);
	printf("%s\n", cube.texture->addr);
	screen = rcdda(&cube, level.maps, player);
	// mlx_put_image_to_window(cube.mlx, cube.win, screen->img, 0, 0);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	mlx_mouse_hook(cube.win, &mouse_event, &cube);
	// mlx_scroll_hook(cube.mlx, scroll_event, &cube);
	//mlx_loop_hook(cube.mlx, add_event, &cube);
	mlx_loop(cube.mlx);
	return (0);
}

int	mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);
int	mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);

int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
int	mlx_loop (void *mlx_ptr);