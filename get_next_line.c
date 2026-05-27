#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*storage_box;
	char			*temp;
	char			*buffer;
	int				b_read;

	b_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((b_read > 0) && (ft_strchr(storage_box, '\n') == NULL))
	{
			buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
			if (!buffer)
				return (NULL);
			b_read = read(fd, buffer, BUFFER_SIZE);
			if (b_read == -1)
			{
				free(buffer);
				return (NULL);
			}
			buffer[b_read] = '\0';
			temp = storage_box;
			storage_box = ft_strjoin(storage_box, buffer);
			free(buffer);
			free(temp);
	}
}
