/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:48:54 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/02 12:58:32 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_node *n, char c)
{
	if (c)
		ft_printf("%c: ", c);
	if (n == NULL)
	{
		ft_printf("\n");
		return ;
	}
	ft_printf("[%d]", n->data);
	if (n->next != NULL)
	{
		ft_printf("->");
		print_stack(n->next, 0);
	}
	else
		ft_printf("\n");
}

void	print_ops(t_node *n)
{
	char	**ops;

	ops = (char *[11]){"sa", "sb", "ss", "pa", "pb", "ra", "rb",
		"rr", "rra", "rrb", "rrr"};
	while (n)
	{
		if (n->data >= 0 && n->data <= 10)
			ft_printf("%s\n", ops[n->data]);
		n = n->next;
	}
}

void	printlist(t_node *lst)
{
	while (lst)
	{
		ft_printf("[%d]", lst->data);
		if (lst->next)
			ft_printf("->");
		lst = lst->next;
		if (lst == NULL)
			ft_printf("\n");
	}
}
