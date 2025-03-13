#include "../../includes/minishell.h"

static char	*form_command_path(char *path, char *cmd);

char	*find_command_path(t_list *envs, char *cmd)
{
	int		index;
	char	**path_dirs;
	char	*command_path;

	while (envs)
	{
		if (!ft_strncmp(envs->content, "PATH=", 5))
		{
			path_dirs = ft_split(envs->content + 5, ':');
			index = 0;
			while (path_dirs[index])
			{
				command_path = form_command_path(path_dirs[index++], cmd);
				if (access(command_path, F_OK) == 0)
				{
					free_path_dirs(path_dirs);
					return (command_path);
				}
				free(command_path);
			}
			free_path_dirs(path_dirs);
		}
		envs = envs->next;
	}
	return (NULL);
}

static char	*form_command_path(char *path, char *cmd)
{
	char	*path_with_slash;
	char	*full_path;

	full_path = ft_strjoin(path, "/");
	path_with_slash = ft_strjoin(full_path, cmd);
	free(full_path);
	return (path_with_slash);
}
