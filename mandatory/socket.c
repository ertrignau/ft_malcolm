/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:11 by eric              #+#    #+#             */
/*   Updated: 2026/04/17 15:36:27 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

int	create_socket(void)
{
	int sockfd;
	
	sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sockfd < 0)
	{
		fprintf(stderr, "Error in create_socket\n");
		return (-1);
	}
	return (sockfd);
}

char	*get_interface_info()
{
	struct ifaddrs	*ifaddr;
	struct ifaddrs	*tmp;
	char			*iface;

	iface = NULL;
	if (getifaddrs(&ifaddr) == -1)
		return (NULL);
	tmp = ifaddr;
	while (tmp)
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET)
		{
			if (ft_strcmp(tmp->ifa_name, "lo") != 0)
			{
				iface = ft_strdup(tmp->ifa_name);
				if (!iface)
					return (NULL);
				break;
			}
		}
		tmp = tmp->ifa_next;
	}
	freeifaddrs(ifaddr);
	return (iface);
}

int	get_local_mac(const char *iface, uint8_t mac[6])
{
	struct ifaddrs		*ifaddr;
	struct ifaddrs		*tmp;
	struct sockaddr_ll	*s;

	if (getifaddrs(&ifaddr) == -1)
		return (-1);
	tmp = ifaddr;
	while (tmp)
	{
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_PACKET && ft_strcmp(tmp->ifa_name, iface) == 0)
		{
			s = (struct sockaddr_ll *)tmp->ifa_addr;
			ft_memcpy(mac, s->sll_addr, 6);
			freeifaddrs(ifaddr);
			return (0);
		}
		tmp = tmp->ifa_next;
	}
	freeifaddrs(ifaddr);
	return (-1);	
}
