/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 13:08:45 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/31 18:17:29 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_op(t_stack *s, t_stack *(*op)(t_stack *s), int abr)
{
	if (abr < 0 || abr > 2 || (op == &push && abr == 2))
		return ;
	if (op == &swap)
		s->ops = add_to_end(0 + abr, s->ops);
	if (op == &push)
		s->ops = add_to_end(3 + abr, s->ops);
	if (op == &rot)
		s->ops = add_to_end(5 + abr, s->ops);
	if (op == &rrot)
		s->ops = add_to_end(8 + abr, s->ops);
}

t_stack	*a(t_stack *s, t_stack *(*op)(t_stack *s), int log)
{
	if (s == NULL)
		return (NULL);
	op(s);
	if (log)
		add_op(s, op, 0);
	return (s);
}

t_stack	*b(t_stack *s, t_stack *(*op)(t_stack *s), int log)
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
	if (log)
		add_op(s, op, 1);
	return (s);
}

t_stack	*r(t_stack *s, t_stack *(*op)(t_stack *s), int log)
{
	if (s == NULL || op == &push)
		return (NULL);
	op(s);
	b(s, op, 0);
	if (log)
		add_op(s, op, 2);
	return (s);
}

int	is_sorted(t_node *lst)
{
	int	i;

	if (!lst)
		return (1);
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
	copy->ops = copy_list(s->ops);
	return (copy);
}

int	free_stack(t_stack *s)
{
	if (!s)
		return (1);
	if (s->a)
		destroy_list(s->a);
	if (s->b)
		destroy_list(s->b);
	if (s->j)
		destroy_list(s->j);
	if (s->ops)
		destroy_list(s->ops);
	free(s);
	return (1);
}
