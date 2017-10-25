#include "libft.h"

void	clear_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (g_env_change && environ)
	{
		while (environ[i])
		{
			free(environ[i]);
			i++;
		}
		free(environ);
	}
}
