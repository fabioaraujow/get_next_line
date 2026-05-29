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

char	*get_next_line(int fd)
{
	static char	*storage_box;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_search_new_line(fd, &storage_box);
	if (!storage_box)
		return (NULL);
}
