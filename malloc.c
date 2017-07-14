/*
** malloc.c for PSU_2016_malloc in /home/morel_j/Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc
**
** Made by Antoine Morel
** Login   <antoine.morel@epitech.net>
**
** Started on  Wed Jan 25 13:25:53 2017 Antoine Morel
** Last update Wed Jan 25 23:02:04 2017 Antoine Morel
*/

#include	"memory.h"

static void	*push_at_end_heap(const size_t size, size_t *size_last_elem)
{
  t_header	*header;

  if ((header = sbrk(sizeof(t_header) + size)) == (void *) -1)
    return (NULL);
  header->size = size;
  header->status = USED;
  header->previous = NULL;
  if ((*size_last_elem) != 0)
    header->previous = (void *)header - (*size_last_elem) - sizeof(t_header);
  (*size_last_elem) = size;
  return (header + 1);
}

static void	*search_free_space(void *begin, const size_t size)
{
  t_header	*header;
  void		*end;

  header = begin;
  if ((end = sbrk(0)) == (void *) -1)
    return (NULL);
  while (header != end)
  {
    if (header->status == FREE && (header->size == sizeof(t_header) + size ||
      header->size >= sizeof(t_header) * 2 + size + 1))
      return (header);
    header = EOS;
  }
  return (NULL);
}

static void	*push_at_pos_heap(t_header *header, const size_t size)
{
  t_header	*leftovers;
  size_t	old_size;
  t_header	*next;

  old_size = header->size;
  next = EOS;
  header->size = size;
  header->status = USED;
  leftovers = EOS;
  leftovers->size = old_size - size - sizeof(t_header);
  leftovers->status = FREE;
  leftovers->previous = header;
  next->previous = leftovers;
  return (header + 1);
}

void		*malloc_system(void *begin, const size_t size,
				   size_t *size_last_elem)
{
  t_header	*header;

  if ((header = search_free_space(begin, size)) != NULL)
    return (push_at_pos_heap(header, size));
  return (push_at_end_heap(size, size_last_elem));
}
