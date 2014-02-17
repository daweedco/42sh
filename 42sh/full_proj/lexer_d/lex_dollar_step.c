#include "libft.h"
#include "lexer.h"


void			make_replace(char *value, char **cmd, int dollar)
{
	int			i;
	int			j;
	char		*cmd_new;

	i = 0;
	j = 0;
	cmd_new = ft_strnew(ft_strlen(value) - 1 + ft_strlen(*cmd));
	while ((*cmd)[i])
	{
		if (i != dollar)
			cmd_new[j++] = (*cmd)[i];
		else
		{
			while (*value)
			{
				cmd_new[j++] = *value;
				value++;
			}
		}
		i++;
	}
	free(*cmd);
	*cmd = cmd_new;
}

void			replace_dollar(char **cmd, char **env, int dollar)
{
	char		*tmp;
	int			i;

	tmp = env;
	while (*tmp)
	{
		i = 0;
		while ((*cmd)[i] == (*tmp)[i])
		{
			i++;
			if ((*tmp)[i] == '=')
			{
				make_replace(*tmp + (i + 1), cmd, dollar);
				return ;
			}
		}
		tmp++;
	}
}

void			stp_dollar(char **cmd, char **env)
{
	int		i;

	while ((*cmd)[i])
	{
		if ((*cmd)[i] == '$' && (i == 0 || (*cmd)[i - 1] != '/'))
			replace_dollar(cmd, env, i);
		i++;
	}
}
