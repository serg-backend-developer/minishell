#include "../../includes/get_next_line.h"

char	*read_and_store(int fd, char *buffer_for_storing)
{
	char	*buffer;
	int		amount_bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	amount_bytes = 1;
	while (!gnl_strchr(buffer_for_storing, '\n') && amount_bytes != 0)
	{
		amount_bytes = read(fd, buffer, BUFFER_SIZE);
		if (amount_bytes == -1)
		{
			free(buffer);
			free(buffer_for_storing);
			return (NULL);
		}
		buffer[amount_bytes] = '\0';
		buffer_for_storing = gnl_strjoin(buffer_for_storing, buffer);
	}
	free(buffer);
	return (buffer_for_storing);
}

char	*extract_line(char *buffer_for_storing)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer_for_storing[i])
		return (NULL);
	while (buffer_for_storing[i] && buffer_for_storing[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer_for_storing[i] && buffer_for_storing[i] != '\n')
	{
		str[i] = buffer_for_storing[i];
		i++;
	}
	if (buffer_for_storing[i] == '\n')
	{
		str[i] = buffer_for_storing[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*update_buffer(char *rb)
{
	int		end_str_i;
	int		i;
	char	*str;

	end_str_i = 0;
	while (rb[end_str_i] && rb[end_str_i] != '\n')
		end_str_i++;
	if (!rb[end_str_i])
	{
		free(rb);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (gnl_strlen(rb) - end_str_i + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	end_str_i++;
	i = 0;
	while (rb[end_str_i])
		str[i++] = rb[end_str_i++];
	str[i] = '\0';
	free(rb);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*buffer_for_storing;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer_for_storing = read_and_store(fd, buffer_for_storing);
	if (!buffer_for_storing)
		return (NULL);
	current_line = extract_line(buffer_for_storing);
	buffer_for_storing = update_buffer(buffer_for_storing);
	return (current_line);
}
