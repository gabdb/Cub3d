/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angerard <angerard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/19 11:45:40 by angerard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void)
{
	t_mlx	data;
	int		fd;

	fd = open("maps/test.cub", O_RDONLY);
	if (-1 == fd)
		return (write(2, "Error opening file\n", 19), 1);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		write(2, "Error: mlx_init failed\n", 16);
		return (1);
	}
	if (!parsing(&data, fd))
		return (close(fd), write(2, "Error: invalid map\n", 12), 1);
	handle_mlx(&data);
	return (0);
}
