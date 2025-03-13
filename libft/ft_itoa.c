#include "libft.h"

// additional function

static size_t	get_length(int n)
{
	size_t	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	long_n;

	len = get_length(n);
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	long_n = n;
	if (long_n < 0)
		long_n *= -1;
	result[len] = '\0';
	while (--len >= 0)
	{
		result[len] = long_n % 10 + '0';
		long_n /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
