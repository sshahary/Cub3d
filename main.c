/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/25 17:47:29 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

static void error(void)
{
	printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	init(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "Cube3D", true);
	if (!*mlx)
	{
		fprintf(stderr, "MLX42 initialization failed\n");
		exit(EXIT_FAILURE);
	}

	*img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (!*img)
	{
		fprintf(stderr, "Image creation failed\n");
		exit(EXIT_FAILURE);
	}
}


void	loop_hook(void* param)
{
	(void) param;
}

void handle_keys(void *param)
{
	(void) param;
}

int	main()
{
	mlx_t* mlx;
	mlx_image_t* img;


	mlx_texture_t* texture; 
	
	
	init(&mlx, &img);;
	texture = mlx_load_png("texture/brick.png");
	if (!texture)
		error();
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 500, 600) < 0)
		error();

	mlx_loop_hook(mlx, loop_hook, mlx);
	// mlx_key_hook(mlx, handle_keys, NULL);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return 0;
}
