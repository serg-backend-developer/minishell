#include "../../includes/minishell.h"

static void	print_string_array(char **array);
static char	**sort_string_array(char **array);

char	**convert_env_list_to_array(t_minishell **minishell)
{
	t_list	*env_list;
	char	**env_array;
	int		index;
	int		size;

	if (minishell == NULL || *minishell == NULL)
		return (NULL);
	index = 0;
	env_list = (*minishell)->envs;
	size = ft_lstsize(env_list) + 1;
	env_array = (char **)(malloc(sizeof(char *) * size));
	if (env_array == NULL)
	{
		perror("Malloc failed");
		return (NULL);
	}
	while (env_list)
	{
		env_array[index] = (char *)env_list->content;
		env_list = env_list->next;
		index++;
	}
	env_array[index] = NULL;
	return (env_array);
}

void	handle_export_no_args(t_minishell **minishell)
{
	char	**env_array;

	env_array = convert_env_list_to_array(minishell);
	env_array = sort_string_array(env_array);
	print_string_array(env_array);
	free(env_array);
}

static void	print_string_array(char **array)
{
	int		index;
	char	*env_value;
	char	*env_name;

	index = 0;
	while (array[index])
	{
		env_name = retrieve_env_name(array[index]);
		env_value = ft_substr(array[index], ft_strlen(env_name) + 1,
				ft_strlen(array[index]));
		printf("declare -x %s=\"%s\"\n", env_name, env_value);
		free(env_name);
		free(env_value);
		index++;
	}
}

static char	**sort_string_array(char **array)
{
	int		index1;
	int		index2;
	char	*temp;

	index1 = 0;
	while (array[index1])
	{
		index2 = index1 + 1;
		while (array[index2])
		{
			if (ft_strcmp(array[index1], array[index2]) > 0)
			{
				temp = array[index1];
				array[index1] = array[index2];
				array[index2] = temp;
			}
			index2++;
		}
		index1++;
	}
	return (array);
}
