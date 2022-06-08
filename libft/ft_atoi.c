/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:13:50 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:13:52 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoi(const char *str)
{
	long long	num;
	long long	n;

	num = 1;
	n = 0;
	while ((*str == '\t') || (*str == '\v') || (*str == '\f') || (*str == '\r')
		|| (*str == '\n') || (*str == ' '))
		str++;
	if (*str == '-')
	{
		num *= -1;
		str++;
	}
	else
	{
		if (*str == '+')
			str++;
	}
	while ((*str >= '0' && *str <= '9'))
		n = (n * 10) + (*(str++) - '0');
	return (n * num);
}
