/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:08 by eric              #+#    #+#             */
/*   Updated: 2026/04/16 13:23:08 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

// void	free_entry(t_entry *entry)
// {
// 	t_entry	*tmp;
// 	while (entry)
// 	{
// 		tmp = entry->next;
// 		free(entry);
// 		entry = tmp;
// 	}
// }

void	print_mac(uint8_t mac[6])
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

void	print_ip(uint8_t ip[4])
{
	printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}

void	print_arp(t_arp *arp)
{
	printf("ARP packet:\n");
	printf("	Sender MAC: ");
	print_mac(arp->sender_mac);
	printf (" | Sender IP: ");
	print_ip(arp->sender_ip);
	printf("\n  Target MAC: ");
	print_mac(arp->target_mac);
	printf(" | Target IP: ");
	print_ip(arp->target_ip);
	printf("\n");
}

int	hex_char_to_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}
