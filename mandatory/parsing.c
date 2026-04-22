/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:34 by eric              #+#    #+#             */
/*   Updated: 2026/04/22 13:19:08 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"
#include <getopt.h>
#include <stdlib.h>

int	parse_ip(const char *s, uint8_t ip[4])
{
	int	i;		// pos dans la chaine
	int	part;	// indice du bloc IP qu'on remplit
	int	val;	// valeur numerique

	i = 0;
	part = 0;
	val = 0;		
	while (s[i])
	{
		if (s[i] == '.')
		{
			if (part >= 4 || val < 0 || val > 255)
				return (-1);
			ip[part++] = (uint8_t)val;
			val = 0;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			val = val * 10 + (s[i] - '0');
			if (val > 255)
				return (-1);
		}
		else	
			return (-1);
		i++;
	}
	if (part != 3 || val <  0 || val > 255)
		return (-1);
	ip[part] = (uint8_t)val;
	return (0);
}

int parse_mac(const char *s, uint8_t mac[6])
{
	int	i;
	int	part;	// indice de l'octet MAC
	int	hi;		// valeur du 1er caractere hexa
	int	lo;		// valeur du 2e caractere hexa

	i = 0;
	part  = 0;
	while (s[i] && part < 6)
	{
		hi = hex_char_to_val(s[i++]);
		if (hi < 0 || !s[i])
			return (-1);
		lo = hex_char_to_val(s[i++]);
		if (lo < 0)
			return (-1);
		mac[part++] = (uint8_t)((hi << 4) | lo);
		if (s[i] == ':')
			i++;
		else if (s[i] != '\0' && part < 6)
			return (-1);
	}
	if (part != 6 || s[i] != '\0')
		return (-1);
	return (0);
}

int	parse_args(int ac, char *av[], t_config *conf)
{
	int		opt;
	int		required_args = 0;

	// Initialiser les flags
	conf->continuous = 0;
	conf->verbose = 0;

	// Traiter les options
	while ((opt = getopt(ac, av, "hcV")) != -1)
	{
		switch (opt)
		{
			case 'h':
				print_help(av[0]);
				exit(0);
			case 'c':
				conf->continuous = 1;
				break;
			case 'V':
				conf->verbose = 1;
				break;
			default:
				fprintf(stderr, "Unknown option: -%c\n", opt);
				return (1);
		}
	}

	// Vérifier les arguments positionnels (après les options)
	required_args = ac - optind;
	if (required_args < 4)
	{
		fprintf(stderr, "Wrong number of arguments\n");
		print_help(av[0]);
		return (1);
	}

	// Parser les arguments: target_ip, target_mac, gateway_ip, gateway_mac
	if (parse_ip(av[optind], conf->spoof_ip) < 0 || 
		parse_mac(av[optind + 1], conf->spoof_mac) < 0 || 
		parse_ip(av[optind + 2], conf->target_ip) < 0 || 
		parse_mac(av[optind + 3], conf->target_mac) < 0)
	{
		fprintf(stderr, "Invalid IP/MAC format\n");
		return (1);
	}

	return (0);
}

void	print_help(const char *prog_name)
{
	printf("Usage: %s [OPTIONS] <spoof_ip> <spoof_mac> <target_ip> <target_mac>\n\n", prog_name);
	printf("Perform ARP spoofing attack\n\n");
	printf("Arguments:\n");
	printf("  <spoof_ip>        IP address to spoof (e.g., 192.168.1.1)\n");
	printf("  <spoof_mac>       MAC address to use (e.g., aa:bb:cc:dd:ee:ff)\n");
	printf("  <target_ip>       Target IP address (e.g., 192.168.1.100)\n");
	printf("  <target_mac>      Target MAC address\n\n");
	printf("Options:\n");
	printf("  -h                Display this help message\n");
	printf("  -c                Continuous mode (keep spoofing)\n");
	printf("  -V                Verbose mode (show debug messages)\n");
}
