/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_phases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:36:53 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/22 12:00:32 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************* */

#include "philosophers.h"

void	is_eating(t_philo *p, t_values *v)
{
	printf("\n%d INDEX\n\n", v->index);
	pthread_mutex_lock(&p->fork[v->prev]);
	pthread_mutex_lock(&p->voix);
	if (p->is_dead == FALSE)
		printf(MAG "%lu %d has taken a fork\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	pthread_mutex_lock(&p->fork[v->index]);
	pthread_mutex_lock(&p->voix);
	if (p->is_dead == FALSE)
		printf(MAG "%lu %d has taken a fork\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	p->can_eat[v->index] = TRUE;
	v->nb_of_meals++;
	if (v->nb_of_meals >= p->as_eaten && p->as_eaten != -1)
		p->is_full[v->index] = TRUE;
	pthread_mutex_lock(&p->voix);
	if (p->is_dead == FALSE)
		printf(BLU "%lu %d is eating\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	v->last_meal = gtime();
	ft_sleep(p->time_to_eat, p);
	pthread_mutex_unlock(&p->fork[v->prev]);
	pthread_mutex_unlock(&p->fork[v->index]);
	p->can_sleep[v->index] = TRUE;
}

void	is_sleeping(t_philo *p, t_values *v)
{
	printf("\n%d INDEX\n\n", v->index);
	pthread_mutex_lock(&p->voix);
	if (p->is_dead == FALSE)
		printf(CYN "%lu %d is sleeping\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	ft_sleep(p->time_to_sleep, p);
	p->can_eat[v->index] = FALSE;
	p->can_sleep[v->index] = FALSE;
	pthread_mutex_lock(&p->voix);
	if (p->is_dead == FALSE)
		printf(GRN "%lu %d is thinking\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
}

void	is_dead(t_philo *p, t_values *v)
{
	p->is_dead = TRUE;
	pthread_mutex_lock(&p->voix);
	printf(RED "%lu %d died\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
}

static t_values	initialize_values(t_philo	*p)
{
	t_values	v;

	v.nb_of_meals = 0;
	v.time = gtime();
	v.last_meal = gtime();
	v.index = *(int *)p->index;
	v.prev = v.index - 1;
	if (v.index == 0)
		v.prev = p->nb_of_philo - 1;
	return (v);
}

void	*philosophers(void	*arg)
{
	t_philo		*p;
	t_values	v;

	p = (t_philo *)arg;
	v = initialize_values(p);
	while (all_as_eaten(p) && p->is_dead == FALSE)
	{
		if (p->can_eat[v.index] == FALSE && p->is_dead == FALSE)
			is_eating(p, &v);
		else if (p->can_sleep[v.index] == TRUE && p->is_dead == FALSE)
			is_sleeping(p, &v);
		if (gtime() - v.last_meal > (size_t)p->time_to_die
			&& p->is_dead == FALSE)
			is_dead(p, &v);
	}
	return (NULL);
}
