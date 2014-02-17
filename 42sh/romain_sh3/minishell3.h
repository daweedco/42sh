/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell3.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 18:59:11 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 20:43:58 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE 1

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "./libft/includes/libft.h"

# define RIGHT	"\x1b\x5b\x43"
# define LEFT	"\x1b\x5b\x44"
# define UP		"\x1b\x5b\x41"
# define DOWN	"\x1b\x5b\x42"
# define RETURN	"\x0a\x00\x00"
# define HOME	"\x1b\x5b\x48"
# define END	"\x1b\x5b\x46"
# define OPTR	"\x1b\x5b\x31\x3b\x39\x43"
# define OPTL	"\x1b\x5b\x31\x3b\x39\x44"
# define OPTU	"\x1b\x5b\x31\x3b\x39\x41"
# define OPTD	"\x1b\x5b\x31\x3b\x39\x42"
# define DEL 	"\x7f"
# define DEL2	"\x1b\x5b\x33\x7e"
# define CTRLD	"\x04"
# define OPTC	"\x02"
# define OPTX	"\x18"
# define OPTV	"\x10"

extern char 	**environ;
int				g_stop;

typedef struct		s_hist
{
	char			*cmd;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_pipe
{
	char			*path1;
	char			**cmd1;
	char			*path2;
	char			**cmd2;
}					t_pipe;

typedef struct		s_cmd
{
	t_hist			*list;
	char			*line;
	char			*save;
	int				exec;
	int				fd;
	pid_t			id;
	int				i;
	int				c;
	int				count;
	int				fd_out;
	char			*path;
	char			**cmd;
	char			*arg;
	char			**cmd_arg;
	char			**env;
	char			*pwd;
	char			*old_pwd;
}					t_cmd;

char			**init_env(void);
char			**add_var(char **env, char *var);
t_cmd			*execute_cmd(t_cmd *cmd);
void			execute_env(char **env);
int				execute_mycmd(t_cmd **cmd);
char			**execute_setenv(char **env, char **cmd);
char			**modify_var(char **env, char **cmd);
char			*which_path(char *cmd);
void			execute_error(char *cmd);
char			**delete_var(char **env, char **cmd);
char			**execute_unsetenv(char **env, char **cmd);
void			init_cmd(t_cmd *cmd);
t_cmd			*init_pipe(t_cmd *cmd);
int				open_file(char *dir, char *dest);
char			*ft_clean(char *cmd, int i, int j);
int				ft_tablen(char **tab);
t_cmd			*ft_select(t_cmd *cmd);
void			restore_env(void);
struct termios	init_term(void);
void			catch_signal(void);
char			**ft_strsplit_space(char const *str);
int				tputchar(int c);
t_hist			*add_list(t_cmd *cmd);
t_cmd			*add_char(t_cmd *cmd, char c);
t_cmd			*del_char(t_cmd *cmd);
t_cmd			*move_side(char *key, t_cmd *cmd);
t_cmd			*move_word(t_cmd *cmd, char *key, int i);
t_cmd			*prev_cmd(char *key, t_cmd *cmd);
t_cmd			*my_cd(t_cmd *cmd, int i);

#endif
