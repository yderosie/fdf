/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 17:41:03 by yderosie          #+#    #+#             */
/*   Updated: 2014/11/18 10:56:12 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	s1 = (void *)s;
	s2 = (char *)malloc(sizeof(*s2) * (1 + len));
	while (len--)
	{
		s2[i] = s1[start];
		i++;
		start++;
	}
	if (s2 == NULL)
		return (NULL);
	else
		return (s2);
}
