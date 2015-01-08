/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:40:58 by yderosie          #+#    #+#             */
/*   Updated: 2014/11/20 11:39:16 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char const *src, size_t size)
{
	char	*s1;
	int		j;
	int		i;
	int		k;

	k = ft_strlen(dst);
	s1 = (char *)src;
	i = size;
	if (ft_strlen(src) < size)
		i = size - k;
	if (ft_strlen(dst) < 1)
		j = ft_strlen(src) - ft_strlen(dst);
	else if (ft_strlen(dst) > size)
		j = ft_strlen(src) + size;
	else
		j = ft_strlen(src) + ft_strlen(dst);
	while (i-- > 0)
		dst[k++] = *s1++;
	if (ft_strlen(dst) != 0)
		dst[--k] = '\0';
	else
		dst[k] = '\0';
	return (j);
}
