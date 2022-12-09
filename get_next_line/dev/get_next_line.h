/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:58:45 by rleskine          #+#    #+#             */
/*   Updated: 2022/12/09 10:02:42 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

typedef struct s_nextline
{
	char			*line;
	unsigned int	linesize;
	unsigned int	linepos;
	unsigned int	bufsize;
}	t_nextline;

char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
