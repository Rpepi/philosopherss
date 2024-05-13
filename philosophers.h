/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:23:34 by pepi              #+#    #+#             */
/*   Updated: 2024/05/13 10:49:50 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>

#define PHILO_MAX 200

typedef struct s_philo
{
	int					id;
	long long			last_meal;
	int					l_fork_id;
	int					r_fork_id;
	int					nb_meals_eated;
	pthread_t			thread;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					nb_meals;
	int					all_have_eat;
	long long			starting_time;
	int					one_is_dead;
	pthread_mutex_t		fork_mutex[250];
	pthread_mutex_t		writing;
	pthread_mutex_t		meals_mutex;
	t_philo				philos[200];
}	t_data;


int				ft_atoi(const char *str);
long long		get_current_time(void);
int 			ft_init_all(t_data *data, char   **argv);
int 			create_threads(t_data *data);
void    		*ft_routine(void *pointer);
void			exit_threads(t_data *data, t_philo *philos);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			message(char *str, t_philo *philo);
int				ft_usleep(size_t milliseconds);
void			dead_check(t_data *data, t_philo *philo);
long long		time_diff(long long past, long long pres);
void			ft_sleep(long long time, t_data *data);
#endif