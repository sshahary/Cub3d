/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 12:23:21 by asemsey          ###   ########.fr       */
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
	// printf("x: %d\n, y: %d\n", game_data.player->x, game_data.player->y);
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
	if (data->cub->player_dir == 0)
		data->player->angle = 0;
	if (data->cub->player_dir == 1)
		data->player->angle = M_PI/2;
	if (data->cub->player_dir == 2)
		data->player->angle = M_PI;
	if (data->cub->player_dir == 3)
		data->player->angle = M_PI * 3 / 2;
	if (!data->textures.north || !data->textures.south ||
		!data->textures.east || !data->textures.west) {
		ft_error("Failed to load textures");
	}
}

void	loop_hook(void* param)
{
	t_game *data;
	data = param;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	control(data);
	ray_cast(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_game game_data;
	t_cub	*cub = NULL;

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
		ft_error("forget to give map .cub file :(");
	game_data.cub = cub;
	game_data.player = ft_calloc(1, sizeof(t_player));
	game_data.ray = ft_calloc(1, sizeof(t_ray));
	game_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 0);
	init(game_data);
	load_textures(&game_data);
	mlx_loop_hook(game_data.mlx, &loop_hook, &game_data);
	mlx_key_hook(game_data.mlx, &key, &game_data);
	mlx_loop(game_data.mlx);
	mlx_delete_image(game_data.mlx, game_data.img);
	mlx_delete_texture(game_data.textures.north);
	mlx_delete_texture(game_data.textures.south);
	mlx_delete_texture(game_data.textures.east);
	mlx_delete_texture(game_data.textures.west);
	mlx_terminate(game_data.mlx);
	return (EXIT_SUCCESS);
}
