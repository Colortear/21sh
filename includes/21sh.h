/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:49:13 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/15 23:19:35 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TWO_ONE_SH_H
# define TWO_ONE_SH_H

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
# include <paths.h>
# include <sys/param.h>
# include <sys/select.h>

# include "libft.h"

# define CLEAR			tputs(tgetstr("cl", NULL), 1, ft_putchar)
# define STR_CURSOR_MV	tputs(tgetstr("ti", NULL), 1, ft_putchar)
# define END_CURSOR_MV	tputs(tgetstr("te", NULL), 1, ft_putchar)
# define LINE			tputs(tgetstr("cr", NULL), 1, ft_putchar)
# define SCREEN			tputs(tgetstr("ho", NULL), 1, ft_putchar)
# define DOWN			tputs(tgetstr("do", NULL), 1, ft_putchar)
# define UP				tputs(tgetstr("up", NULL), 1, ft_putchar)
# define RIGHT			tputs(tgetstr("nd", NULL), 1, ft_putchar)
# define LEFT			tputs(tgetstr("le", NULL), 1, ft_putchar)
# define DEL_MODE_ON	tputs(tgetstr("dm", NULL), 1, ft_putchar)
# define DEL_CHAR		tputs(tgetstr("dc", NULL), 1, ft_putchar)
# define DEL_MODE_OFF	tputs(tgetstr("ed", NULL), 1, ft_putchar)
# define INSERT_MODE_ON	tputs(tgetstr("im", NULL), 1, ft_putchar)
# define INSERT_CHAR	tputs(tgetstr("ic", NULL), 1, ft_putchar)
# define INSRT_MODE_OFF	tputs(tgetstr("ei", NULL), 1, ft_putchar)

typedef struct			s_history
{
	char				*hist_cmd;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct		s_shell
{
	struct termios	old;
	char			*cmd;
	char			**path;
	t_history		*history;
}					t_shell;

int		command(t_shell *shell);
int		set_termcap(t_shell *shell);
int		end_termcap(t_shell *shell);
int		terms_esc(char c, t_shell *shell);
void	exit_shell(t_shell *shell, int err_code);
void	setup(t_shell *shell);
void	insert_char(char *c);
void	delete_char(t_shell *shell);
void	cleanup(t_shell *shell);
void	add_to_history(t_shell *shell);
void	read_and_parse(t_shell *shell);
void	disp_prompt(void);
t_shell	*initialize_structs(void);

#endif
