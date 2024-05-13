/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:03:56 by pepi              #+#    #+#             */
/*   Updated: 2024/05/13 10:36:57 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *ft_routine(void *pointer)
{
    t_philo *philo;
    t_data *data;
    
    philo = (t_philo *)pointer;
    data = philo->data;
    if (philo->id % 2)
		usleep(15000);
	while (!(data->one_is_dead))
	{
		eating(philo);
		if (data->all_have_eat)
			break ;
		sleeping(philo);
		thinking(philo);
	}
    return (NULL);
}

int create_threads(t_data *data)
{
    int i;
    t_philo *philo;
   
    i = 0;
    philo = data->philos;
    data->starting_time = get_current_time();
    while (i < data->nb_philos)
    {
        if (pthread_create(&(philo[i].thread), NULL, ft_routine, &(philo[i])))
            return (1);
        philo[i].last_meal = get_current_time();
        i++;
    }
    dead_check(data, data->philos);
    exit_threads(data, philo);
    return (0);
}