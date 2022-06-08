/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarette <jbarette@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:15:21 by jbarette          #+#    #+#             */
/*   Updated: 2021/05/15 13:15:21 by jbarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_2;
	t_list	*new;
	t_list	*tmp_1;

	if (!lst)
		return (NULL);
	tmp_1 = lst;
	new = NULL;
	while (tmp_1)
	{
		tmp_2 = ft_lstnew(f(tmp_1->content));
		if (!tmp_2)
		{
			ft_lstclear(&new, del);
			break ;
		}
		ft_lstadd_back(&new, tmp_2);
		tmp_1 = tmp_1->next;
	}
	return (new);
}
