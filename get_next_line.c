/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:12:20 by vivaccar          #+#    #+#             */
/*   Updated: 2023/11/08 16:40:59 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extractline(char *text)
{
	int		i;
	char	*line;

	i = 0;
	if (!text[i])
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		line[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
	{
		line[i] = text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_delete(char *text)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(text) - i + 1));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (text[i])
		rest[j++] = text[i++];
	rest[j] = '\0';
	free(text);
	return (rest);
}

char	*ft_read(int fd, char *text)
{
	char	*buff;
	int		bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(text, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(text);
			return (NULL);
		}
		buff[bytes] = '\0';
		text = ft_strjoin(text, buff);
	}
	free(buff);
	return (text);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	text = ft_read(fd, text);
	if (!text)
		return (NULL);
	line = ft_extractline(text);
	text = ft_delete(text);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*test;

	fd = open("test.txt", O_RDONLY);
	test = get_next_line(fd);
	printf("%s", test);
	test = get_next_line(fd);
	printf("%s", test);
 	test = get_next_line(fd);
	printf("%s", test);
 	test = get_next_line(fd);
	printf("%s", test);
	test = get_next_line(fd);
	printf("%s", test); 
 	close(fd);
	free(test);
}
 */