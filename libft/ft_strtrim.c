#include <ctype.h>
#include <string.h>
#include "libft.h"

#define NUL '\0'

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
		obuf[i] = NUL;
		while (--i >= 0)
		{
			if (!ft_isspace(obuf[i]))
				break;
		}
		obuf[++i] = NUL;
	}
	return str;
}