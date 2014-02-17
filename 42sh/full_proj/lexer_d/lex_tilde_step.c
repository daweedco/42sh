
#include <stdlib.h>
#include "libft.h"
#include "lexer.h"

char			*sh_get_env(char *var, char **env)
{
	char			**tmp;
	char			*value;
	int				len;

	value = NULL;
	tmp = env;
	while (*tmp)
	{
		if ((ft_strnequ(*tmp, var, (len = ft_strlen(var))) == 1))
		{
			if ((*tmp)[len + 1] == '=')
				len++;
			value = ft_strdup((*tmp) + len);
			return (value);
		}
		tmp++;
	}
	return (value);
}

void		replace_tidle(char **cmd, char **env, int tilde)
{
	char	*home;
	char	*new_cmd;
	int		j;
	int		t;
	int		i;

	j = 0;
	t = 0;
	i = 0;
	home = sh_getenv("HOME", env);
	new_cmd = ft_strnew(ft_strlen(*cmd) + ft_strlen(home) - 1);
	while ((*cmd)[j])
	{
		if (j != tilde)
			new_cmd[t++] = (*cmd)[j];
		else
		{
			while (home[i])
				new_cmd[t++] = home[i++]; //voir si ca marche
		}
		j++;
	}
	free(*cmd);
	*cmd = new_cmd;
}

void		stp_tilde(char **cmd, char **env)
{
	int		i;

	i = 0;
	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '~')
			replace_tidle(cmd, env, i);
		i++;
	}
}
