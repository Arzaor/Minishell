/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:16:18 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:16:19 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_countalphas(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

static char	**ft_fill(char const *s, char c, int a, int w)
{
	int		i;
	int		j;
	char	**str;

	w = ft_countwords(s, c);
	str = (char **)malloc(sizeof(char *) * (w + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < w)
	{
		while (*s == c)
			s++;
		a = ft_countalphas(s, c);
		str[i] = (char *)malloc(sizeof(char) * (a + 1));
		if (!str[i])
			return (NULL);
		j = 0;
		while (j < a)
			str[i][j++] = *s++;
		str[i][j] = '\0';
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		countwords;
	int		countalphas;

	str = 0;
	countwords = 0;
	countalphas = 0;
	if (!s)
		return (NULL);
	str = ft_fill(s, c, countalphas, countwords);
	return (str);
}
