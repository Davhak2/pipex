#include "pipex.h"

void    ft_free(char **tab)
{
	int i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char    *my_getenv(char *var, char **env)
{
	int i = 0;
	size_t len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char    *get_path(char *cmd, char **env)
{
	t_path path;

	path.i = -1;
	path.env_path = my_getenv("PATH", env);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	if (!path.env_path)
		return (NULL);
	path.dirs = ft_split(path.env_path, ':');
	if (!path.dirs)
		return (NULL);
	while (path.dirs[++path.i])
	{
		path.part = ft_strjoin(path.dirs[path.i], "/");
		path.exec = ft_strjoin(path.part, cmd);
		free(path.part);
		if (access(path.exec, F_OK | X_OK) == 0)
		{
			ft_free(path.dirs);
			return (path.exec);
		}
		free(path.exec);
	}
	ft_free(path.dirs);
	return (NULL);
}

int ft_open(char *file, int flag)
{
	int fd;

	if (flag == 0)
		fd = open(file, O_RDONLY);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		exit(EXIT_FAILURE);

	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
