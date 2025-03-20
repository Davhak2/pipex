/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:15:41 by davihako          #+#    #+#             */
/*   Updated: 2025/03/20 21:15:44 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **tab)
{
	int		i;

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
	t_path	path;

	path.i = -1;
	path.env_path = my_getenv("PATH", env);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path.dirs = ft_split(path.env_path, ':');
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

int	ft_open(char *file, int flag)
{
	int	fd;

	if (flag == 0)
		fd = open(file, O_RDONLY);
	else if (flag == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);
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
