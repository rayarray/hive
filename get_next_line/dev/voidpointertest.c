/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voidpointertest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rleskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:40:23 by rleskine          #+#    #+#             */
/*   Updated: 2022/12/07 16:27:51 by rleskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	static void	*vp;
	void		*vpstart;
	int			fd;
	int			pos;
//	int			ret;
	int			i;
	char		buf[128];

	memset(buf, 48, 128);
	buf[30] = 't';
	buf[31] = 's';
	buf[32] = 't';
	memset((void *)&buf[64], 49, 32);
	memset(&buf[96], 50, 16);
	pos = 24;
	fd = 3;
	vp = (void *)malloc((sizeof(int) * 2) + (sizeof(char) * 128));
	vpstart = vp;
	*(int *)vp = fd;
	vp = vp + sizeof(int);
	*(int *)vp = pos;
	vp = vp + sizeof(int);
	i = 0;
	while (i < 128)
	{
		*(char *)vp = buf[i];
		vp = vp + sizeof(char);
		i++;
	}
	
	printf("first int: [%i]\n", *(int *)vpstart);
	vpstart = vpstart + sizeof(int);
	printf("second int: [%i]\n", *(int *)vpstart);
	vpstart = vpstart + sizeof(int);
	i = 0;
	while (i < 128)
	{
		printf("%c", *(char *)vpstart);
		vpstart = vpstart + sizeof(char);
		i++;
	}
	printf("\n");
}
