/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:08:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/22 12:45:43 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	gtime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	ft_sleep(int timeobj, t_philo *p)
{
	size_t	time;

	time = gtime();
	while (gtime() - time < (size_t)timeobj && p->is_dead == FALSE)
		usleep(60);
}

int	all_as_eaten(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->as_eaten)
		if (p->is_full[i++] == FALSE)
			return (1);
	if (p->as_eaten == -1)
		return (1);
	return (0);
}

int	create_threadtab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		p->index = malloc(sizeof(int));
		*p->index = i;
		if (i % 2)
			usleep(100);
		if (pthread_create(&p->threadtab[i], NULL, &philosophers, (void *)p) != 0)
			return (1);
		usleep(12);
		free(p->index);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	p;

	if (error_gestion(ac, av))
		return (1);
	p = initializer(av);
	pthread_mutex_init(&p.voix, NULL);
	if (create_mutextab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	if (create_threadtab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	wait_pthreads(&p);
	destroy_mutextab(&p);
	pthread_mutex_destroy(&p.voix);
	return (0);
}
