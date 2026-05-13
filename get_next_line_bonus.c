/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clferrei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:31:05 by clferrei          #+#    #+#             */
/*   Updated: 2026/05/13 10:22:00 by clferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_and_join(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
		return (NULL);
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	int		i;
	char	*line;
	int		active;

	if (argc < 2)
	{
		printf("Please insert a valid argument");
		return (1);
	}
	i = 0;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("open");
		return (1);
	}
	active = 1;
	while (active == 1)
	{
		active = 0;
		line = get_next_line(fd1);
		if (line)
		{
			printf("fd1: %s", line);
			free(line);
			active = 1;
		}
		line = get_next_line(fd2);
		if (line)
		{
			printf("fd2: %s", line);
			free(line);
			active = 1;
		}
		if (!active)
			break ;
	}
	close(fd1);
	close(fd2);
	return (0);
}*/
