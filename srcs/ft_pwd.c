/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hterras <hterras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:47:04 by hterras           #+#    #+#             */
/*   Updated: 2022/06/23 20:29:22 by hterras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	pwd[256];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}


char	*ft_strcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	k = 0;
	while (src[i])
		i++;
	
	while (j < dstsize && dst[j])
		j++;
	
	k = 0;
	while (dstsize && (--dstsize - j) && src[k])
	{
		dst[j + k] = src[k];
		k++;
	}
	dst[j + k] = '\0';
	return (dst);
}
