/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 16:23:42 by yderosie          #+#    #+#             */
/*   Updated: 2014/12/04 16:54:53 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			check_line(char *buf, int ret, char **line)
{
	int			i;
	int			j;
	static char	*tab;

	if (tab == NULL)
		tab = (char *)malloc(sizeof(tab) * (ret + 1));
	i = -1;
	j = 0;
	tab = ft_strjoin(tab, buf);
	while (tab[++i] != '\0')
		if ((tab[i] == '\n' || tab[i] == EOF) || (ret != BUFF_SIZE))
			j++;
	i = 0;
	if ((j > 0) || (ret != BUFF_SIZE && tab[0] != '\0'))
	{
		while (tab[i] != '\n' && tab[i] != '\0')
			i++;
		(*line) = ft_memalloc(i);
		(*line) = ft_strncpy((*line), tab, i);
		tab = ft_strsub(tab, (i + 1), (ft_strlen(tab)));
	}
	ft_bzero(buf, BUFF_SIZE);
	return (j);
}

int			get_next_line(int const fd, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == (-1))
			return (-1);
		buf[ret] = '\0';
		if ((check_line(buf, ret, line)))
			break ;
	}
	if (ret > 0)
		return (1);
	if ((ret == 0) && (check_line(buf, ret, line)))
		return (1);
	else
		return (ret);
}
