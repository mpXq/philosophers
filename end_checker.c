/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:52:53 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/23 12:55:16 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dead(t_philo *p, int i, size_t time)
{
	size_t	last_meal;

	pthread_mutex_lock(&p->data_race);
	last_meal = p->last_meal[i];
	pthread_mutex_unlock(&p->data_race);
	if (gtime() - last_meal >= (size_t)p->time_to_die
		&& p->is_dead == FALSE)
	{
		pthread_mutex_lock(&p->data_race);
		p->is_dead = TRUE;
		pthread_mutex_unlock(&p->data_race);
		pthread_mutex_lock(&p->voix);
		printf(RED "%lu %d died\n", gtime() - time, i + 1);
		pthread_mutex_unlock(&p->voix);
		return (1);
	}
	return (0);
}

int	end(t_philo	*p)
{
	if (!all_eat(p))
	{
		pthread_mutex_lock(&p->data_race);
		p->meals_end = TRUE;
		pthread_mutex_unlock(&p->data_race);
	}
	return (0);
}
