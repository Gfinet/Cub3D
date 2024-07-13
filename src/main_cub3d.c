/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:40:12 by gfinet            #+#    #+#             */
/*   Updated: 2024/07/13 15:41:02 by lvodak           ###   ########.fr       */
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
	t_cube		cube;
	t_maps		level;
	t_data		screen;
	t_player	player ;//= {(t_point){11., 11.}, (t_point){1., -1.}};

	cube = (t_cube){0};
	player = (t_player){0};
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
	get_player_pos(&cube);
	make_background(&cube);
	printf("ceiling	%i, %i, %i\n", cube.lvl->ceil[0], cube.lvl->ceil[1], cube.lvl->ceil[2]);
	printf("floor	%i, %i, %i\n", cube.lvl->floor[0], cube.lvl->floor[1], cube.lvl->floor[2] );
	screen.img = mlx_new_image(cube.mlx, WIN_WIDTH, WIN_HEIGHT);
	screen.addr = mlx_get_data_addr(screen.img, &screen.bits_per_pixel,
			&screen.line_length, &screen.endian);
	cube.screen = &screen;
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
	cube.maps = &level;
	cube.player = &player;
	cube.frame = FRAME;
	//rcdda(&cube, cube.maps->c_maps, player);
	draw_doom(&cube);
	mlx_loop_hook(cube.mlx, &fps, &cube);
	mlx_hook(cube.win, 17, 0, &esc_handle, &cube);
	mlx_hook(cube.win, 2, 0, &key_event, &cube);
	mlx_hook(cube.win, 3, 10, &key_event_release, &cube);
	// mlx_loop_hook(cube.mlx, &key_event, &cube);
	// mlx_mouse_hook(cube.win, &mouse_event, &cube);
	//mlx_scroll_hook(cube.mlx, scroll_event, &cube);
	//mlx_loop_hook(cube.mlx, add_event, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
