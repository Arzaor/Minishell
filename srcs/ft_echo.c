/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:09:44 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/26 16:20:19 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_parser *parser)
{
	if (parser->parser_args)
	{
		printf("%s", parser->parser_args);
		if (!parser->parser_opt)
			printf("\n");
	}
	else
		printf("\n");
	g_code = 0;
}
