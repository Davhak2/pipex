#include "pipex.h"

static void	exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		ft_free(split_cmd);
		exit(127);
	}
	ft_free(split_cmd);
}

static void	child(int *fds, char **argv, char **env)
{
	int	fd;

	fd = ft_open(argv[1], 0);
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[0]);
	exec(argv[2], env);
}

static void	parent(int *fds, char **argv, char **env)
{
	int	fd;

	fd = ft_open(argv[4], 1);
	dup2(fd, 1);
	dup2(fds[0], 0);
	close(fds[1]);
	exec(argv[3], env);
}


int main(int argc, char **argv, char **envp)
{
	int		fds[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(fds) == -1)
	{
		ft_putstr_fd("Error: Pipe failed\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (!pid)
		child(fds, argv, envp);
	parent(fds, argv, envp);
	ft_putstr_fd("Your pipes worked successfully", 1);
	exit(EXIT_SUCCESS);
}
