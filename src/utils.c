#include "pipex.h"

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*my_getenv(char *var, char **env)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**path;
	char	*path_part;
	char	**split_cmd;

	i = -1;
	path = ft_split(my_getenv("PATH", env), ':');
	split_cmd = ft_split(cmd, ' ');
	while (path[++i])
	{
		path_part = ft_strjoin(path[i], "/");
		exec = ft_strjoin(path_part, split_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free(split_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free(path);
	ft_free(split_cmd);
	return (cmd);
}

int	ft_open(char *file, int val)
{
	int	fd;

	if (val == 0)
		fd = open(file, O_RDONLY, 0777);
	if (val == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putstr_fd("Error, Can't open file\nGood Luck! ", 2);
		exit(1);
	}
	return (fd);
}
