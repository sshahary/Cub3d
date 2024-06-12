/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:46:51 by sshahary          #+#    #+#             */
/*   Updated: 2024/06/12 10:20:51 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_free(t_game *data, int flag)
{
	int	i;

	i = 0;
	ft_arrfree(data->cub->map);
	free(data->cub->ea_png);
	free(data->cub->we_png);
	free(data->cub->no_png);
	free(data->cub->so_png);
	free(data->cub);
	if (!flag)
		return ;
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	printf("Game closed\n");
	exit (EXIT_SUCCESS);
}

void	release(t_game *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		data->player->leftright = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		data->player->leftright = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		data->player->updown = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		data->player->updown = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		data->player->rotate = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		data->player->rotate = 0;
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_game	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		ft_free(data, 1);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		data->player->leftright = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		data->player->leftright = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		data->player->updown = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		data->player->updown = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->player->rotate = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->player->rotate = 1;
	release(data, keydata);
}
