/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:52:10 by gnyssens          #+#    #+#             */
/*   Updated: 2025/02/04 00:42:47 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(void)
{
	t_mlx	mlx;
	int		fd;
	int		rows;
	
	fd = open("source/test.cub", O_RDONLY);
	if (-1 == fd)
		return(write(2, "error opening file\n", 19), 1);
	rows = num_rows(); //path du .cub un peu hardcodée
	if (!parsing(fd, NULL, rows))
		return (close(fd), write(2, "invalid map\n", 12), 1);
	mlx.map = make_map(rows);
	handle_mlx(&mlx);
	return (0);
}
