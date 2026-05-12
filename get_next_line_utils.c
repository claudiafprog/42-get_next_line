/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:24:33 by clferrei          #+#    #+#             */
/*   Updated: 2026/05/12 12:21:05 by clferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	totallen;
	char	*joined;
	int		i;
	int		j;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	totallen = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (totallen + 1));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		joined[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		joined[j++] = s2[i++];
	joined[j] = '\0';
	return (joined);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	while (*str != '\0' && *str != (char)c)
		str++;
	if (*str == (char)c)
		return (str);
	else
		return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t		len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
