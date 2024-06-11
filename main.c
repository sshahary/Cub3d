/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/11 16:22:17 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

void	init(t_game game_data)
{
	game_data.player->x = game_data.cub->x * TILE + TILE / 2;
	game_data.player->y = game_data.cub->y * TILE + TILE / 2;
	game_data.player->fovradian = FOV * M_PI / 180;
	game_data.player->angle = M_PI;
}

void	load_textures(t_game *data)
{
	data->textures.north = mlx_load_png(data->cub->no_png);
	data->textures.south = mlx_load_png(data->cub->so_png);
	data->textures.east = mlx_load_png(data->cub->we_png);
	data->textures.west = mlx_load_png(data->cub->ea_png);
	data->player->angle = data->cub->player_dir * M_PI / 2;
	if (!data->textures.north || !data->textures.south ||
		!data->textures.east || !data->textures.west)
		ft_error("Failed to load textures");
}

void	loop_hook(void* param)
{
	t_game	*data;

	data = param;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	control(data);
	ray_cast(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	clear_stuff(t_game game_data)
{
	mlx_delete_image(game_data.mlx, game_data.img);
	mlx_delete_texture(game_data.textures.north);
	mlx_delete_texture(game_data.textures.south);
	mlx_delete_texture(game_data.textures.east);
	mlx_delete_texture(game_data.textures.west);
	mlx_terminate(game_data.mlx);
}

int	main(int argc, char **argv)
{
	t_game game_data;
	t_cub	*cub;

	if (argc != 2)
		ft_error("forget to give map .cub file :(");
	cub = ft_calloc(1, sizeof(t_cub));
	if (!read_mapfile(argv[1], cub))
		ft_error("couldn't read map file");
	game_data.cub = cub;
	game_data.player = ft_calloc(1, sizeof(t_player));
	game_data.ray = ft_calloc(1, sizeof(t_ray));
	game_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 0);
	init(game_data);
	load_textures(&game_data);
	mlx_loop_hook(game_data.mlx, &loop_hook, &game_data);
	mlx_key_hook(game_data.mlx, &key, &game_data);
	mlx_loop(game_data.mlx);
	clear_stuff(game_data);
	return (EXIT_SUCCESS);
}
