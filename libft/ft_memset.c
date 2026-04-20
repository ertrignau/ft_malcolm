/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 15:25:20 by eric              #+#    #+#             */
/*   Updated: 2026/04/16 15:25:23 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	size_t			i;
	unsigned char	*pointeur;

	i = 0;
	pointeur = (unsigned char *)ptr;
	while (i < len)
	{
		pointeur[i] = (unsigned char) value;
		i++;
	}
	return (pointeur);
}
