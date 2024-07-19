# About

One or more philosophers are sitting at a round table either eating, either thinking,
either sleeping. While they are eating, they do not think or sleep; while thinking
they don’t eat or sleep; and, of course, while sleeping, they do not eat or think.

The philosophers sit at a circular table with a large bowl of spaghetti in the center.

There are some forks on the table. Serving and eating spaghetti with a single fork
is very inconvenient, so the philosophers will eat with two forks, one for each hand.

Each time a philosopher finishes eating, they will drop their forks and start sleeping.
Once they have finished sleeping, they will start thinking. The simulation stops
when a philosopher dies.

Every philosopher needs to eat and they should never starve.

## How to run

        ./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

The program takes the following arguments: 

    number_of_philosophers: is the number of philosophers and also the number
of forks.
    
    time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting their last meal or the beginning of the simulation,
it dies.
    
    time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time they will need to keep the two forks.
    
    time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.
    
    number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.

## Additional information
Each philosopher has been given a number from 1 to ’number_of_philosophers’. Philosopher number 1 is next to philosopher number ’number_of_philosophers’. Any other philosopher with the number N is seated between philosopher N - 1 and
philosopher N + 1.

Output of the program will look something like this:

    timestamp_in_ms X has taken a fork
    
    timestamp_in_ms X is eating
    
    timestamp_in_ms X is sleeping
    
    timestamp_in_ms X is thinking
    
    timestamp_in_ms X died

Each philosopher is a thread.

One fork between each philosopher, therefore if they are multiple philosophers, there
will be a fork at the right and the left of each philosopher.

To avoid philosophers duplicating forks, I protected the forks state with a mutex for each.
