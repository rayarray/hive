/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:26:21 by rleskine          #+#    #+#             */
/*   Updated: 2023/06/02 20:15:36 by rleskine         ###   ########.fr       */
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

int	get_fastest(t_stack *stack, int n)
{
	t_stack	*s[2];

	s[0] = copy_stack(stack);
	s[1] = copy_stack(stack);
	while (s[0]->a->data != n)
	{
		rot(s[0]);
		s[0]->j = add_to_end(5, s[0]->j);
	}
	while (s[1]->a->data != n)
	{
		rrot(s[1]);
		s[1]->j = add_to_end(8, s[1]->j);
	}
	if (get_listsize(s[0]->j) < get_listsize(s[1]->j))
		n = 0;
	else
		n = 1;
	free_stack(s[1]);
	free_stack(s[0]);
	return (n);
}

t_stack	*simplesort(t_stack *s, int i)
{
	t_stack	*(*op)(t_stack *);
	int		*list;
	int		size;

	size = get_listsize(s->a);
	list = cnv_to_arr(s->a);
	quicksort(list, 0, size - 1);
	while (i < (size - 1))
	{
		if (1 || get_fastest(s, list[i]) == 0)
			op = &rot;
		else
			op = &rrot;
		while (s->a->data != list[i])
		{
			a(s, op, 1);
		}
		b(s, &push, 1);
		i++;
		if (is_sorted(s->a))
			break ;
		else if (s->a && s->a->next && !((t_node *)(s->a->next))->next)
		{
			a(s, &swap, 1);
			break ;
		}
	}
	while (s->b)
		a(s, &push, 1);
	free(list);
	return (s);
}
