/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 15:05:44 by yderosie          #+#    #+#             */
/*   Updated: 2014/11/13 17:19:26 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char const *src, size_t n)
{
	int		i;
	char	*s2;
	char	*s1;

	i = 0;
	s2 = (char *)src;
	s1 = (char *)dst;
	while (n > 0)
	{
		s1[i] = s2[i];
		i++;
		n--;
	}
	return (s1);
}
