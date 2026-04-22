/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:36 by eric              #+#    #+#             */
/*   Updated: 2026/04/22 12:03:55 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

volatile sig_atomic_t g_signal = 0;

void	signal_handler(int signal)
{
	(void)signal;
	g_signal = 1;
	printf("\nExiting ft_malcolm ...\n");
}

int main(int ac, char *av[])
{
	int		sockfd;
	char	*iface;
	uint8_t	mac[6];
	t_config	conf;
	init_signals();
	// 1. Parse arguments (sender_ip, sender_mac, target_ip, target_mac)
	if (parse_args(ac, av, &conf) != 0)
		return (1);
	// 2. Trouver interface
	iface = get_interface_info();
	if (!iface)
	{
		printf("Error: no interface found\n");
		return (1);
	}
	printf("Using interface: %s\n", iface);
	// 3. Récupérer MAC locale
	if (get_local_mac(iface, mac) == -1)
	{
		fprintf(stderr, "Error: failed to get MAC address\n");
		free(iface);
		return (1);
	}
	printf("Local MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
		mac[0], mac[1], mac[2],
		mac[3], mac[4], mac[5]);
	// 4. Créer socket RAW
	sockfd = create_socket();
	// 5. Sniff and respond to ARP requests
	sniff_arp(sockfd, iface, &conf);
	close(sockfd);
	free(iface);
	return (0);
}
