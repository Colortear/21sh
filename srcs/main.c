/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:23:51 by wdebs             #+#    #+#             */
/*   Updated: 2017/03/16 00:00:22 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int			set_termcap(t_shell *shell)
{
	struct termios	new;
	char			*term;

	term = getenv("TERM");
	tgetent(NULL, term);
	if (tcgetattr(0, &shell->old) < 0)
		return (-1);
	new = shell->old;
	new.c_lflag &= ~(ECHO | ICANON);
	new.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	new.c_cflag &= ~(CSIZE | PARENB);
	new.c_cflag |= CS8;
	new.c_oflag &= ~(OPOST);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSAFLUSH, &new) < 0)
		return (-1);
	return (1);
}

int			end_termcap(t_shell *shell)
{
	if (tcsetattr(0, TCSAFLUSH, &shell->old) < 0)
		return (-1);
	return (0);
}

int			terms_esc(char c, t_shell *shell)
{
	int		check;

	check = 0;
	if ((c &= 255) == 0177 && (check = 1))
		delete_char(shell);
	return (check);
}

void		exit_shell(t_shell *shell, int err_code)
{
	free(shell);
	exit(err_code);
}

int			main(void)
{
	t_shell	*shell;

	shell = initialize_structs();
	if (set_termcap(shell) < 0)
		exit_shell(shell, 1);
	while (1)
	{
		setup(shell);
		read_and_parse(shell);
		if (shell->cmd && command(shell) == 1)
			break ;
		shell->cmd ? free(shell->cmd) : 0;
		ft_putstr("\n\r");
	}
	cleanup(shell);
	return (0);
}
