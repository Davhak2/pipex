#include "pipex.h"

void exec_cmd(t_cmd *cmd, char **env)
{
	if (!cmd->path)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free(cmd->args);
		exit(127);
	}
	execve(cmd->path, cmd->args, env);
	perror("pipex");
	ft_free(cmd->args);
	exit(127);
}

void child_process(t_pipex *pipex)
{
	int fd = ft_open(pipex->argv[1], 0);
	t_cmd cmd;

	dup2(fd, 0);
	dup2(pipex->fds[1], 1);
	close(pipex->fds[0]);
	cmd.args = ft_split(pipex->argv[2], ' ');
	cmd.path = get_path(cmd.args[0], pipex->env);
	exec_cmd(&cmd, pipex->env);
}

void parent_process(t_pipex *pipex)
{
	int fd = ft_open(pipex->argv[4], 1);
	t_cmd cmd;

	dup2(fd, 1);
	dup2(pipex->fds[0], 0);
	close(pipex->fds[1]);

	cmd.args = ft_split(pipex->argv[3], ' ');
	cmd.path = get_path(cmd.args[0], pipex->env);
	exec_cmd(&cmd, pipex->env);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	pid_t pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}

	pipex.env = envp;
	pipex.argv = argv;

	if (pipe(pipex.fds) == -1)
	{
		ft_putstr_fd("Error: Pipe failed\n", 2);
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (!pid)
		child_process(&pipex);
	parent_process(&pipex);

	ft_putstr_fd("Your pipes worked successfully\n", 1);
	exit(EXIT_SUCCESS);
}
