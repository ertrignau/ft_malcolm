/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malcolm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 11:05:11 by eric              #+#    #+#             */
/*   Updated: 2026/04/16 11:22:13 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALCOLM_H
#define MALCOLM_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <net/if_packet.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <signal.h>
#include <time.h>

#include "libft/libft.h"

#define ARP_REQUEST 1
#define ARP_REPLY	2
#define BUFFER_SIZE 2048

/*Structure header Ethernet, qui est le debut de tous les paquets reseaux LAN*/
typedef struct s_ethernet
{
	uint8_t			dst_mac[6];	 	// -> 6 bytes, MAC du destinataire	AA:BB:CC:DD:EE:FF
	uint8_t			src_mac[6]; 	// -> 6 bytes, MAC de l'emeteur 	11:22:33:44:55:66
	uint16_t		type;			// -> 2 bytes, 0x0800 = IPv4, 0x0806 = ARP, 0x86DD = IPv6
} __attribute__((packed)) t_ethernet;

/*Structure ARP pour le contenu du paquet Address Rsolution Protocol*/
typedef struct s_arp
{
	uint16_t		htype;			// -> type de reseau		(Ethernet)
	uint16_t		ptype;			// -> protocole du reseau	(IPv4)
	uint8_t			hlen;			// -> taille de l'adresse hardware
	uint8_t			plen;			// -> taille de l'adresse protocole
	uint16_t		opcode;			// -> type de paquet ARP (request/reply)
	uint8_t			sender_mac[6];	// -> mac de l'emetteur (11:22:33:44:55:66)
	uint8_t			sender_ip[4];	// -> ip de l'emetteur	(192.168.1.1)
	uint8_t			target_mac[6];	// -> mac vise
	uint8_t			target_ip[4];	// -> ip vise
} __attribute__((packed)) t_arp;

/*Sert a memoriser les associations IP->MAC en liste chainee pour stocker plusieurs machines*/
typedef struct s_entry
{
	uint8_t			ip[4];
	uint8_t			mac[6];
	struct s_entry	*next;
} t_entry;


/*INIT*/
t_entry *add_entry(t_entry **table, uint8_t *ip, uint8_t *mac);


#endif