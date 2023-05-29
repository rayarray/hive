/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <rleskine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:40:34 by rleskine          #+#    #+#             */
/*   Updated: 2023/05/24 13:14:45 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_node {
	int		data;
	void	*next;
}	t_node;

// read_args.c

t_node	*read_args(int ac, char **ag, int i, t_node *lst[2]);

// list_oprs.c

t_node	*add_node(int value);
int		append_node(int value, t_node *prev);
t_node	*get_last(t_node *lst);
t_node	*remove_node(t_node *lst);
int		destroy_list(t_node *lst);

#endif	/* PUSH_SWAP_H */
