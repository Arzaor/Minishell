/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:46:23 by jbarette          #+#    #+#             */
/*   Updated: 2022/07/26 16:38:18 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fast_parsing(char *line)
{
	char	**cmds_bis;

	cmds_bis = ft_split(line, ' ');
	return (cmds_bis);
}
