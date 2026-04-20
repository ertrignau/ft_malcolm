/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eric <eric@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:53:34 by eric              #+#    #+#             */
/*   Updated: 2026/04/20 13:52:32 by eric             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malcolm.h"

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
	if (ac < 5)
	{
		fprintf (stderr, "Wrong number of arguments\n");
		fprintf (stderr, "Usage: ./ft_malcom [ip] [mac adress] [target ip] [target mac adress]\n");
		return (1);
	}

		if (parse_ip(av[1], conf->spoof_ip) < 0 || parse_mac(av[2], conf->spoof_mac) < 0 || parse_ip(av[3], conf->target_ip) < 0 || parse_mac(av[4], conf->target_mac) < 0)
	{
		fprintf(stderr, "Invalid IP/MAC format\n");
		return (1);
	}
	return (0);
}
