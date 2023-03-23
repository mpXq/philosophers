/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_phases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:47:19 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/23 14:01:36 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_boolean	eat_part1(t_philo *p, t_values *v, t_boolean check)
{
	pthread_mutex_lock(&p->fork[v->prev]);
	pthread_mutex_lock(&p->voix);
	pthread_mutex_lock(&p->data_race);
	check = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	usleep(20);
	if (p->is_dead == FALSE && check == FALSE)
		printf(MAG "%lu %d has taken a fork\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	pthread_mutex_lock(&p->fork[v->index]);
	pthread_mutex_lock(&p->voix);
	pthread_mutex_lock(&p->data_race);
	check = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	usleep(15);
	if (p->is_dead == FALSE && check == FALSE)
		printf(MAG "%lu %d has taken a fork\n", gtime() - v->time, v->index + 1);
	p->can_eat[v->index] = TRUE;
	pthread_mutex_unlock(&p->voix);
	pthread_mutex_lock(&p->voix);
	pthread_mutex_lock(&p->data_race);
	check = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	return (check);
}

void	is_eating(t_philo *p, t_values *v)
{
	t_boolean	check;

	check = 0;
	check = eat_part1(p, v, check);
	usleep(15);
	if (p->is_dead == FALSE && check == FALSE)
		printf(BLU "%lu %d is eating\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	v->nb_of_meals++;
	if (v->nb_of_meals >= p->as_eaten && p->as_eaten != -1)
	{
		pthread_mutex_lock(&p->data_race);
		p->is_full[v->index] = TRUE;
		pthread_mutex_unlock(&p->data_race);
	}
	ft_sleep(p->time_to_eat, p);
	pthread_mutex_lock(&p->data_race);
	p->last_meal[v->index] = gtime();
	p->can_sleep[v->index] = TRUE;
	pthread_mutex_unlock(&p->data_race);
	pthread_mutex_unlock(&p->fork[v->prev]);
	pthread_mutex_unlock(&p->fork[v->index]);
}

void	is_sleeping(t_philo *p, t_values *v)
{
	t_boolean	check;

	pthread_mutex_lock(&p->voix);
	pthread_mutex_lock(&p->data_race);
	check = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	usleep(40);
	if (p->is_dead == FALSE && check == FALSE)
		printf(CYN "%lu %d is sleeping\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
	pthread_mutex_lock(&p->data_race);
	p->can_eat[v->index] = FALSE;
	p->can_sleep[v->index] = FALSE;
	pthread_mutex_unlock(&p->data_race);
	ft_sleep(p->time_to_sleep, p);
	pthread_mutex_lock(&p->voix);
	pthread_mutex_lock(&p->data_race);
	check = p->meals_end;
	pthread_mutex_unlock(&p->data_race);
	if (p->is_dead == FALSE && check == FALSE)
		printf(GRN "%lu %d is thinking\n", gtime() - v->time, v->index + 1);
	pthread_mutex_unlock(&p->voix);
}

static t_values	initialize_values(t_philo	*p)
{
	t_values	v;

	v.nb_of_meals = 0;
	v.time = gtime();
	pthread_mutex_lock(&p->data_race);
	v.index = *(int *)p->index;
	pthread_mutex_unlock(&p->data_race);
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
	pthread_mutex_lock(&p->data_race);
	p->last_meal[v.index] = gtime();
	pthread_mutex_unlock(&p->data_race);
	while (p->meals_end == FALSE && p->is_dead == FALSE)
	{
		if (p->can_eat[v.index] == FALSE && p->is_dead == FALSE)
			is_eating(p, &v);
		else if (p->can_sleep[v.index] == TRUE && p->is_dead == FALSE)
			is_sleeping(p, &v);
	}
	return (NULL);
}
