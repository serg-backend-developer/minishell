#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	execute_command(t_minishell **minishell, char **args, t_list *cmds);
static void	wait_for_processes(
				int process_count, int pipe_fds[2], int process_ids[1000]);
static void	close_pipes(
				int cmd_index, int current_pipe[2], int previous_pipe[2]);

int	execute_commands(t_minishell **minishell, t_list *cmds)
{
	t_pinfo	pi;

	pi.cmd_index = 0;
	pi.previous_pipe[0] = -1;
	pi.previous_pipe[1] = -1;
	pi.uniq = (cmds && !cmds->next && ((t_cmd *)cmds->content)->files == NULL);
	g_exit_status = 0;
	while (cmds)
	{
		if (pi.uniq && ((t_cmd *)(cmds->content))->args &&
			((t_cmd *)(cmds->content))->args[0] && handle_spec(minishell,
			((t_cmd *)(cmds->content))->args) == 0)
			break ;
		create_process(pi.current_pipe, pi.cmd_index, cmds, pi.process_ids);
		if (pi.process_ids[pi.cmd_index] == 0)
			setup_pipes_and_files(
				pi.cmd_index, pi.current_pipe, pi.previous_pipe, cmds);
		if (pi.process_ids[pi.cmd_index] == 0)
			execute_command(minishell, ((t_cmd *)(cmds->content))->args, cmds);
		close_pipes(pi.cmd_index++, pi.current_pipe, pi.previous_pipe);
		cmds = cmds->next;
	}
	wait_for_processes(pi.cmd_index, pi.previous_pipe, pi.process_ids);
	return (EXIT_SUCCESS);
}

static void	execute_command(t_minishell **minishell, char **args, t_list *cmds)
{
	args = ((t_cmd *)(cmds->content))->args;
	if (!args[0])
	{
		free_set(minishell);
		exit(EXIT_SUCCESS);
	}
	if (handle_builtin(minishell, args) != 0)
		exec_external_cmd(minishell, args);
	free_set(minishell);
	exit(EXIT_FAILURE);
}

static void	wait_for_processes(
	int process_count, int pipe_fds[2], int process_ids[1000])
{
	int	index;
	int	status;

	if (pipe_fds[READ_MODE] != -1)
		close(pipe_fds[READ_MODE]);
	if (pipe_fds[WRITE_MODE] != -1)
		close(pipe_fds[WRITE_MODE]);
	index = 0;
	while (index < process_count)
	{
		status = 0;
		waitpid(process_ids[index], &status, 0);
		g_exit_status = 0;
		g_exit_status = status % 255;
		index++;
	}
}

static void	close_pipes(
	int cmd_index, int current_pipe[2], int previous_pipe[2])
{
	if (cmd_index != 0)
	{
		close(previous_pipe[READ_MODE]);
		close(previous_pipe[WRITE_MODE]);
	}
	previous_pipe[READ_MODE] = current_pipe[READ_MODE];
	previous_pipe[WRITE_MODE] = current_pipe[WRITE_MODE];
}
