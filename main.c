/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/25 23:50:33 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"


static void error(void) {
	printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	init(t_game *game_data)
{
	game_data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", true);
	if (!game_data->mlx) {
		fprintf(stderr, "MLX42 initialization failed\n");
		exit(EXIT_FAILURE);
	}

	game_data->img = mlx_new_image(game_data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game_data->img) {
		fprintf(stderr, "Image creation failed\n");
		mlx_terminate(game_data->mlx);
		exit(EXIT_FAILURE);
	}
	game_data->texture = mlx_load_png("texture/brick.png");
	if (!game_data->texture)
		error();
	mlx_image_t *temp_img = mlx_texture_to_image(game_data->mlx, game_data->texture);
	if (!temp_img)
		error();
	if (mlx_image_to_window(game_data->mlx, temp_img, 0, 0) < 0)
		error();
	mlx_delete_image(game_data->mlx, temp_img);
}

void clear_image(mlx_image_t *img, uint32_t color)
{
	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			((uint32_t*)img->pixels)[y * img->width + x] = color;
		}
	}
}


void render_floor_ceiling(t_game *game_data)
{
	uint32_t ceiling_color = 0xFF87CEEB; // Sky blue color (with alpha)
	uint32_t floor_color = 0xFF8B4513;   // Brown color (with alpha)

	for (uint32_t y = 0; y < game_data->img->height; y++) {
		for (uint32_t x = 0; x < game_data->img->width; x++) {
			if (y < game_data->img->height / 2) {
				((uint32_t*)game_data->img->pixels)[y * game_data->img->width + x] = ceiling_color;
			} else {
				((uint32_t*)game_data->img->pixels)[y * game_data->img->width + x] = floor_color;
			}
		}
	}
}

void	loop_hook(void* param)
{
	t_game *game_data = (t_game*)param;

	clear_image(game_data->img, 0x00000000); // Clear the image with transparency
	render_floor_ceiling(game_data);

	// Update the image to the window
	mlx_image_to_window(game_data->mlx, game_data->img, 0, 0);

	if (mlx_is_key_down(game_data->mlx, MLX_KEY_ESCAPE)) {
		mlx_close_window(game_data->mlx);
	}
}

int main()
{
	t_game game_data;

	init(&game_data);

	// Main loop with rendering
	mlx_loop_hook(game_data.mlx, loop_hook, &game_data);
	mlx_loop(game_data.mlx);

	// Cleanup
	mlx_delete_image(game_data.mlx, game_data.img);
	mlx_delete_texture(game_data.texture);
	mlx_terminate(game_data.mlx);

	return EXIT_SUCCESS;
}