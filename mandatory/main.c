/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:36 by eric              #+#    #+#             */
/*   Updated: 2026/04/17 16:30:42 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

int main(int ac, char *av[])
{
	int		sockfd;
	char	*iface;
	uint8_t	mac[6];
	t_arp	arp;
	// 1. Parse arguments (sender_ip, sender_mac, target_ip, target_mac)
	if (parse_args(ac, av, &arp) != 0)
	{
		return (1);
	}
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
		printf("Error: failed to get MAC address\n");
		free(iface);
		return (1);
	}
	printf("Local MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
		mac[0], mac[1], mac[2],
		mac[3], mac[4], mac[5]);

	// 4. Créer socket RAW
	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockfd < 0)
	{
		perror("socket");
		free(iface);
		return (1);
	}
	printf("Spoofing ARP: claiming %d.%d.%d.%d is at %02x:%02x:%02x:%02x:%02x:%02x\n",
		arp.sender_ip[0], arp.sender_ip[1], arp.sender_ip[2], arp.sender_ip[3],
		arp.sender_mac[0], arp.sender_mac[1], arp.sender_mac[2], 
		arp.sender_mac[3], arp.sender_mac[4], arp.sender_mac[5]);
	// 6. Sniff and respond to ARP requests
	sniff_arp(sockfd, iface, &arp);
	close(sockfd);
	free(iface);
	return (0);
}
