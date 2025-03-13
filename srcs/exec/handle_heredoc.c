#include "../../includes/minishell.h"

void	handle_heredoc(char	*stop_word)
{
	char	*line;
	int		fd[2];

	if (!stop_word)
		return ;
	pipe(fd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, stop_word))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[WRITE_MODE]);
		ft_putstr_fd("\n", fd[WRITE_MODE]);
		free(line);
	}
	dup2(fd[READ_MODE], STDIN_FILENO);
	close(fd[READ_MODE]);
	close(fd[WRITE_MODE]);
}
