/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshahary <sshahary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:53:23 by sshahary          #+#    #+#             */
/*   Updated: 2024/05/25 17:19:32 by sshahary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub.h"

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


	init(&mlx, &img);;

	mlx_loop_hook(mlx, loop_hook, mlx);
	// mlx_key_hook(mlx, handle_keys, NULL);
	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return 0;
}
