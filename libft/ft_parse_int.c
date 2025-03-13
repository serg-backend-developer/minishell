#include "libft.h"

int	parse_integer(const char	*input_str, long	*result)
{
	int	multiplier;

	multiplier = 1;
	*result = 0;
	while (ft_isspace(*input_str))
		input_str++;
	if (*input_str == '-')
		multiplier = -multiplier;
	if (*input_str == '-' || *input_str == '+')
		input_str++;
	if (!ft_isdigit(*input_str))
		return (-1);
	while (ft_isdigit(*input_str))
	{
		*result = 10 * *result + (*input_str - '0');
		if (*result > 2147483647 && multiplier == 1)
			return (-1);
		if (*result > 2147483648 && multiplier == -1)
			return (-1);
		input_str++;
	}
	if (*input_str && !ft_isspace(*input_str))
		return (-1);
	*result *= multiplier;
	return (0);
}
