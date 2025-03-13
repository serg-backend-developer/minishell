#include "libft.h"

// additional function
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	start;
	size_t	finish;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	finish = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == finish + 1)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[finish]))
		finish--;
	trimmed = ft_substr(s1, start, finish - start + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
