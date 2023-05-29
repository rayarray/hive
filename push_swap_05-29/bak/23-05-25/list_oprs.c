/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_oprs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:03:39 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 13:28:58 by rleskine         ###   ########.fr       */
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

int	append_node(int value, t_node *prev)
{
	t_node	*lst;

	lst = (t_node *)malloc(sizeof(t_node));
	if (lst == NULL)
		return (0);
	lst->data = value;
	lst->next = prev->next;
	prev->next = lst;
	return (1);
}

t_node	*get_last(t_node *lst)
{
	while (lst->next)
		lst = (t_node *)lst->next;
	return (lst);
}

t_node	*remove_node(t_node *lst)
{
	t_node	*next;

	next = lst->next;
	free(lst);
	return (next);
}

int	destroy_list(t_node *lst)
{
	while (lst->next)
		lst = remove_node(lst);
	return (1);
}