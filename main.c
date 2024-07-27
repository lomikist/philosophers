/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vyepremy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:09:27 by vyepremy          #+#    #+#             */
/*   Updated: 2024/07/27 16:20:11 by vyepremy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define USAGE "Usage: \n\
	./philosophers [NUM_PHILOS] [THINK_TIME] [EAT_TIME] [SLEEP_TIME] [[NUM_MEALS]]\n\n\
	NUM_PHILOS   -  number of philosophers \n\
	THINK_TIME   -  maximum time philosopher can stay hungry/thinking (ms) \n\
	EAT_TIME     -  time philosopher spends eating (ms) \n\
	SLEEP_TIME   -  time philosopher spends sleeping (ms) \n\
	[NUM_MEALS]  -  optional, number of meals each philosophers eat to stop simulation\n"
#define MALLOC_ERROR "Memory Error\n"

typedef enum s_status {
	eating = 0,
	sleeping,
	thinking
} t_status;

struct s_philo;

typedef struct	s_data
{
	unsigned int	n_philos;
	unsigned int	think_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	n_dinners;
	struct s_philo	*philos;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
} t_data;

typedef struct	s_philo
{
	unsigned int	id;
	unsigned int	eat_count;
	t_status		status;
	t_data			*data;
	pthread_t		t1;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

unsigned int	to_uint(char *str, int *status)
{
	long	number;

	if (*str == '+')
		str++;
	if (*str == '\0')
		*status = EXIT_FAILURE;
	while (*str == '0')
		++str;
	number = 0;
	while (*str != '\0' && *status == EXIT_SUCCESS)
	{
		if (*str <= '9' && *str >= '0')
			number = number * 10 + (*str++ - '0');
		else
			*status = EXIT_FAILURE;
		if (number > UINT_MAX)
			*status = EXIT_FAILURE;
	}
	return (number);
}

size_t	ft_strlen(const char *c)
{
	size_t	size;

	size = 0;
	while (c[size] != '\0')
		++size;
	return (size);
}

void	message(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

int	init_args(int argc, char **argv, t_data *data)
{
	int	status;

	status = EXIT_SUCCESS;
	if (argc != 5 && argc != 6)
		status = EXIT_FAILURE;
	if (!status)
		data->n_philos = to_uint(argv[1], &status);
	if (!status)
		data->think_time = to_uint(argv[2], &status);
	if (!status)
		data->eat_time = to_uint(argv[3], &status);
	if (!status)
		data->sleep_time = to_uint(argv[4], &status);
	data->n_dinners = 0;
	if (!status && argc == 6)
		data->n_dinners = to_uint(argv[5], &status);
	return (status);
}

t_philo *init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->tid = (pthread_t *)malloc(sizeof(pthread_t) * data->n_philos);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n_philos);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_philos);
	if (!data->tid || !data->forks || !data->philos)
		return (NULL);
	data->philos[0].l_fork = &data->forks[0];
	data->philos[0].r_fork = &data->forks[data->n_philos - 1];
	while (++i < data->n_philos)
	{
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[i - 1];
	}
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
		data->philos[i].status = sleeping;
		data->philos[i].eat_count = 0;
	}
	return (data->philos);
}

void	start_dinner(t_philo *philos)
{

}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	data;

	if (init_args(argc, argv, &data) == EXIT_SUCCESS)
	{
		philos = init_philos(&data);
		if (philos)
			start_dinner(philos);
		else
			message(MALLOC_ERROR);
	}
	else
		message(USAGE);
	return (0);
}
