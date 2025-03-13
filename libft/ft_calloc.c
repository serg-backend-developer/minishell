#include "libft.h"

// man calloc
void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	size_t	len;

	len = count * size;
	if (count != 0 && len / count != size)
		return (NULL);
	pointer = malloc(len);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, len);
	return (pointer);
}
