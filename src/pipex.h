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

char	*my_getenv(char *var, char **env);
char	*get_path(char *cmd, char **env);
int		ft_open(char *file, int val);
void	ft_free(char **tab);

#endif
