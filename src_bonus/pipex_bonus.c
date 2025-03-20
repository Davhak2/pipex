#include "pipex_bonus.h"

void	exec_cmd(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	path = get_path(args[0], env);
	if (!path)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free(args);
		exit(127);
	}
	if (execve(path, args, env) == -1)
	{
		perror("pipex");
		ft_free(args);
		free(path);
		exit(127);
	}
}

void	make_process(t_pipex *pipex, char *cmd)
{
	if (pipe(pipex->fds) == -1)
		exit(EXIT_FAILURE);
	pipex->pid = fork();
	if (pipex->pid == -1)
		exit(EXIT_FAILURE);
	if (pipex->pid == 0)
	{
		close(pipex->fds[0]);
		dup2(pipex->fds[1], STDOUT_FILENO);
		close(pipex->fds[1]);
		exec_cmd(cmd, pipex->env);
	}
	else
	{
		close(pipex->fds[1]);
		dup2(pipex->fds[0], STDIN_FILENO);
		close(pipex->fds[0]);
	}
}

void	here_doc_put_in(t_pipex *pipex, char *limiter)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	close(pipex->fds[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if ((ft_strlen(line) == limiter_len + 1 && \
			!ft_strncmp(line, limiter, limiter_len) && \
			line[limiter_len] == '\n') || (ft_strlen(line) == limiter_len && \
			!ft_strncmp(line, limiter, limiter_len)))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipex->fds[1]);
		free(line);
	}
	close(pipex->fds[1]);
	exit(0);
}

void	here_doc(t_pipex *pipex, char *limiter)
{
	if (pipe(pipex->fds) == -1)
		exit(EXIT_FAILURE);
	pipex->pid = fork();
	if (pipex->pid == -1)
		exit(EXIT_FAILURE);
	if (pipex->pid == 0)
	{
		close(pipex->fds[0]);
		here_doc_put_in(pipex, limiter);
	}
	else
	{
		close(pipex->fds[1]);
		dup2(pipex->fds[0], STDIN_FILENO);
		close(pipex->fds[0]);
		waitpid(pipex->pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		i;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		norm_handle1("Not enough arguments\n", EXIT_FAILURE);
	pipex.env = env;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		i = 3;
		pipex.out_fd = ft_open(argv[argc - 1], 2);
		here_doc(&pipex, argv[2]);
	}
	else
	{
		i = 2;
		pipex.in_fd = ft_open(argv[1], 0);
		pipex.out_fd = ft_open(argv[argc - 1], 1);
		dup2(pipex.in_fd, STDIN_FILENO);
		close(pipex.in_fd);
	}
	while (i < argc - 2)
		make_process(&pipex, argv[i++]);
	dup2(pipex.out_fd, STDOUT_FILENO);
	close(pipex.out_fd);
	exec_cmd(argv[argc - 2], env);
}
