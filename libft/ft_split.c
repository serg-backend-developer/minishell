#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	amount;
	int	flag;

	amount = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			amount++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (amount);
}

static char	*check_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i_str;
	size_t	i_arr;
	int		i_start_word;
	char	**res;

	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (0);
	i_str = 0;
	i_arr = 0;
	i_start_word = -1;
	while (i_str <= ft_strlen(s))
	{
		if (s[i_str] != c && i_start_word < 0)
			i_start_word = i_str;
		else if ((s[i_str] == c || i_str == ft_strlen(s)) && i_start_word >= 0)
		{
			res[i_arr++] = check_word(s, i_start_word, i_str);
			i_start_word = -1;
		}
		i_str++;
	}
	res[i_arr] = 0;
	return (res);
}
