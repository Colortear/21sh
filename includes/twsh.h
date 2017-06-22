/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twsh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 21:55:00 by wdebs             #+#    #+#             */
/*   Updated: 2017/06/13 20:49:48 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWSH_H
# define TWSH_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <termcap.h>
# include <term.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <paths.h>
# include <sys/param.h>
# include <sys/select.h>

# include "libft.h"

# define CLEAR			tputs(tgetstr("cl", NULL), 1, ft_putchar)
# define STR_CURSOR_MV	tputs(tgetstr("ti", NULL), 1, ft_putchar)
# define END_CURSOR_MV	tputs(tgetstr("te", NULL), 1, ft_putchar)
# define LINE			tputs(tgetstr("cr", NULL), 1, ft_putchar)
# define HOME			tputs(tgetstr("ho", NULL), 1, ft_putchar)
# define DOWN			tputs(tgetstr("do", NULL), 1, ft_putchar)
# define UP				tputs(tgetstr("up", NULL), 1, ft_putchar)
# define RIGHT			tputs(tgetstr("nd", NULL), 1, ft_putchar)
# define LEFT			tputs(tgetstr("le", NULL), 1, ft_putchar)
# define DEL_MODE_ON	tputs(tgetstr("dm", NULL), 1, ft_putchar)
# define DEL_LINE		tputs(tgetstr("dl", NULL), 1, ft_putchar)
# define DEL_CHAR		tputs(tgetstr("dc", NULL), 1, ft_putchar)
# define DEL_MODE_OFF	tputs(tgetstr("ed", NULL), 1, ft_putchar)
# define INSERT_MODE_ON	tputs(tgetstr("im", NULL), 1, ft_putchar)
# define INSERT_CHAR	tputs(tgetstr("ic", NULL), 1, ft_putchar)
# define INSRT_MODE_OFF	tputs(tgetstr("ei", NULL), 1, ft_putchar)
# define KEYS_ON		tputs(tgetstr("ks", NULL), 1, ft_putchar)
# define KEYS_LOCAL		tputs(tgetstr("ke", NULL), 1, ft_putchar)
# define LEFT_INPUT		tgetstr("kl", NULL)
# define RIGHT_INPUT	tgetstr("kr", NULL)
# define UP_INPUT		tgetstr("ku", NULL)
# define DOWN_INPUT		tgetstr("kd", NULL)
# define HOME_KEY		tgetstr("kh", NULL)
# define END_KEY		tgetstr("@7", NULL)
# define HISTORY_UP		0
# define HISTORY_DOWN	1
# define PIPE			0
# define LEFT_REDIR		1
# define RIGHT_REDIR	2
# define LEFT_DOUBLE	3
# define RIGHT_DOUBLE	4
# define AMPERSAND		5
# define NORMAL			6
# define BAD_CMD		0
# define BIN			1
# define PATH			2
# define LOCAL			3
# define AMP_LEFT		1
# define AMP_RIGHT		2

int						g_reset;
struct termios			g_old_term;

typedef struct			s_cmd
{
	struct s_cmd		*head;
	struct s_cmd		*prev;
	struct s_cmd		*next;
	char				**aggs;
	char				**in;
	char				**out;
	char				**heredoc;
	char				**append;
	char				*cmd;
	char				**args;
	int					out_ord;
	int					in_ord;
	int					std_in;
	int					std_out;
	int					std_err;
	int					pipe_in;
	int					fd[2];
	char				*hds;
}						t_cmd;

typedef struct			s_history
{
	struct s_history	*prev;
	struct s_history	*next;
	int					x_max[1000];
	int					y_max;
	int					chars;
	int					d;
	char				*cmd;
}						t_history;

typedef struct			s_shell
{
	t_history			*hist_head;
	struct termios		old;
	int					x;
	int					y;
	char				**path;
}						t_shell;

int						command(t_history *hist);
int						set_termcap(void);
int						end_termcap(void);
int						terms_esc(char c, t_shell *shell,
		t_history **hist);
void					exit_shell(t_history *hist,
		t_shell *shell, int err_code);
t_history				*setup(t_shell *shell,
		t_history *hist);
void					insert_char(char *c, t_shell *shell,
		t_history *hist);
void					delete_char(t_shell *shell, t_history **hist);
void					cleanup(t_shell *shell, t_history *hist);
t_history				*init_hist(t_shell *shell, t_history *hist);
t_history				*read_and_parse(t_shell *shell, t_history *hist);
void					disp_prompt(void);
t_shell					*initialize_structs(void);
char					**freetwod(char **str);
void					history_move(t_shell *shell,
		t_history **hist, int dir);
t_history				*add_cmd(t_shell *shell, t_history *copy);
void					delete_return(t_history **hist);
void					puterm(char *str);
t_history				*copy_history(t_history *hist);
void					destroy_copy(t_history *copy);
void					fill_x(t_history **head, t_history *hist);
int						check_home_end(char *str, int check,
		t_shell *shell, t_history **hist);
void					set_node(t_cmd **cmd, char *tmp, int type);
char					**twsplit(char *str);
char					**split_quotes(char *str, char **new, int *i);
char					**extract_cmd(char *str, char **new, int *i);
int						parse_pipes(char *str);
t_cmd					*insert_cmd_list(char *str, int type);
void					destroy_cmd_list(t_cmd *cmd);
char					*copy_seg(char *str, int start, int end);
int						check_spaces(char *str);
t_cmd					*link_cmds(t_cmd *cmds);
void					run_execs(t_cmd *cmds);
void					free_cmds(t_cmd *cmds);
int						exec(t_cmd *cmds);
t_cmd					*next_cmd(t_cmd *cmds);
int						run_builtins(t_cmd *cmds);
void					run_env(void);
void					run_echo(char **args);
void					run_cd(char **path);
t_cmd					*link_cmds(t_cmd *cmds);
char					check_expansions(char exp);
char					heredoc_manage(char *key, int len);
int						heredoc(t_cmd *cmds, char *key);
void					ampersand(t_cmd *cmds);
int						ampersand_type(char **amp);
int						isnum(char *tmp, int size);
void					amp(char **tmp, int type);
void					fd_dups(char **split);
void					check_aggs(char **aggs);
void					lay_pipe(t_cmd *cmds);
void					save_fd(int io);

#endif
