#include "pipex_bonus.h"

void	exec_cmd(t_cmd *cmd, char **env)
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

void	make_process(t_pipex *pipex, t_cmd *cmd)
{
	if (pipe(pipex->fds) == -1)
		exit(EXIT_FAILURE);
	pipex->pid = fork();
	if (pipex->pid == -1)
		exit(EXIT_FAILURE);
	if (!pipex->pid)
	{
		close(pipex->fds[0]);
		dup2(pipex->fds[1], STDOUT_FILENO);
		exec_cmd(cmd->args, pipex->env);
	}
	else
	{
		close(pipex->fds[1]);
		dup2(pipex->fds[0], STDIN_FILENO);
	}
}


int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("Not enough arguments!\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		
	}
}
