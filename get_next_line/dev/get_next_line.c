/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:37:57 by rleskine          #+#    #+#             */
/*   Updated: 2022/12/09 10:25:31 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	free_data(void)
{
	static void	**data;
	int			arraysize;
	int			i;

	i = 0;
	if (*data != NULL)
	{
		arraysize = *(int *)*(void **)data;
		while (*(data + i) != NULL && i < arraysize)
			free(*(data + i++));
	}
	free(data);
	return (1);
}

char	*resize_str(char *src)
{
	char			*dst;
	unsigned int	size;

	size = 0;
	while (*(src + size) != NULL)
		size++;
	dst = (char *)malloc((size * 2) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	size++;
	*(dst + size) = NULL;
	while (size > 0)
		*(dst + size - 1) = *(src + size - 1);
	return (dst);
}

int	init_data(int fd, int arraysize, int i, void **resize)
{
	static void	**data;

	if (data == NULL)
	{
		data = (void **)malloc((arraysize) * sizeof(void *));
		*data = (void *)malloc(sizeof(int));
		if (data == NULL || (*data == NULL && free_data()) )
			return (0);
		*(int *)*data = arraysize;
		*(void **)(data + sizeof(void **)) = NULL;
	}
	arraysize = *(int *)*(void **)data;
	i = 1;
	while (i++ < arraysize)
		if (*(void **)data == NULL || *(int *)*(void **)(data + (sizeof(void *) * i)) == fd)
			return (1);
	resize = (void **)malloc((2 * arraysize) * sizeof(void *));
	if (resize == NULL && free_data())
		return (0);
	*(resize + (sizeof(void **) * (arraysize + 1))) = NULL;
	while (i-- > 1)
		*(resize + (sizeof(void **) * i)) = *(data + (sizeof(void **) * i));
	*(int *)*resize = arraysize * 2;
	data = resize;
	return(1);
}

char	*copy_next_line(t_nextline nextline)
{
	static void	**data;

	
}

char	*get_next_line(int fd)
{
	static void	**data;
	t_nextline	nextline;

	#ifdef BUFFER_SIZE
	nextline->bufsize = BUFFER_SIZE;
	#else
	nextline->bufsize = 42;
	#endif
	nextline->linesize = 256;
	nextline->linepos = 0;
	nextline->line = (char *)malloc(linesize * sizeof(char));
	if (nextline->line == NULL)
		return(NULL);

	init_data();
	init_nextline();
	read_data();
	cleanup_if_eof();

	return(NULL);
}
