/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:31:13 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/02 19:56:17 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*s;

	s = (t_stack *)malloc(sizeof(t_stack));
	if (s == NULL)
		return (NULL);
	s->a = NULL;
	s->b = NULL;
	s->i = NULL;
	s->j = NULL;
	s->ops = NULL;
	return (s);
}

t_stack	*swap(t_stack *s)
{
	if (s->a != NULL && s->a->next != NULL)
	{
		s->i = s->a->next;
		s->a->next = ((t_node *)(s->a->next))->next;
		s->i->next = s->a;
		s->a = s->i;
		s->i = NULL;
	}
	return (s);
}

t_stack	*push(t_stack *s)
{
	if (s->b != NULL && s->a == NULL)
	{
		s->a = s->b;
		if (s->a->next == NULL)
			s->b = NULL;
		else
		{
			s->b = s->a->next;
			s->a->next = NULL;
		}
	}
	else if (s->b != NULL && s->a != NULL)
	{
		s->i = s->b;
		s->b = s->b->next;
		((t_node *)(s->i))->next = s->a;
		s->a = s->i;
		s->i = NULL;
	}
	return (s);
}

t_stack	*rot(t_stack *s)
{
	if (s->a == NULL || s->a->next == NULL)
		return (s);
	s->i = get_last(s->a);
	s->i->next = s->a;
	s->a = ((t_node *)(s->a))->next;
	s->i = s->i->next;
	s->i->next = NULL;
	s->i = NULL;
	return (s);
}

t_stack	*rrot(t_stack *s)
{
	if (s == NULL || s->a == NULL || s->a->next == NULL)
		return (s);
	s->i = s->a;
	s->j = s->a->next;
	while (s->i->next && s->j->next)
	{
		s->i = s->i->next;
		s->j = s->j->next;
	}
	s->i->next = NULL;
	s->j->next = s->a;
	s->a = s->j;
	s->j = NULL;
	return (s);
}



