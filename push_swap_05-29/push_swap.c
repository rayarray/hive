/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:59:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/29 16:06:42 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_node *n, char c)
{
	if (c)
	{
		ft_printf("%c: ");
		c = 0;
	}
	if (n != NULL)
		ft_printf("[%d]", n->data);
	if (n->next != NULL)
	{
		ft_printf("->");
		print_stack(n->next, 0);
	}
	else
		ft_printf("\n");
}

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

int	main(int ac, char **ag)
{
	t_stack	*s;
	//t_node	*tmp;
	t_stack	*srt;
	int		maxops;

	s = init_stack();
	//for (int i = 0; i < ac; i++)
	//	ft_printf("%d: %s\n", i, *(ag + i));
	s->a = read_args(ac, ag, 0, (t_node *[2]){NULL, NULL});
	if (s->a == NULL)
		ft_printf("stack is null");
	printlist(s->a);
	// ft_printf("dup_check:%d\n", dup_check(s->a, s->a->next));
	// ft_printf("is_sorted:%d\n", is_sorted(s->a));
	// ft_printf("is_sorted2:%d\n", is_sorted2(s->a));
	srt = copy_stack(s);
	//srt = bruteforce(s, 0);
	//print_stack(srt->i, 'i');
	simplesort(srt, 0);
	maxops = get_listsize(srt->ops);
	ft_printf("ops:%d\n", maxops);
	bruteforce(s, maxops, 0);
	ft_printf("brute:%d\n", get_listsize(s->ops));
}
