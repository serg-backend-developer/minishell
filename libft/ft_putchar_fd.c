#include "libft.h"

// additional function
int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}
