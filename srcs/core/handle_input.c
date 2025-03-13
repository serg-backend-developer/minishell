#include "../../includes/minishell.h"

void	process_input(t_minishell *minishell, char *input_line)
{
	if (lexer(&minishell, input_line) && validate_tokens(&minishell))
	{
		parse_commands(&minishell);
		execute_commands(&minishell, minishell->cmds);
	}
	free_minishell(&minishell);
	if (input_line)
		free(input_line);
}
