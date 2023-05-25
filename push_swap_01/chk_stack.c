/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:40:56 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/25 11:24:04 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	dup_check(t_node *lst, t_node *next)
{
	while (next)
	{
		if (lst->data == next->data)
			return (1);
		next = next->next;
	}
	if (lst->next == NULL)
		return (0);
	else
		return (dup_check(lst->next, ((t_node *)(lst->next))->next));
}