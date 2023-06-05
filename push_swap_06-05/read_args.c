/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:02:50 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/30 17:20:17 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define INT_MIN	-2147483648
#define INT_MAX	2147483647

int	check_args(int ac, char **ag)
{
	char	*s;
	int		i;

	i = 0;
	while (++i < ac)
	{
		s = ag[i];
		while (s && *s != 0)
		{
			if (*s != '+' && *s != '-' && *s != ' '
				&& ft_isdigit(*s) == 0)
				return (0);
			s++;
		}
	}
	return (1);
}

int	check_digits(const char *s)
{
	int	digits;

	digits = 0;
	if (!s || *s == 0)
		return (0);
	if (*s == '+' || *s == '-')
	{
		s++;
		if (!ft_isdigit(*s))
			return (0);
	}
	while (*s == 0)
		s++;
	while (*s >= 48 && *s <= 57 && s++)
		digits++;
	if (digits > 10)
		return (0);
	return (1);
}

long int	long_atoi(const char *s)
{
	long int	value;
	int			sign;

	sign = 0;
	value = 0;
	if (check_digits(s) == 0)
		return (__LONG_MAX__);
	if ((*s == '+' && ++sign) || (*s == '-' && --sign))
		s++;
	while ((!sign && sign++) || *s == '0')
		s++;
	while (*s >= 48 && *s <= 57)
	{
		value = value * 10;
		value += *s - 48;
		s++;
	}
	return (value * sign);
}

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
				if ((long_atoi(*(ag + i)) < INT_MIN || long_atoi(*(ag + i))
						> INT_MAX) && destroy_list(lst[1]))
					return (NULL);
				lst[0]->next = add_node((int)long_atoi(*(ag + i)));
				lst[0] = lst[0]->next;
			}
			if (**(ag + i) && (**(ag + i) == '-' || **(ag + i) == '+'))
				(*(ag + i))++;
			while (**(ag + i) && ft_isdigit(**(ag + i)))
				(*(ag + i))++;
		}
	}
	return (lst[1]);
}
