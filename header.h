//
// header.h for PSU_2016_malloc in /home/morel_j/Documents/epitech/annee_2/semestre_2/unix_memory/PSU_2016_malloc
//
// Made by Antoine Morel
// Login   <antoine.morel@epitech.net>
//
// Started on  Tue Jan 24 16:26:34 2017 Antoine Morel
// Last update Wed Jan 25 00:16:11 2017 Antoine Morel
//

#ifndef			PSU_2016_MALLOC_HEADER_H_
# define		PSU_2016_MALLOC_HEADER_H_

#include		<stdlib.h>

#define			FREE		0
#define			USED		1
#define			EOS (void *)header + sizeof(t_header) + header->size

typedef struct		s_header
{
  size_t		size;
  struct s_header	*previous;
  char			status;
}__attribute__((packed))t_header;

#endif			/* !PSU_2016_MALLOC_HEADER_H_ */
