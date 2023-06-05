/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:48:34 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/05 18:31:42 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*pushback(t_stack *s, int size, int bits, int last)
{
	while (size--)
	{
		if (bits < last && ((s->b->data >> bits) & 1) == 0)
			b(s, &rot, 1);
		else
			a(s, &push, 1);
	}
	return (s);
}

t_stack	*radix(t_stack *s, int size, int bits, int i)
{
	int	j;

	rdx_revalue(s->a, size, 0);
	j = 0;
	while (((size - 1) >> bits) > 0)
		bits++;
	// ft_printf("size = %d, bits = %d", size, bits);
	while (j < bits)
	{
		i = 0;
		//while (i++ < get_listsize(s->b))
		//	a(s, &rot, 1);
		i = 0;
		while (i < size)
		{
			if ((s->a->data >> j) & 1)
				a(s, &rot, 1);
			else
				b(s, &push, 1);
			i++;

		}
		ft_printf("step %d\n", j);
		print_stack(s->a, 'a');
		print_stack(s->b, 'b');
		while (s->b)
			a(s, &push, 1);
		//pushback(s, get_listsize(s->b), j + 1, bits);
		j++;
		ft_printf("after:\n");
		print_stack(s->a, 'a');
		print_stack(s->b, 'b');
	}
	return (s);
}
