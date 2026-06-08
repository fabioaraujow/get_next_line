/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabde-ar <fabde-ar@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:25:11 by fabde-ar          #+#    #+#             */
/*   Updated: 2026/06/08 10:25:13 by fabde-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_clean(char **storage_box)
{
	free(*storage_box);
	*storage_box = NULL;
	return (NULL);
}

char	*ft_search_newline(int fd, char **storage_box)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while ((bytes_read > 0) && (!ft_strchr(*storage_box, '\n')))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (ft_clean(storage_box));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (ft_clean(storage_box));
		}
		buffer[bytes_read] = '\0';
		temp = *storage_box;
		*storage_box = ft_strjoin(*storage_box, buffer);
		free(temp);
		free(buffer);
	}
	return (*storage_box);
}

char	*get_next_line(int fd)
{
	static char	*storage_box;
	char		*to_print;
	char		*temp;
	int			newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_search_newline(fd, &storage_box);
	if (!storage_box || !*storage_box)
		return (free(storage_box), storage_box = NULL, NULL);
	if (!ft_strchr(storage_box, '\n'))
		newline_pos = ft_strlen(storage_box);
	else
		newline_pos = (ft_strchr(storage_box, '\n') - storage_box + 1);
	to_print = ft_substr(storage_box, 0, newline_pos);
	if (!to_print)
		return (ft_clean(&storage_box));
	temp = storage_box;
	storage_box = ft_substr(storage_box, newline_pos,
			ft_strlen(storage_box) - newline_pos);
	free(temp);
	return (to_print);
}
