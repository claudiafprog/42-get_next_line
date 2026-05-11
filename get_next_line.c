/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:38:05 by clferrei          #+#    #+#             */
/*   Updated: 2026/05/11 16:28:39 by clferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_join(int fd, char	*stash)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		if (!stash)
			return (NULL);
		free(temp);
		if (ft_strchr(stash, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes == -1)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*complete_line;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	complete_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!complete_line)
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		complete_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		complete_line[i] = '\n';
		complete_line[i + 1] = '\0';
		i++;
	}
	return (complete_line);
}

//To be continued...
