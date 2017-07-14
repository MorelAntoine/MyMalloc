/*
** memory.c for PSU_2016_malloc in /home/morel_j/Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc
**
** Made by Antoine Morel
** Login   <antoine.morel@epitech.net>
**
** Started on  Tue Jan 24 16:27:57 2017 Antoine Morel
** Last update Thu Jan 26 17:33:06 2017 Antoine Morel
*/

#define		_GNU_SOURCE
#include	<stdio.h>
#include	<string.h>
#include	<pthread.h>
#include	"memory.h"

static void	*begin = NULL;
static size_t	size_last_elem = 0;
pthread_mutex_t mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

/*
 * Allocation
 */

void		*malloc(size_t size)
{
  void		*ptr;

  if (size > 0xFFFFFFFF)
    return (NULL);
  if ((begin = sbrk(0)) ==  (void *) -1)
    return (NULL);
  pthread_mutex_lock(&mutex);
  ptr = malloc_system(begin, size, &size_last_elem);
  pthread_mutex_unlock(&mutex);
  return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
  void		*ptr;

  if (nmemb == 0 || size == 0)
    return (NULL);
  if (begin == NULL)
    if ((begin = sbrk(0)) ==  (void *) -1)
      return (NULL);
  pthread_mutex_lock(&mutex);
  if ((ptr = malloc(nmemb * size)) == NULL)
  {
    pthread_mutex_unlock(&mutex);
    return (NULL);
  }
  memset(ptr, 0 , nmemb * size);
  pthread_mutex_unlock(&mutex);
  return (ptr);
}

/*
 * Modify
 */

void		*realloc(void *ptr, size_t size)
{
  t_header	*header;
  void		*n_ptr;

  if (size == 0)
  {
    free(ptr);
    return (NULL);
  }
  if (ptr == NULL)
    return (malloc(size));
  if (begin == NULL)
    return (NULL);
  pthread_mutex_lock(&mutex);
  header = ptr - sizeof(t_header);
  n_ptr = realloc_system(header, size);
  pthread_mutex_unlock(&mutex);
  return (n_ptr);
}

/*
 * Release
 */

void		free(void *ptr)
{
  t_header	*header;

  if (ptr == NULL || begin == NULL)
    return ;
  pthread_mutex_lock(&mutex);
  header = ptr - sizeof(t_header);
  free_system(header, &size_last_elem);
  pthread_mutex_unlock(&mutex);
}

/*
 * Display
 */

void		show_alloc_mem(void)
{
  t_header	*header;
  void		*end;

  if ((end = sbrk(0)) == (void *) -1)
    return ;
  printf("break : %p\n", end);
  if ((header = begin) == NULL)
    return ;
  while (header != end)
  {
    if (header->status == USED)
      printf("%p - %p : %zu bytes\n", header + 1, EOS, header->size);
    header = EOS;
  }
}
