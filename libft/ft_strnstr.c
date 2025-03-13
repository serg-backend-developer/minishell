#include "libft.h"

// man strnstr
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	char	*haystack_pointer;

	if (!*needle)
		return ((char *) haystack);
	if (len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	haystack_pointer = (char *)haystack;
	while (*haystack_pointer && len >= needle_len)
	{
		if (ft_strncmp(haystack_pointer, needle, needle_len) == 0)
			return (haystack_pointer);
		haystack_pointer++;
		len--;
	}
	return (NULL);
}
