/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davihako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:14:31 by davihako          #+#    #+#             */
/*   Updated: 2025/03/20 21:14:59 by davihako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX__BONUS_H

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
	int		fds[2];
	int		in_fd;
	int		out_fd;
	pid_t	pid;
	char	**argv;
	char	**env;
}	t_pipex;

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_path
{
	int		i;
	char	*exec;
	char	**dirs;
	char	*part;
	char	*env_path;
}	t_path;

int		ft_open(char *file, int val);
char	*my_getenv(char *var, char **env);
char	*get_path(char *cmd, char **env);
void	ft_free(char **tab);
void	exec_cmd(char *cmd, char **env);
void	child_process(t_pipex *pipex);
void	parent_process(t_pipex *pipex);
void	norm_handle1(char *msg, int exit_code);

#endif
