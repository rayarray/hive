/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 09:59:29 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 13:28:38 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **ag)
{
	t_node	*s_a;

	for (int i = 0; i < ac; i++)
		ft_printf("%d: %s\n", i, *(ag + i));
	s_a = read_args(ac, ag, 0, (t_node *[2]){NULL, NULL});
	if (s_a == NULL)
		ft_printf("stack is null");
	while (s_a)
	{
		ft_printf("[%d]", s_a->data);
		s_a = s_a->next;
		if (s_a)
			ft_printf("->");
	}
	ft_printf("\n");
}
