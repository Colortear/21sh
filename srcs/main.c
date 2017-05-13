/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebs <wdebs@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:23:51 by wdebs             #+#    #+#             */
/*   Updated: 2017/05/12 22:25:22 by wdebs            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twsh.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_reset = 1;
		write(0, "\r", 1);
	}
	else if (signal == SIGHUP || signal == SIGXCPU || signal == SIGXFSZ)
		exit(1);
}

static void	signals(void)
{
	struct sigaction	s;

	s.sa_handler = &signal_handler;
	s.sa_flags = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGURG, SIG_IGN);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGIO, SIG_IGN);
	sigaction(SIGINT, &s, 0);
	sigaction(SIGHUP, &s, 0);
	sigaction(SIGXCPU, &s, 0);
	sigaction(SIGXFSZ, &s, 0);
}

void		exit_shell(t_history *hist, t_shell *shell, int err_code)
{
	free(hist);
	free(shell);
	exit(err_code);
}

int			main(void)
{
	t_shell		*shell;
	t_history	*hist;

	shell = (t_shell *)malloc(sizeof(t_shell));
	hist = (t_history *)malloc(sizeof(t_history));
	hist->prev = NULL;
	shell->hist_head = NULL;
	shell->path = NULL;
	if (set_termcap(shell) < 0)
		exit_shell(hist, shell, 1);
	while (1)
	{
		g_reset = 0;
		signals();
		hist = setup(shell, hist);
		hist = read_and_parse(shell, hist);
		ft_putstr("\n\r");
		if (!g_reset && ((hist->cmd && command(hist) == 1) ||
				hist->d == 1))
			break ;
	}
	cleanup(shell, hist);
	return (0);
}
