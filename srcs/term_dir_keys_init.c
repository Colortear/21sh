/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_dir_keys_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:33:32 by wdebs             #+#    #+#             */
/*   Updated: 2017/08/11 16:12:49 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

static int	check_direction_keys(char *str, int check, t_shell *shell,
		t_history **hist)
{
	extern char	**environ;
	char		*left;
	char		*right;
	char		*down;
	char		*up;

	left = LEFT_INPUT;
	right = RIGHT_INPUT;
	down = DOWN_INPUT;
	up = UP_INPUT;
	if (environ && ft_strcmp(str, left) == 0 && (check = 1) &&
			shell->x > 0 && shell->x--)
		LEFT;
	else if (environ && ft_strcmp(str, right) == 0 && (check = 1) &&
			shell->x < (*hist)->x_max[shell->y] &&
			++shell->x)
		RIGHT;
	else if (environ && ft_strcmp(str, down) == 0 && (check = 1))
		history_move(shell, hist, HISTORY_DOWN);
	else if (environ && ft_strcmp(str, up) == 0 && (check = 1))
		history_move(shell, hist, HISTORY_UP);
	return (check);
}

static int	escape_chars(char c, int check, t_shell *shell, t_history **hist)
{
	char	buf[10];
	char	*seq;
	int		size;

	ft_bzero(buf, 10);
	size = read(0, buf, 10);
	buf[size] = 0;
	seq = ft_strnew(size + 1);
	seq[0] = c;
	ft_strcat(seq, buf);
	check = check_direction_keys(seq, check, shell, hist);
	if (check == 0)
		check = check_home_end(seq, check, shell, hist);
	free(seq);
	return (check);
}

int			terms_esc(char c, t_shell *shell, t_history **hist)
{
	int	check;

	check = 0;

	if (c == 127 && (check = 1))
		delete_char(shell, hist);
	if (check == 0 && c == 27)
		check = escape_chars(c, check, shell, hist);
	if (check == 0 && c == 4)
		check = -1;
	return (check);
}

int			set_termcap(void)
{
	struct termios	new;
	char			*term;

	getenv("TERM") == NULL ? ft_setenv("TERM", "xterm-256color") : 0;
	term = getenv("TERM");
	tgetent(NULL, term);
	if (tcgetattr(0, &g_old_term) < 0)
		return (-1);
	new = g_old_term;
	new.c_lflag &= ~(ECHO | ICANON);
	new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	new.c_cflag &= ~(CSIZE | PARENB);
	new.c_cflag |= CS8;
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, &new) < 0)
		return (-1);
	KEYS_ON;
	return (1);
}

int			end_termcap(void)
{
	if (tcsetattr(0, TCSAFLUSH, &g_old_term) < 0)
		return (-1);
	KEYS_LOCAL;
	return (0);
}
