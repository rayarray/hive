/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:39:41 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/05 12:58:57 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rdx_revalue(t_node *n, int size, int i)
{
	int	*arr;

	arr = cnv_to_arr(n);
	quicksort(arr, 0, size - 1);
	while (n)
	{
		i = 0;
		while (n->data != arr[i])
			i++;
		n->data = i;
		n = n->next;
	}
	free(arr);
}
