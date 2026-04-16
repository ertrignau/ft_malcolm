/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:36 by eric              #+#    #+#             */
/*   Updated: 2026/04/16 14:01:11 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

int main(int ac, char *av[])
{
	(void)av;
	if (ac < 1)
		printf("Not enough arguments\n");
	char *iface = get_interface_info();
	if (!iface)
	{
		printf("No interface\n");
		return (1);
	}
	printf("Interface found: %s\n", iface);
	free(iface);
	return (0);
}
