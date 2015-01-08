/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yderosie <yderosie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:48:08 by yderosie          #+#    #+#             */
/*   Updated: 2014/11/18 10:50:34 by yderosie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;

	s2 = (char *)s;
	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s2[j] != '\0')
		j++;
	s1 = (char *)malloc(sizeof(*s1) * (1 + j));
	while (s2[i] != '\0')
	{
		s1[i] = f(i, s2[i]);
		i++;
	}
	s1[i] = '\0';
	if (s1 == NULL)
		return (NULL);
	return (s1);
}
