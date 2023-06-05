/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:06:42 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/05 20:13:11 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_b_rot(t_node *n, int nbr, int i)
{
	while ()
}

t_insert	get_iops(t_stack *s, int pos, t_node *n)
{
	t_insert	ops;

	ft_bzero(&ops, sizeof(t_insert));
	if (pos < (get_listsize(s->a) - 1) - pos)
		ops.ra = pos;
	else
		ops.rra = (get_listsize(s->a) - 1) - pos;
	ops.ops = get_b_rot(s->b, n->data, 0);
	if (ops.ops > 0)
		ops.rb = ops.ops;
	else
		ops.rrb = -ops.ops;
	ops.ops = ops.ra + ops.rb + ops.rra + ops.rrb + 1;
	return (ops);
}

t_insert	find_best(t_stack *s, int i)
{
	t_insert	best;
	t_insert	swap;
	t_node		*n;

	n = s->a;
	best = get_iops(s, 0, n->data);
	n = n->next;
	while (n && i++)
	{
		swap = get_iops(s, i, n);
		if (swap.ops < best.ops)
			best = swap;
	}
	return (best);
}

void	grd_ins_sort(t_stack *s)
{
	t_insert	ops;

	while (s->a && !is_sorted(s->b))
	{
		find_best(s, 0);
		make_ops(s, ops);
	}
	while (s->b)
		b(s, &push, 1);
}