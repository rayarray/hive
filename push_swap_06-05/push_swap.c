/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:59:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/05 14:10:34 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	dup_check(t_node *lst)
{
	t_node	*next;

	if (!lst)
		return (0);
	next = lst->next;
	while (next)
	{
		if (lst->data == next->data)
			return (1);
		next = next->next;
	}
	if (lst->next == NULL)
		return (0);
	else
		return (dup_check(lst->next));
}

int	main(int ac, char **ag)
{
	t_stack	*s;
	t_stack	*srt;
	int		maxops;

	s = init_stack();
	//for (int i = 0; i < ac; i++)
	//	ft_printf("%d: %s\n", i, *(ag + i));
	if (check_args(ac, ag))
		s->a = read_args(ac, ag, 0, (t_node *[2]){NULL, NULL});
	//printlist(s->a);
	if ((!s->a || dup_check(s->a) || !check_args(ac, ag)))
	{
		write(2, &"Error\n", 6);
		return (free_stack(s));
	}
	s->i = s->a;
	s->a = s->a->next; // free the first node
	free(s->i);
	s->i = NULL;
	if (s->a == NULL || (is_sorted(s->a)))
		return (free_stack(s) - 1);
	srt = copy_stack(s);
	//simplesort(srt, 0);
	radix(srt, get_listsize(srt->a), 0, 0);
	//rdx_revalue(srt->a, get_listsize(srt->a), 0);
	//bruteforce3(srt, init_brute(9), 0);
	maxops = get_listsize(srt->ops);
	//print_stack(srt->a, 'a');
	//ft_printf("ops:%d\n", maxops);
	print_ops(srt->ops);
	//bruteforce(s, maxops, 0);
	//ft_printf("brute:%d\n", get_listsize(s->ops));
	free_stack(s);
	free_stack(srt);
	maxops = 0;
}
