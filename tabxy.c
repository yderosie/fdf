/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabxy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 15:30:51 by yderosie          #+#    #+#             */
/*   Updated: 2015/01/18 15:30:53 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		nbline(char *argv)
{
	char	*s;
	int		fd;
	int		j;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("error");
		return (-1);
	}
	while (get_next_line(fd, &s))
		j++;
	free(s);
	close(fd);
	return (j);
}

void	tabint_xy(char **coordonner, int **xy, t_line *l)
{
	int		j;

	j = 0;
	while (coordonner[j] != '\0')
		j++;
	(*xy) = (int *)malloc(sizeof(int) * (j + 1));
	j = 0;
	while (coordonner[j] != '\0')
	{
		(*xy)[j] = ft_atoi(coordonner[j]);
		j++;
	}
	if (j > l->c)
		l->c = j;
}

void	tabxy(int fd, int ***xy, t_line *l)
{
	char		*line;
	char		**coordonner;
	int			j;

	while (get_next_line(fd, &line))
	{
		coordonner = ft_strsplit(line, ' ');
		tabint_xy(coordonner, &(*xy)[j], &(*l));
		j++;
	}
	l->l = j;
}
