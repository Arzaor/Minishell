/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:34:02 by hterras           #+#    #+#             */
/*   Updated: 2022/07/21 01:53:03 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_tri_tab(char **tri, int count)
{
	char	*t;
	int		j;
	int		i;

	i = 0;
	while (i < count)
	{
		while (j < count)
		{
			if (ft_strcmp(tri[i], tri[j]) < 0)
			{
				t = tri[i];
				tri[i] = tri[j];
				tri[j] = t;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

/*void static	export_arg2(t_env *env, char *value)
{
	ft_unset(env, value);
	insert_env(env, value);
}
*/
static void	export_arg2(t_env *env, char *value)
{
	char	**str;

	str = ft_split(value, '=');
	ft_unset(env, str[0]);
	free_array(str);
	insert_env(env, value);
}

static char	*check_symbols_w_parser(char *str, int i)
{
	int		count;
	int		j;
	char	*env_var;

	count = i;
	j = 0;
	env_var = 0;
	str++;
	while (str[count] && (str[count] != ' ' || str[count] != '\'' || str[count] != '"' || str[count] != '$' || str[count] != '(' || str[count] != ')'))
		count++;
	env_var = malloc(sizeof(char) * count + 1);
	while (str[i] && (str[i] != ' ' || str[i] != '\'' || str[i] != '"' || str[i] != '$' || str[i] != '(' || str[i] != ')'))
		env_var[j++]= str[i++];
	env_var[j] = '\0';
	return (env_var);
}

static void	export_arg(t_env *env, char *value)
{
	int		j;
	int		i;
	char	**str;
	char	**str1;
	char	*str3;
	char	*result;
	char	*bin;

	j = 0;
	i = 0;
	result = 0;
	str = ft_split(value, ' ');
	while (str[i])
	{
		str1 = ft_split(str[i], '=');
		while (str1[1][j])
		{
			if (str1[1][j] == '$')
				break ;
			j++;
		}
		str3 = check_symbols_w_parser(str1[1], j++);
		result = get_env(env, str3);
		if (result)
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(str1[0]) + 1 + ft_strlen(result) + 1));
			ft_strcat(bin, str1[0]);
			ft_strcat(bin, "=");
			ft_strcat(bin, result);
			result = get_env(env, str1[0]);
			if (result)
				export_arg2(env, bin);
			else
				insert_env(env, bin);
			free(bin);
		}
		else
		{
			result = get_env(env, str1[0]);
			if (result)
				export_arg2(env, str[i]);
			else
				insert_env(env, str[i]);
		}
		j = 0;
		i++;
		free_array(str1);
		free(result);
	}
	free_array(str);
}

void	ft_export(t_env *env, char *value)
{
	char	**tri;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	if (!value)
	{
		tri = create_tab(env);
		while (tri[i])
			i++;
		count = i;
		ft_tri_tab(tri, i);
		while (j < count)
			printf("declare -x %s\n", tri[j++]);
		free(tri);
	}
	else
		export_arg(env, value);
}
