/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:17:15 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:17:16 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substring;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (ft_strlen(s) - 1))
	{
		substring = (char *)malloc(sizeof(char));
		substring[i] = '\0';
		return (substring);
	}
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (len)
	{
		substring[i] = s[start];
		i++;
		start++;
		len--;
	}
	substring[i] = '\0';
	return (substring);
}
