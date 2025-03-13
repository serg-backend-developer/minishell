#include "../../includes/minishell.h"

void	exec_external_cmd(t_minishell **minishell, char **args)
{
	char	*command_path;
	char	**envs_arr;

	command_path = NULL;
	envs_arr = NULL;
	if (access(args[0], F_OK) == 0)
		command_path = args[0];
	else
		command_path = find_command_path((*minishell)->envs, args[0]);
	if (command_path)
	{
		envs_arr = convert_env_list_to_array(minishell);
		execve(command_path, args, envs_arr);
		display_error(NULL, args[0], strerror(errno));
	}
	else
		display_error(NULL, args[0], "command not found");
	free_set(minishell);
	free(envs_arr);
	exit(127);
}
