/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:19:55 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/05 17:41:17 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim4(char *ibuf, char *str)
{
	ibuf = str;
	while (*ibuf && ft_isspace(*ibuf))
		++ibuf;
	return (ibuf);
}

char	*ft_strtrim3(int i, char *obuf)
{
	obuf[i] = '\0';
	while (--i >= 0)
	{
		if (!ft_isspace(obuf[i]))
			break ;
	}
	obuf[++i] = '\0';
	return (obuf);
}

char	*ft_strtrim2(char *str, char *ibuf, char *obuf, int cnt)
{
	int	i;

	i = 0;
	ibuf = ft_strtrim4(ibuf, str);
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
	obuf = ft_strtrim3(i, obuf);
}

char	*ft_strtrim(char *str)
{
	char	*ibuf;
	char	*obuf;
	int		cnt;

	ibuf = str;
	obuf = str;
	cnt = 0;
	str = ft_strtrim2(str, ibuf, obuf, cnt);
	return (str);
}
