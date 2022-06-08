/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:15:47 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:15:48 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	i = 0;
	while (n--)
	{
		if (dst == NULL && src == NULL)
			break ;
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}
