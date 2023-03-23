/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:08:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/23 12:54:33 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threadtab(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
	{
		pthread_mutex_lock(&p->data_race);
		p->index = malloc(sizeof(int));
		*p->index = i;
		pthread_mutex_unlock(&p->data_race);
		if (pthread_create(&p->threadtab[i], NULL,
				&philosophers, (void *)p) != 0)
			return (1);
		usleep(120);
		pthread_mutex_lock(&p->data_race);
		free(p->index);
		pthread_mutex_unlock(&p->data_race);
		i++;
	}
	return (0);
}

void	*death_check(void *arg)
{
	t_philo		*p;
	t_boolean	check;
	int			i;
	size_t		time;

	p = (t_philo *)arg;
	time = gtime();
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&p->data_race);
		check = p->is_dead;
		pthread_mutex_unlock(&p->data_race);
		if (check == TRUE || p->meals_end == TRUE)
			break ;
		while (++i < p->nb_of_philo)
		{
			dead(p, i, time);
			end(p);
		}
	}
	return (NULL);
}

void	detach_pthreads(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->nb_of_philo)
		pthread_detach(p->threadtab[i++]);
	return ;
}

int	main(int ac, char **av)
{
	t_philo		p;
	pthread_t	checker;

	if (error_gestion(ac, av))
		return (1);
	p = initializer(av);
	pthread_mutex_init(&p.voix, NULL);
	pthread_mutex_init(&p.data_race, NULL);
	if (create_mutextab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	if (create_threadtab(&p))
		return (free(p.threadtab), free(p.fork), 1);
	pthread_create(&checker, NULL, &death_check, (void *)&p);
	wait_pthreads(&p);
	if (p.meals_end == TRUE)
		printf(GRN "SUCCESS !!!\n");
	destroy_mutextab(&p);
	pthread_detach(checker);
	pthread_mutex_destroy(&p.voix);
	pthread_mutex_destroy(&p.data_race);
	ft_free(&p);
	return (0);
}
