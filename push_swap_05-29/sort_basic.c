/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:26:21 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/29 16:07:04 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	intswap(int *a, int *b)
{
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

int	partition(int arr[], int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			intswap(&arr[i], &arr[j]);
		}
		j++;
	}
	intswap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quicksort(int arr[], int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(arr, low, high);
		quicksort(arr, low, pivot - 1);
		quicksort(arr, pivot + 1, high);
	}
}

t_stack	*simplesort(t_stack *s, int i)
{
	int	*list;
	int	size;

	i = 0;
	s->ops = NULL;
	size = get_listsize(s->a);
	list = cnv_to_arr(s->a);
	//for (int j = 0; j < size; j++)
	//	ft_printf("[%d:%d]", j, list[j]);
	//ft_printf("\n");
	quicksort(list, 0, size - 1);
	//for (int j = 0; j < size; j++)
	//	ft_printf("[%d:%d]", j, list[j]);
	while (i < (size - 1))
	{
		while (s->a->data != list[i])
		{
			rot(s);
			s->ops = add_to_end(5, s->ops);
		}
		b(s, &push);
		s->ops = add_to_end(4, s->ops);
		i++;
	}
	while (s->b)
	{
		push(s);
		s->ops = add_to_end(3, s->ops);
	}
	free(list);
	return (s);
}