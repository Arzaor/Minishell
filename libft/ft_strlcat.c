/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:16:37 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:16:37 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	k = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (j < dstsize && dst[j])
		j++;
	if (dstsize <= j)
		return (j + i);
	k = 0;
	while (dstsize && (--dstsize - j) && src[k])
	{
		dst[j + k] = src[k];
		k++;
	}
	dst[j + k] = '\0';
	return (i + j);
}
