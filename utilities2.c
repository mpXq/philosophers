/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 10:54:13 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/23 11:26:33 by pfaria-d         ###   ########.fr       */
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

int	all_eat(t_philo *p)
{
	int			i;
	t_boolean	is_full;

	i = 0;
	while (i < p->as_eaten)
	{
		pthread_mutex_lock(&p->data_race);
		is_full = p->is_full[i];
		pthread_mutex_unlock(&p->data_race);
		if (is_full == FALSE)
			return (1);
		i++;
	}
	if (p->as_eaten == -1)
		return (1);
	return (0);
}

void	ft_free(t_philo	*p)
{
	free(p->threadtab);
	p->threadtab = NULL;
	free(p->fork);
	p->fork = NULL;
	free(p->can_eat);
	p->can_eat = NULL;
	free(p->can_sleep);
	p->can_sleep = NULL;
	free(p->is_full);
	free(p->last_meal);
}
