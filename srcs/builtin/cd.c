#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	handle_cd_special_cases(t_minishell **minishell, char **args);
static void	update_directory_envs(
				t_minishell **minishell,
				char *prev_dir, char *curr_dir);

int	change_directory(t_minishell **minishell, char **args)
{
	char	*prev_dir;
	char	*curr_dir;

	if (!args[1] || ft_strcmp(args[1], "~") == 0 || ft_strcmp(args[1],
			"--") == 0 || ft_strcmp(args[1], "-") == 0)
		handle_cd_special_cases(minishell, args);
	else if (chdir(args[1]) == -1)
	{
		display_error("cd", args[1], "No such file or directory");
		g_exit_status = 1;
	}
	prev_dir = retrieve_env_value((*minishell)->envs, "PWD");
	curr_dir = getcwd(NULL, 0);
	update_directory_envs(minishell, prev_dir, curr_dir);
	free(prev_dir);
	free(curr_dir);
	return (EXIT_SUCCESS);
}

static int	handle_cd_special_cases(t_minishell **minishell, char **args)
{
	char	*curr_dir;
	char	*prev_dir;

	if (args[1] && ft_strcmp(args[1], "-") == 0)
	{
		prev_dir = retrieve_env_value((*minishell)->envs, "OLDPWD");
		if (!prev_dir)
		{
			printf("cd: OLDPWD not set\n");
			free(prev_dir);
			return (EXIT_FAILURE);
		}
		else
		{
			chdir(prev_dir);
			free(prev_dir);
		}
	}
	else
	{
		curr_dir = retrieve_env_value((*minishell)->envs, "HOME");
		chdir(curr_dir);
		free(curr_dir);
	}
	return (EXIT_SUCCESS);
}

static void	update_directory_envs(
	t_minishell **minishell, char *prev_dir, char *curr_dir)
{
	char	*oldpwd_env;
	char	*pwd_env;
	char	*env_value;

	oldpwd_env = ft_strjoin("OLDPWD=", prev_dir);
	pwd_env = ft_strjoin("PWD=", curr_dir);
	env_value = retrieve_env_value((*minishell)->envs, "OLDPWD");
	if (env_value)
		update_env_value(minishell, oldpwd_env);
	else
		ft_lstadd_back(&(*minishell)->envs, ft_lstnew(oldpwd_env));
	free(env_value);
	env_value = retrieve_env_value((*minishell)->envs, "PWD");
	if (env_value)
		update_env_value(minishell, pwd_env);
	else
		ft_lstadd_back(&(*minishell)->envs, ft_lstnew(pwd_env));
	free(env_value);
}
