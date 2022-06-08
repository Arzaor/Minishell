/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:17:07 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:17:07 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;
	int		i;

	index = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			index = i;
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	if (index == -1)
		return (NULL);
	else
	{
		return ((char *)(s + index));
	}
}
