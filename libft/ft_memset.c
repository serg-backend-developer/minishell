#include "libft.h"

// man memset
void	*ft_memset(void *str, int value, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) str)[i] = value;
		i++;
	}
	return (str);
}
