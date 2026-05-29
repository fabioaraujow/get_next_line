#include "get_next_line.h"

char	*ft_search_newliwe(int fd, char **storage_box)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	bytes_read = 1;
	while ((bytes_read > 0) && (ft_strchr(*storage_box, '\n') == NULL))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = *storage_box;
		*storage_box = ft_strjoin(*storage_box, buffer);
		free(temp);
		free(buffer);
	}
	return (*storage_box);
}

int	ft_getlen(int pos, char *s)
{
	while (s[pos])
		pos++;
	return (pos);
}

char	*get_next_line(int fd)
{
	static char	*storage_box;
	char		*to_print;
	int			newline_pos;
	int			find_null;

	newline_pos = 0;
	find_NULL = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_search_new_line(fd, &storage_box);
	if (!storage_box)
		return (NULL);
	newline_pos = ft_strchr(storage_box, '\n') - storage_box;
	to_print = ft_substr(storage_box, 0, (newline_pos + 1));
	find_NULL = ft_getlen(newline_pos, storage_box);
	storage_box = ft_substr(storage_box, (newline_pos + 1), find_null);
	return (to_print);
}
