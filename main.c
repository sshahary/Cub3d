#include "include/cub.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	// (void)argc;
	// (void)argv;
	printf("hello!\n");
	if (argc == 2)
	{
		if (read_mapfile(argv[1], &cub))
			printf("everything ok :)\n");
		else
			printf("error reading cub file\n");
	}
	return (0);
}
