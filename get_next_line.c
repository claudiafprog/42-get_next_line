/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:38:05 by clferrei          #+#    #+#             */
/*   Updated: 2026/05/13 10:21:35 by clferrei         ###   ########.fr       */
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
		return (free(stash), NULL);
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
		i++;
	}
	complete_line[i] = '\0';
	return (complete_line);
}

int	forward_stash(char *stash)
{
	int		i;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

char	*clean_stash(char *stash)
{
	char	*clean_s;
	int		j;
	int		len;
	int		start;

	if (!stash)
		return (NULL);
	j = 0;
	len = ft_strlen(stash);
	start = forward_stash(stash);
	if (len - start == 0)
	{
		free(stash);
		return (NULL);
	}
	clean_s = (char *)malloc(sizeof(char) * ((len - start) + 1));
	if (!clean_s)
		return (free(stash), NULL);
	while (start < len)
		clean_s[j++] = stash[start++];
	clean_s[j] = '\0';
	free(stash);
	return (clean_s);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_join(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = clean_stash(stash);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Please insert a valid argument");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
