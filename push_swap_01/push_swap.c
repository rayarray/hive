/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:59:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/25 13:25:06 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **ag)
{
	t_node	*s_a;
	t_node	*tmp;

	for (int i = 0; i < ac; i++)
		ft_printf("%d: %s\n", i, *(ag + i));
	s_a = read_args(ac, ag, 0, (t_node *[2]){NULL, NULL});
	tmp = s_a;
	if (s_a == NULL)
		ft_printf("stack is null");
	while (tmp)
	{
		ft_printf("[%d]", tmp->data);
		tmp = tmp->next;
		if (tmp)
			ft_printf("->");
	}
	ft_printf("\n");
	ft_printf("dup_check:%d", dup_check(s_a, s_a->next));
}
