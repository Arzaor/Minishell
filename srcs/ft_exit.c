/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 02:09:25 by jbarette          #+#    #+#             */
/*   Updated: 2022/06/26 02:20:09 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_parser *parser)
{
	// Créer un free_env
	free_parser(parser);
	printf("exit");
	exit(EXIT_SUCCESS);
}

void	ft_exit_with_line(char *line)
{
	// Créer un free_env
	free(line);
	printf("exit");
	exit(EXIT_SUCCESS);
}