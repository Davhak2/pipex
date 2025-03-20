#include "pipex_bonus.h"

void	norm_handle1(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}
