#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "../libft/libft.h"

# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <unistd.h>

# define RESET "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"

# define MINISHELL "\033[1;93mminishell\033[0m$ "

# define EXIT_ERROR 2

# define READ_MODE 0
# define WRITE_MODE 1

typedef enum e_token_category
{
	TOKEN_SPACE = 1,
	TOKEN_DOUBLE_QUOTE = 2,
	TOKEN_PIPE = 3,
	TOKEN_ARGUMENT = 4,
	TOKEN_REDIR_OUT = 5,
	TOKEN_REDIR_IN = 6,
	TOKEN_APPEND = 7,
	TOKEN_HEREDOC = 8
}	t_token_category;

typedef enum e_fd_mode
{
	MODE_WRITE_TRUNCATE = 5,
	MODE_WRITE_APPEND = 6,
	MODE_READ = 7
}	t_fd_mode;

typedef struct s_pinfo
{
	int		current_pipe[2];
	int		previous_pipe[2];
	int		cmd_index;
	int		uniq;
	int		process_ids[1000];
}			t_pinfo;

typedef struct s_fd
{
	char	*filename;
	int		mode;
}	t_fd;

typedef struct s_cmd
{
	char	**args;
	t_list	*files;
	char	*heredoc;
}	t_cmd;

typedef struct s_token
{
	char	*value;
	int		category;
	int		length;
}	t_token;

typedef struct s_minishell
{
	t_list	*envs;
	t_list	*tokens;
	t_list	*cmds;
}	t_minishell;

int			change_directory(t_minishell **minishell, char **args);
int			create_env_list(t_minishell **minishell, char **envp);
int			delete_spaces(t_minishell **minishell);
int			execute_commands(t_minishell **minishell, t_list *cmds);
int			handle_export_cmd(t_minishell **minishell, char **args);
int			handle_builtin(t_minishell **minishell, char **args);
int			handle_spec(t_minishell **minishell, char **args);
int			handle_exit(t_minishell **minishell, char **args);
int			handle_echo(t_minishell **minishell, char **args);
int			handle_redirection(char *input, int *curr_index, t_token *token);
int			handle_pwd(t_minishell **minishell);
int			handle_dollar_sign(
				t_minishell **minishell, char *input,
				int *curr_index, t_token *parsed_token);
int			handle_single_quote(char *input, int *index, t_token *token);
int			handle_double_quote(char *input, int *index, t_token *token);
int			handle_pipe(int *curr_index, t_token *parsed_token);
int			handle_space(int *curr_index, t_token *parsed_token);
int			lexer(t_minishell **minishell, char *input);
int			open_and_process_quotes(t_minishell **minishell);
int			print_env(t_minishell **minishell);
int			print_syntax_error(void);
int			unset_env_variable(t_minishell **minishell, char **args);
int			validate_tokens(t_minishell **minishell);

char		**convert_env_list_to_array(t_minishell **minishell);
char		*find_command_path(t_list *envs, char *cmd);
char		*retrieve_env_name(char *env_entry);
char		*retrieve_env_value(t_list *env_list, char *key);

void		create_process(
				int current_pipe[2], int cmd_index,
				t_list *cmds, int process_ids[1000]);
void		display_error(char *cmd, char *arg, char *error_message);
void		exec_external_cmd(t_minishell **minishell, char **args);
void		handle_export_no_args(t_minishell **minishell);
void		handle_heredoc(char	*stop_word);
void		handle_file_redirection(t_list *file_list);
void		handle_signal(int signal);
void		free_env_list(t_minishell *minishell);
void		free_minishell(t_minishell **minishell);
void		free_path_dirs(char **path_dirs);
void		free_set(t_minishell **minishell);
void		minishell_loop(t_minishell *minishell);
void		parse_commands(t_minishell **minishell);
void		process_input(t_minishell *minishell, char *input_line);
void		remove_list_nodes(t_list **list, void *value_to_remove,
				int (*cmp)(const char *, const void *));
void		set_signals(void);
void		setup_pipes_and_files(int cmd_index, int current_pipe[2],
				int previous_pipe[2], t_list *cmds);
void		update_env_value(t_minishell **minishell, char *arg);
void		welcome(void);

t_minishell	*init_minishell(char **envp);

#endif
