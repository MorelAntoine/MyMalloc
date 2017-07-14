/*
** free.c for PSU_2016_malloc in /home/morel_j/Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc
**
** Made by Antoine Morel
** Login   <antoine.morel@epitech.net>
**
** Started on  Tue Jan 24 22:14:26 2017 Antoine Morel
** Last update Wed Jan 25 23:07:09 2017 Antoine Morel
*/

#include	"memory.h"

static void	free_end_heap(t_header *header, size_t *size_last_elem)
{
  (*size_last_elem) = (header->previous ? header->previous->size : 0);
  if (header->previous && header->previous->status == FREE)
  {
    (*size_last_elem) = (header->previous->previous ?
			 header->previous->previous->size : 0);
    sbrk(-sizeof(t_header) * 2 - header->size - header->previous->size);
  }
  else
    sbrk(-sizeof(t_header) - header->size);
}

static void	merge_previous(t_header **previous, t_header **header,
				  t_header **next,
				  const void *end)
{
  (*previous)->size += sizeof(t_header) + (*header)->size;
  (*header) = (*previous);
  (*previous) = (*header)->previous;
  if ((*next) != end)
    (*next)->previous = (*header);
}

static void	merge_next(t_header **header, t_header **next,
			      size_t *size_last_elem,
			      const void *end)
{
  (*header)->size += sizeof(t_header) + (*next)->size;
  if ((void *)(*header) + sizeof(t_header) + (*header)->size != end)
  {
    (*next) = (void *)(*header) + sizeof(t_header) + (*header)->size;
    (*next)->previous = (*header);
  }
  else
    free_end_heap((*header), size_last_elem);
}

static void	merge_segment(t_header *previous, t_header *header,
				 t_header *next,
				 size_t *size_last_elem)
{
  void		*end;

  if ((end = sbrk(0)) == (void *) -1)
    return ;
  if (previous && previous->status == FREE)
    merge_previous(&previous, &header, &next, end);
  if (next != end && next->status == FREE)
    merge_next(&header, &next, size_last_elem,end);
}

void		free_system(t_header *header, size_t *size_last_elem)
{
  t_header	*next;

  if (EOS == sbrk(0))
    free_end_heap(header, size_last_elem);
  else
  {
    header->status = FREE;
    next = EOS;
    merge_segment(header->previous, header, next, size_last_elem);
  }
}
