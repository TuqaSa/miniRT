#include "MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t *)param);
}

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			r;
	int			g;
	int			b;
	uint32_t	color;

	mlx = mlx_init(800, 600, "MLX42 Test - miniRT Setup", true);
	if (!mlx)
	{
		printf("Error: Failed to initialize MLX42\n");
		return (1);
	}
	// Create a simple colored image to test pixel operations
	img = mlx_new_image(mlx, 800, 600);
	if (!img)
	{
		printf("Error: Failed to create image\n");
		mlx_terminate(mlx);
		return (1);
	}
	// Fill with a gradient (testing pixel operations for ray tracing)
	for (int y = 0; y < 600; y++)
	{
		for (int x = 0; x < 800; x++)
		{
			r = (x * 255) / 800;
			g = (y * 255) / 600;
			b = 128;
			color = (r << 24) | (g << 16) | (b << 8) | 255;
			mlx_put_pixel(img, x, y, color);
		}
	}
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	{
		printf("Error: Failed to display image\n");
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		return (1);
	}
	printf("MLX42 test successful!\n");
	printf("You should see a colored gradient. Press ESC to close.\n");
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	printf("MLX42 test completed successfully!\n");
	return (0);
}
