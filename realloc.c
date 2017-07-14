/*
** realloc.c for PSU_2016_malloc in /home/morel_j/Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc
**
** Made by Antoine Morel
** Login   <antoine.morel@epitech.net>
**
** Started on  Wed Jan 25 18:43:32 2017 Antoine Morel
** Last update Wed Jan 25 23:55:07 2017 Antoine Morel
*/

#include	<string.h>
#include	"memory.h"

static void	*resize_ptr(t_header *header, const size_t size,
			       const size_t ncopy)
{
  t_header	*origin;
  void		*ptr;

  origin = header;
  if ((ptr = malloc(size)) == NULL)
    return (NULL);
  memcpy(ptr, origin + 1, ncopy);
  free(origin + 1);
  return (ptr);
}

void		*realloc_system(t_header *header, const size_t size)
{
  if (size > header->size)
    return (resize_ptr(header, size, header->size));
  else if (size < header->size)
    return (resize_ptr(header, size, size));
  return (header + 1);
}
