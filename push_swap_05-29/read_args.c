/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:02:50 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/26 15:56:23 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*read_args(int ac, char **ag, int i, t_node *lst[2])
{
	lst[0] = add_node(-1);
	if (lst[0] == NULL)
		return (NULL);
	lst[1] = lst[0];
	while (++i < ac)
	{
		while (**(ag + i) != 0)
		{
			while (**(ag + i) && **(ag + i) == ' ')
				(*(ag + i))++;
			if (**(ag + i))
			{
				lst[0]->next = add_node(ft_atoi(*(ag + i)));
				lst[0] = lst[0]->next;
			}
			if (**(ag + i) && (**(ag + i) == '-' || **(ag + i) == '+'))
				(*(ag + i))++;
			while (**(ag + i) && ft_isdigit(**(ag + i)))
				(*(ag + i))++;
			if (**(ag + i) && **(ag + i) != ' '
				&& !ft_isdigit(**(ag + i)) && destroy_list(lst[1]))
				return (NULL);
		}
	}
	return (remove_node(lst[1]));
}
