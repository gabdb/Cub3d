/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnyssens <gnyssens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:03:42 by angerard          #+#    #+#             */
/*   Updated: 2025/04/01 15:32:09 by gnyssens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Supprime les espaces et tabulations en début et fin de ligne et
** retourne le pointeur ajusté.
*/
char	*trim_spaces_texture(t_mlx *data, char *line)
{
	int		start;
	int		end;
	char	*result;

	start = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	end = ft_strlen(line) - 1;
	while (end > start && (line[end] == ' ' || line[end] == '\t'
			|| line[end] == '\n'))
		end--;
	result = ft_substr(line, start, end - start + 1);
	if (!result)
		my_exit("Error: Malloc failed in trim_spaces_texture", data);
	return (result);
}

/*
** Supprime les espaces et tabulations en début de ligne et
** retourne le pointeur ajusté.
*/
char	*trim_spaces_tabs(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

/*
** Extrait et charge le chemin de la texture depuis une ligne de configuration.
** Trim les espaces et tabulations des deux côtés.
*/
void	parse_texture_line(t_mlx *data, char *line, int index)
{
	char	*trimmed_line;
	char	*path_copy;

	trimmed_line = trim_spaces_texture(data, line + 2);
	path_copy = safe_strdup(trimmed_line);
	if (!path_copy)
		my_exit("Memory allocation failed in parse_texture_line", data);
	do_textures(data, path_copy, index);
	free(trimmed_line);
	free(path_copy);
}

/*
** Extrait une ligne de couleur, la convertit en valeur
** hexadécimale et l'assigne.
*/
void	parse_color_line(t_mlx *data, unsigned int *color, char *line)
{
	char	*color_copy;

	line = trim_spaces_tabs(line + 1);
	color_copy = ft_strdup(line);
	if (!color_copy)
		my_exit("Memory allocation failed in parse_color_line", data);
	*color = str_to_hexa(data, color_copy);
	free(color_copy);
}

/*
** Initialise les indicateurs de présence des éléments
** de configuration à zéro.
*/
void	init_element_flags(t_element_flags *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->f = 0;
	flags->c = 0;
}
