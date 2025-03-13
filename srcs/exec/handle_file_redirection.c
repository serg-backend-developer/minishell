#include "../../includes/minishell.h"

void	handle_file_redirection(t_list *file_list)
{
	t_fd	*file;
	int		fd;

	while (file_list)
	{
		file = file_list->content;
		fd = 0;
		if (file->mode == MODE_WRITE_TRUNCATE)
			fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		else if (file->mode == MODE_WRITE_APPEND)
			fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file->mode == MODE_READ)
			fd = open(file->filename, O_RDONLY, 700);
		if (fd == -1)
		{
			display_error(NULL, file->filename, strerror(errno));
			exit(EXIT_FAILURE);
		}
		if (file->mode == MODE_READ)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		file_list = file_list->next;
	}
}
