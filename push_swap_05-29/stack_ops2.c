/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:08:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/29 15:09:17 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*b(t_stack *s, t_stack *(*op)(t_stack *s))
{
	if (s == NULL)
		return (NULL);
	s->i = s->a;
	s->a = s->b;
	s->b = s->i;
	op(s);
	s->i = s->a;
	s->a = s->b;
	s->b = s->i;
	return (s);
}

t_stack	*r(t_stack *s, t_stack *(*op)(t_stack *s))
{
	if (s == NULL)
		return (NULL);
	op(s);
	b(s, op);
	return (s);
}

int	is_sorted(t_node *lst)
{
	int	i;

	i = lst->data;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (i >= lst->data)
			return (0);
		i = lst->data;
	}
	return (1);
}

int	is_sorted2(t_node *lst)
{
	if (lst != NULL && lst->next != NULL)
	{
		if (lst->data >= ((t_node *)(lst->next))->data)
			return (0);
		else
			return (is_sorted2(lst->next));
	}
	else
		return (1);
}

t_stack	*copy_stack(t_stack *s)
{
	t_stack	*copy;

	copy = init_stack();
	copy->a = copy_list(s->a);
	copy->b = copy_list(s->b);
	copy->i = copy_list(s->i);
	copy->j = copy_list(s->j);
	copy->ops = copy_list(s->ops);
	return (copy);
}
