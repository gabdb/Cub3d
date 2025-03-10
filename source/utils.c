/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:59:00 by gnyssens          #+#    #+#             */
/*   Updated: 2025/03/03 15:08:19 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//pr la poubelle aussi
int	num_rows(void)
{
	int		fd;
	int		count;
	char	*line;

	fd = open("maps/test.cub", O_RDONLY);
	if (-1 == fd)
	{
		write(2, "file opening failed, quitting program...\n", 41);
		exit(EXIT_FAILURE);
	}
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
		{
			count++;
			free(line);
		}
	}
	//printf("CHECK nombre de rows: %d\n", count);
	return (count);
}

int	round_float(float nb)
{
	int	a;
	int	b;

	a = (int) nb; // == nb truncated
	b = (float) a;
	if (nb - b <= 0.5)
		return (a);
	else
		return (a + 1);
}

double	get_time_in_seconds(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	free_split(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
