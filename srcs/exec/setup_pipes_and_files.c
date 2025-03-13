#include "../../includes/minishell.h"

void	setup_pipes_and_files(
	int cmd_index, int current_pipe[2], int previous_pipe[2], t_list *cmds)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmds->content;
	if (cmd_index != 0)
	{
		close(previous_pipe[WRITE_MODE]);
		dup2(previous_pipe[READ_MODE], STDIN_FILENO);
		close(previous_pipe[READ_MODE]);
	}
	if (cmd->heredoc)
		handle_heredoc(cmd->heredoc);
	if (cmds->next)
	{
		close(current_pipe[READ_MODE]);
		dup2(current_pipe[WRITE_MODE], STDOUT_FILENO);
		close(current_pipe[WRITE_MODE]);
	}
	handle_file_redirection(cmd->files);
}
