/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 11:04:51 by eric              #+#    #+#             */
/*   Updated: 2026/04/20 11:30:54 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

int	init_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		printf("Error in SIGINT");
		return (-1);	
	}
	return (0);
}
