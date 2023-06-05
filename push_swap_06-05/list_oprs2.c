/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_oprs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:39:07 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/30 16:14:35 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*copy_list(t_node *lst)
{
	t_node	*cpy[2];

	if (lst == NULL)
		return (NULL);
	if (lst != NULL)
	{
		cpy[0] = add_node(lst->data);
		cpy[1] = cpy[0];
	}
	while (lst != NULL)
	{
		lst = lst->next;
		if (lst)
		{
			cpy[0]->next = add_node(lst->data);
			cpy[0] = cpy[0]->next;
		}
	}
	return (cpy[1]);
}

t_node	*add_to_end(int value, t_node *lst)
{
	t_node	*end;

	if (!lst)
		lst = add_node(value);
	else
	{
		end = get_last(lst);
		end->next = add_node(value);
	}
	return (lst);
}

int	get_listsize(t_node *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	*cnv_to_arr(t_node *lst)
{
	int	*arr;
	int	i;
	int	j;

	arr = (int *)malloc(sizeof(int) * get_listsize(lst));
	if (arr == NULL)
		return (NULL);
	i = 0;
	j = get_listsize(lst);
	while (i < j)
	{
		arr[i] = lst->data;
		lst = lst->next;
		i++;
	}
	return (arr);
}
