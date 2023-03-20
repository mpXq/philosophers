/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfaria-d <pfaria-d@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:08:27 by pfaria-d          #+#    #+#             */
/*   Updated: 2023/03/19 17:27:29 by pfaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t	*create_philolst(pthread_t *philolst, int nb_of_philo)
{
	int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		philolst[i] = pthread_create();
		i++;
	}
	return (philolst);
}

int main(int ac, char **av)
{
	pthread_t *philolst;
	if (error_gestion(ac, av))
		return (1);
	philolst = malloc(sizeof(pthread_t) * ft_atol(av[1]));
	philolst = create_philolst(philolst, ft_atol(av[1]));
	return (0);
}
