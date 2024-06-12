/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/12 11:03:08 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

int	init(t_game *data)
{
	data->player->x = data->cub->x * TILE + TILE / 2;
	data->player->y = data->cub->y * TILE + TILE / 2;
	data->player->angle = data->cub->player_dir * M_PI / 2;
	data->player->fovradian = FOV * M_PI / 180;
	data->textures.north = mlx_load_png(data->cub->no_png);
	if (!data->textures.north)
		return (ft_error("Failed to load textures", 0));
	data->textures.south = mlx_load_png(data->cub->so_png);
	if (!data->textures.south)
		return (ft_error("Failed to load textures", 0));
	data->textures.east = mlx_load_png(data->cub->we_png);
	if (!data->textures.east)
		return (ft_error("Failed to load textures", 0));
	data->textures.west = mlx_load_png(data->cub->ea_png);
	if (!data->textures.west)
		return (ft_error("Failed to load textures", 0));
	return (1);
}

void	loop_hook(void *param)
{
	t_game	*data;

	data = param;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	control(data);
	ray_cast(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	clear_mlx(t_game game_data)
{
	if (game_data.mlx && game_data.img)
		mlx_delete_image(game_data.mlx, game_data.img);
	if (game_data.textures.north)
		mlx_delete_texture(game_data.textures.north);
	if (game_data.textures.south)
		mlx_delete_texture(game_data.textures.south);
	if (game_data.textures.east)
		mlx_delete_texture(game_data.textures.east);
	if (game_data.textures.west)
		mlx_delete_texture(game_data.textures.west);
	if (game_data.mlx)
		mlx_terminate(game_data.mlx);
	ft_free(&game_data, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game_data;

	if (argc != 2)
		return (ft_error("run with: ./cub3D mapfile.cub", EXIT_FAILURE));
	if (!cub_filename(argv[1]))
		return (ft_error("not a valid .cub file", EXIT_FAILURE));
	game_data.cub = ft_calloc(1, sizeof(t_cub));
	if (!read_mapfile(argv[1], game_data.cub))
		return (ft_free(&game_data, 0), EXIT_FAILURE);
	game_data.player = ft_calloc(1, sizeof(t_player));
	if (!init(&game_data))
		return (free(game_data.player), clear_mlx(game_data));
	game_data.ray = ft_calloc(1, sizeof(t_ray));
	game_data.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", 0);
	mlx_loop_hook(game_data.mlx, &loop_hook, &game_data);
	mlx_key_hook(game_data.mlx, &key, &game_data);
	mlx_loop(game_data.mlx);
	clear_mlx(game_data);
	return (EXIT_SUCCESS);
}
