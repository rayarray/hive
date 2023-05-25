/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:31:13 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/25 14:03:34 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*swap(t_stack *s)
{
	if (s->a->next != NULL)
	{
		s->a->next = s->a->next->next;
		next->next = lst;
	}
}

t_node	*push(t_node *lst)