/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:46:51 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/29 01:03:23 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_free(t_game *data)	// exit the game
{
	int	i = 0;
	while (data->cub->map[i])
		free(data->cub->map[i++]); // free the map line by line
	free(data->cub->map); // free the map
	free(data->cub); // free the data structure
	free(data->player); // free the player structure
	free(data->ray); // free the ray structure
	mlx_delete_image(data->mlx, data->img); // delete the image
	mlx_close_window(data->mlx); // close the window
	mlx_terminate(data->mlx); // terminate the mlx pointer
	printf("Game closed\n"); // print the message
	exit(0); // exit the game
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

void 	key(mlx_key_data_t keydata, void *param)
{
	t_game	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)) // exit the game
		ft_free(data);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS)) // move left
		data->player->leftright = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS)) // move right
		data->player->leftright = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS)) // move down
		data->player->updown = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		data->player->updown = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) // rotate left
		data->player->rotate = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // rotate right
		data->player->rotate = 1;
	release(data, keydata); 
}