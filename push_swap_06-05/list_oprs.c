/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_oprs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:03:39 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/02 20:08:48 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*add_node(int value)
{
	t_node	*lst;

	lst = (t_node *)malloc(sizeof(t_node));
	if (lst == NULL)
		return (NULL);
	lst->data = value;
	lst->next = NULL;
	return (lst);
}

t_node	*append_node(int value, t_node *prev)
{
	t_node	*lst;

	lst = (t_node *)malloc(sizeof(t_node));
	if (lst == NULL)
		return (NULL);
	lst->data = value;
	if (prev != NULL)
	{
		lst->next = prev->next;
		prev->next = lst;
	}
	else
		lst->next = NULL;
	return (lst);
}

t_node	*get_last(t_node *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_node	*remove_last(t_node *lst)
{
	t_node	*i;
	t_node	*j;

	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
	{
		free(lst);
		return (NULL);
	}
	i = lst;
	while (lst->next)
	{
		j = lst;
		lst = lst->next;
	}
	if (j)
		j->next = NULL;
	free(lst);
	//lst->next = NULL;
	return (i);
}

int	destroy_list(t_node *lst)
{
	t_node	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
	return (1);
}
