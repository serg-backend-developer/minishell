#include "libft.h"

// man memchr
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_pointer;

	s_pointer = (unsigned char *)s;
	while (n && (unsigned char)*s_pointer != (unsigned char)c)
	{
		s_pointer++;
		n--;
	}
	if (n)
		return (s_pointer);
	else
		return (NULL);
}
