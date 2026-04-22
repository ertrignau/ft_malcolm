/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:15:05 by eric              #+#    #+#             */
/*   Updated: 2026/04/22 11:52:01 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);
int		ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *ptr, const	void *ptr2, size_t num);
void	*ft_memset(void *ptr, int value, size_t len);

#endif