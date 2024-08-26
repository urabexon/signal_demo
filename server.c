/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:53:43 by hurabe            #+#    #+#             */
/*   Updated: 2024/08/26 20:27:31 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

volatile sig_atomic_t	g_char = 0;

void	signal_handler(int signum)
{
	static int	i;
	char		c;

	g_char = g_char << 1;
	if (signum == SIGUSR1)
		g_char |= 1;
	else if (signum == SIGUSR2)
		;
	i++;
	c = 0xff & g_char;
	if (i == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		i = 0;
	}
}

int	main(void)
{
	printf("not good minitalk server pid=%d\n", getpid()); // pidが表示される
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
}
