//
// memory.h for PSU_2016_malloc in /home/morel_j/Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc
//
// Made by Antoine Morel
// Login   <antoine.morel@epitech.net>
//
// Started on  Tue Jan 24 16:28:55 2017 Antoine Morel
// Last update Wed Jan 25 23:55:12 2017 Antoine Morel
//

#ifndef		PSU_2016_MALLOC_MEMORY_H_
# define	PSU_2016_MALLOC_MEMORY_H_

#include	<unistd.h>
#include	"header.h"

/*
 * Elementary
 */

void		*malloc(size_t size);
void		*malloc_system(void *begin, const size_t size,
				   size_t *size_last_elem);
void		*calloc(size_t nmemb, size_t size);
void		free(void *ptr);
void		free_system(t_header *header, size_t *size_last_elem);

/*
 * Evolve
 */

void		*realloc(void *ptr, size_t size);
void		*realloc_system(t_header *header, const size_t size);

/*
 * Display
 */

void		show_alloc_mem(void);

#endif		/* !PSU_2016_MALLOC_MEMORY_H_ */
