/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:56:20 by rpepi             #+#    #+#             */
/*   Updated: 2024/06/18 15:24:24 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdatomic.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				id;
	atomic_llong	last_meal;
	int				l_fork_id;
	int				r_fork_id;
	atomic_int		nb_meals_eated;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				nb_meals;
	atomic_int		all_have_eat;
	long long		starting_time;
	int				one_is_dead;
	pthread_mutex_t	fork_mutex[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	meals_mutex;
	t_philo			philos[200];
}					t_data;

int					ft_atoi(const char *nptr);
long long			curr_time(void);
int					ft_init_all(t_data *data, char **argv);
int					create_threads(t_data *data);
void				*ft_routine(void *pointer);
void				exit_threads(t_data *data, t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				message(char *str, t_data *data, int philo_id);
void				dead_check(t_data *data, t_philo *philo);
long long			time_diff(long long past, long long pres);
void				ft_sleep(long long time, t_data *data);
#endif