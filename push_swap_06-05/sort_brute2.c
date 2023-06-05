/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_brute2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:20:57 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/02 18:38:08 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_brute	*init_brute(int maxops)
{
	t_brute	*b;

	b = (t_brute *)malloc(sizeof(t_brute));
	if (b == NULL)
		return (NULL);
	b->n = NULL;
	b->maxops = maxops;
	b->rec = 0;
	return (b);
}

void	get_bestsolve(t_brute *b, t_stack *s)
{
	destroy_list(s->ops);
	s->ops = b->n;
	free(b);
}
