/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _zalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwordes <iwordes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:37:39 by iwordes           #+#    #+#             */
/*   Updated: 2017/04/09 18:40:10 by iwordes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libtp_.h>

void	*tp__zalloc(size_t n)
{
	char	*mem;
	size_t	i;

	if ((mem = (char*)malloc(n)) == NULL)
		return (NULL);
	while (n - i >= 8)
	{
		*(uint64_t*)(mem + i) = 0;
		i += 8;
	}
	while (i < n)
		mem[i++] = 0;
	return (mem);
}
