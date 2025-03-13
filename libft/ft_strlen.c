#include "libft.h"

// man strlen
size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}
