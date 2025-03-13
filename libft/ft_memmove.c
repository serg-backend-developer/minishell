#include "libft.h"

// man memmove
void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (!((char *)dest) && !((char *)src))
		return (0);
	if (dest > src)
	{
		while (len > 0)
		{
			((char *)dest)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(((char *)dest), ((char *)src), len);
	return (((char *)dest));
}
