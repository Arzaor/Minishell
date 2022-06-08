/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:17:11 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:17:11 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	pre;
	unsigned int	post;
	char			*s;

	if (!s1 || !set)
		return (NULL);
	pre = 0;
	while (s1[pre] && ft_strchr(set, s1[pre]))
		pre++;
	post = ft_strlen(s1 + pre);
	if (post)
	{
		while (s1[pre + post - 1] && ft_strchr(set, s1[pre + post - 1]))
			post--;
	}
	s = (char *)malloc((post + 1) * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1 + pre, ft_strlen(s1 + post) - ft_strlen(s1 + pre));
	s[post] = '\0';
	return (s);
}
