#include "../../includes/get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[gnl_strlen(str)]);
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	s1_i;
	size_t	s2_i;
	char	*joined_str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	joined_str = malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	s1_i = -1;
	s2_i = 0;
	if (s1)
		while (s1[++s1_i])
			joined_str[s1_i] = s1[s1_i];
	while (s2[s2_i])
		joined_str[s1_i++] = s2[s2_i++];
	joined_str[gnl_strlen(s1) + gnl_strlen(s2)] = '\0';
	free(s1);
	return (joined_str);
}
