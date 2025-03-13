#include "libft.h"

// additional function
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	char	*result_pointer;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		result = malloc(1 * sizeof(char));
		if (!result)
			return (NULL);
		*result = '\0';
		return (result);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result_pointer = result;
	s += start;
	while (*s && len--)
		*result_pointer++ = *s++;
	*result_pointer = '\0';
	return (result);
}
