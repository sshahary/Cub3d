/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/03 12:10:35 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

// static void error(void) {
// 	printf("%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

void	ft_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	init(t_game game_data)
{
	game_data.player->x = game_data.cub->x * TILE + TILE / 2;
	game_data.player->y = game_data.cub->y * TILE + TILE / 2;
	game_data.player->fovradian = FOV * M_PI / 180;
	game_data.player->angle = M_PI;
	printf("x: %d\n, y: %d\n", game_data.player->x, game_data.player->y);
	
}

// void clear_image(mlx_image_t *img, uint32_t color)
// {
// 	for (uint32_t y = 0; y < img->height; y++)
// 	{
// 		for (uint32_t x = 0; x < img->width; x++)
// 		{
// 			((uint32_t*)img->pixels)[y * img->width + x] = color;
// 		}
// 	}
// }

void load_textures(t_game *data)
{
	data->textures.north = mlx_load_png(data->cub->no_png);
	data->textures.south = mlx_load_png(data->cub->so_png);
	data->textures.east = mlx_load_png(data->cub->we_png);
	data->textures.west = mlx_load_png(data->cub->ea_png);
	// data->textures.south.
	if (!data->textures.north || !data->textures.south ||
		!data->textures.east || !data->textures.west) {
		ft_error("Failed to load textures");
	}
}


t_cub	*init_testmap()
{
	t_cub	*cub = ft_calloc(1, sizeof(t_cub));
	cub->map = ft_calloc(10, sizeof(char *));
	cub->map[0] = strdup("1111111111111111111111111"); //fill the map
	cub->map[1] = strdup("1000000000000000000100001");
	cub->map[2] = strdup("1001000000000P00000000001");
	cub->map[3] = strdup("1001000000010000001000001");
	cub->map[4] = strdup("1001000000000000001000001");
	cub->map[5] = strdup("1001000000100000001000001");
	cub->map[6] = strdup("1001000000000000001000001");
	cub->map[7] = strdup("1001000000001000001000001");
	cub->map[8] = strdup("1111111111111111111111111");
	cub->map[9] = NULL;
	cub->y = 3;
	cub->x = 14;
	cub->map_width = 25;
	cub->map_length = 9;
	return (cub);
	
}


void	loop_hook(void* param)
{
	t_game *data;
	data = param;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	control(data, 0, 0);
	ray_cast(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_game game_data;
	t_cub	*cub;

	(void)argv;
	(void)argc;
	if (argc == 2)
	{
		cub = ft_calloc(1, sizeof(t_cub));
		if (read_mapfile(argv[1], cub))
			printf("map read :)\n");
		else
			ft_error("couldn't read map file");
		print_map(cub->map, cub->map_width);
	}
	else
		cub = init_testmap();
	game_data.cub = cub;
	game_data.player = ft_calloc(1, sizeof(t_player));
	game_data.ray = ft_calloc(1, sizeof(t_ray));
	game_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 0);
	init(game_data);
	load_textures(&game_data);
	mlx_loop_hook(game_data.mlx, &loop_hook, &game_data);
	mlx_key_hook(game_data.mlx, &key, &game_data);
	// Main loop with rendering
	mlx_loop(game_data.mlx);

	// Cleanup
	mlx_delete_image(game_data.mlx, game_data.img);
	mlx_delete_texture(game_data.textures.north);
	mlx_delete_texture(game_data.textures.south);
	mlx_delete_texture(game_data.textures.east);
	mlx_delete_texture(game_data.textures.west);
	mlx_terminate(game_data.mlx);

	return EXIT_SUCCESS;
}