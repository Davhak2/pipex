#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int  fds[2];
	char **env;
	char **argv;
}   t_pipex;

typedef struct s_cmd
{
	char *path;
	char **args;
}   t_cmd;

typedef struct s_path
{
	int  i;
	char *exec;
	char **dirs;
	char *part;
	char *env_path;
}   t_path;


char	*my_getenv(char *var, char **env);
char	*get_path(char *cmd, char **env);
int		ft_open(char *file, int val);
void	ft_free(char **tab);
void	exec_cmd(t_cmd *cmd, char **env);
void	child_process(t_pipex *pipex);
void	parent_process(t_pipex *pipex);

#endif
