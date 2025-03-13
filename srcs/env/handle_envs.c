#include "../../includes/minishell.h"

char	*retrieve_env_name(char *env_entry)
{
	int		index;
	char	*env_name;

	if (!env_entry)
		return (NULL);
	index = 0;
	while (env_entry && env_entry[index] && env_entry[index] != '=')
		index++;
	env_name = ft_substr(env_entry, 0, index);
	return (env_name);
}

char	*retrieve_env_value(t_list *env_list, char *key)
{
	char	*env_name;
	char	*env_value;

	if (!env_list || !key)
		return (NULL);
	while (env_list)
	{
		env_name = retrieve_env_name(env_list->content);
		if (!ft_strcmp(env_name, key))
		{
			env_value = ft_substr(env_list->content, ft_strlen(env_name) + 1,
					ft_strlen(env_list->content));
			free(env_name);
			return (env_value);
		}
		free(env_name);
		env_list = env_list->next;
	}
	return (NULL);
}
