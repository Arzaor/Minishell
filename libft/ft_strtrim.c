/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:19:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 16:23:34 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *str)
{
	char	*ibuf;
	char	*obuf;
	int		i;
	int		cnt;

	ibuf = str;
	obuf = str;
	i = 0;
	cnt = 0;
	if (str)
	{
		ibuf = str;
		while (*ibuf && ft_isspace(*ibuf))
			++ibuf;
		if (str != ibuf)
			ft_memmove(str, ibuf, ibuf - str);
		while (*ibuf)
		{
			if (ft_isspace(*ibuf) && cnt)
				ibuf++;
			else
			{
				if (!ft_isspace(*ibuf))
					cnt = 0;
				else
				{
					ibuf = " ";
					cnt = 1;
				}
				obuf[i++] = *ibuf++;
			}
		}
		obuf[i] = '\0';
		while (--i >= 0)
		{
			if (!ft_isspace(obuf[i]))
				break ;
		}
		obuf[++i] = '\0';
	}
	return (str);
}
