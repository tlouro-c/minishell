/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_v2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:01:27 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/20 00:48:15 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlenm(char const *s1)
{
	int	i;

	if (s1 == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char	*ft_strjoinm(char const *s1, char const *s2, int *flag)
{
	char	*s3;
	int		j;
	int		i;

	s3 = (char *)malloc(ft_strlenm(s1) + ft_strlenm(s2) + 1);
	if (!s3)
		return (s3);
	j = 0;
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
		s3[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		if (s2[i] == '\n')
		{
			*flag = 1;
			break ;
		}
		s3[j++] = s2[i++];
	}
	s3[j] = '\0';
	return (s3);
}

static void	buffer_clear(char *buffer)
{
	int	j;
	int	i;

	i = 0;
	j = -1;
	while (buffer[i])
	{
		if (j != -1)
			buffer[j++] = buffer[i];
		else if (j == -1 && buffer[i] == '\n')
			j = 0;
		buffer[i++] = '\0';
	}
}

static int	line_updater(char **line, char buffer[])
{
	char	*join;
	int		flag;

	flag = 0;
	join = ft_strjoinm(*line, buffer, &flag);
	free(*line);
	*line = join;
	if (*line == NULL)
		return (-1);
	return (flag);
}

char	*ft_get_next_line_v2(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			flag;
	int			read_result;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			read_result = read(fd, buffer, BUFFER_SIZE);
			if (read_result == -1)
				return (ft_free_str_return(line));
			if (read_result == 0)
				return (line);
		}
		flag = line_updater(&line, buffer);
		buffer_clear(buffer);
		if (flag == 1 || flag == -1)
			return (line);
	}
}
