/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:35:43 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/29 16:53:41 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_snode	getlast(t_snode *s)
{
	while (s && s->next)
		s = s->next;
	return (s);
}

t_snode	*add_stack(t_snode *lst, t_stack *s)
{
	while (lst && lst->next)
		lst = lst->next;
	lst->next = (t_snode *)malloc(sizeof(t_snode));
	lst = lst->next;
	lst->next = NULL;
	lst->s = copy_stack(s);
	return (lst);
}

t_stack	*minops(t_stack *s[11])
{
	int	i;
	int	min;
	int	best;

	i = 0;
	min = -1;
	best = -1;
	while (min == -1 && i < 11)
	{
		if (s[i] && s[i]->a && is_sorted2(s[i]->a) && !s[i]->b && s[i]->ops != NULL)
		{
			min = get_listsize(s[i]->ops);
			best = i;
		}
		i++;
	}
	while (i < 11)
	{
		if (s[i] && s[i]->a && is_sorted2(s[i]->a) && !s[i]->b && s[i]->ops != NULL && min > get_listsize(s[i]->ops))
			min = get_listsize(s[i]->ops);
			best = i;
		i++;
	}
	i = 0;
	while (i < 11)
	{
		if (i != best && s[i] != NULL)
			free(s[i]);
		i++;
	}
	if (min != -1)
		return (s[best]);
	else
		return (NULL);
}

t_stack	*minops2(t_snode *sl, int valid)
{
	int	i;
	int	min;
	int	best;

	
}

int	check_op(t_stack *s, int op)
{
	if (op == 0 && s->a && s->a->next)
		return (1);
	else if (op == 1 && s->b && s->b->next)
		return (1);
	else if (op == 2 && ((s->a && s->a->next) || (s->b && s->b->next)))
		return (1);
	else if (op == 3 && s->b)
		return (1);
	else if (op == 4 && s->b)
		return (1);
	else if ((op == 5 || op == 8) && s->a && s->a->next)
		return (1);
	else if ((op == 6 || op == 9) && s->b && s->b->next)
		return (1);
	else if ((op == 7 || op == 10) && ((s->b && s->b->next)
			|| (s->a && s->a->next)))
		return (1);
	return (0);
}

void	make_op(t_stack *s, int op)
{
	if (op == 0)
		swap(s);
	else if (op == 1)
		b(s, &swap);
	else if (op == 2)
		r(s, &swap);
	else if (op == 3)
		push(s);
	else if (op == 4)
		b(s, &push);
	else if (op == 5)
		r(s, &push);
	else if (op == 6)
		rot(s);
	else if (op == 7)
		b(s, &rot);
	else if (op == 8)
		r(s, &rot);
	else if (op == 9)
		rrot(s);
	else if (op == 10)
		b(s, &rrot);
	else if (op == 11)
		r(s, &rrot);
}

t_stack	*bruteforce(t_stack *s, int maxops, int i)
{
	t_stack	*stacks[11];

	i = 0;
	if (is_sorted2(s->a) || get_listsize(s->ops) >= maxops)
		return (s);
	stacks[0] = copy_stack(s);
	stacks[0]->ops = add_to_end(0, stacks[0]->ops);
	swap(stacks[0]);
	stacks[0] = bruteforce(stacks[0], maxops, 0);
	stacks[1] = copy_stack(s);
	stacks[1]->ops = add_to_end(1, stacks[1]->ops);
	b(stacks[1], &swap);
	stacks[1] = bruteforce(stacks[1], maxops, 0);
	stacks[2] = copy_stack(s);
	stacks[2]->ops = add_to_end(2, stacks[2]->ops);
	r(stacks[2], &swap);
	stacks[2] = bruteforce(stacks[2], maxops, 0);
	stacks[3] = copy_stack(s);
	stacks[3]->ops = add_to_end(3, stacks[3]->ops);
	push(stacks[3]);
	stacks[3] = bruteforce(stacks[3], maxops, 0);
	stacks[4] = copy_stack(s);
	stacks[4]->ops = add_to_end(4, stacks[4]->ops);
	b(stacks[4], &push);
	stacks[4] = bruteforce(stacks[4], maxops, 0);
	stacks[5] = copy_stack(s);
	stacks[5]->ops = add_to_end(5, stacks[5]->ops);
	rot(stacks[5]);
	stacks[5] = bruteforce(stacks[5], maxops, 0);
	stacks[6] = copy_stack(s);
	stacks[6]->ops = add_to_end(6, stacks[6]->ops);
	b(stacks[6], &rot);
	stacks[6] = bruteforce(stacks[6], maxops, 0);
	stacks[7] = copy_stack(s);
	stacks[7]->ops = add_to_end(7, stacks[7]->ops);
	r(stacks[7], &rot);
	stacks[7] = bruteforce(stacks[7], maxops, 0);
	stacks[8] = copy_stack(s);
	stacks[8]->ops = add_to_end(8, stacks[8]->ops);
	rrot(stacks[8]);
	stacks[8] = bruteforce(stacks[8], maxops, 0);
	stacks[9] = copy_stack(s);
	stacks[9]->ops = add_to_end(9, stacks[9]->ops);
	b(stacks[9], &rrot);
	stacks[9] = bruteforce(stacks[9], maxops, 0);
	stacks[10] = copy_stack(s);
	stacks[10]->ops = add_to_end(10, stacks[10]->ops);
	r(stacks[10], &rrot);
	stacks[10] = bruteforce(stacks[10], maxops, 0);
	return (minops(stacks));
}

t_stack	bruteforce2(t_stack *s, int maxops, int i)
{
	t_snode	*sl;
	t_snode	*sl2;
	int		valid;

	valid = 0;
	sl = add_stack(NULL, s);
	sl2 = sl;
	if ((is_sorted2(s->a) && !s->b) || get_listsize(s->ops) >= maxops)
		return (s);
	while (i < 11)
	{
		if (check_op(s, i) && valid++)
		{
			make_op(sl->s, i);
			sl->s->ops = add_to_end(i, sl->s->ops);
			bruteforce2(sl->s, maxops, 0);
			sl = add_stack(sl, s);
		}
		i++;
	}
	return (minops2(sl2), valid);
}

