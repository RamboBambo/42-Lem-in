#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

typedef struct	s_ants
{
	int				num;
	int				score;
	struct s_rooms	*room;
	// struct s_ants	*next;
}				t_ants;

typedef	struct	s_tunnels
{
	struct	s_rooms		*exit;
	struct	s_tunnels	*next;
}				t_tunnels; 

typedef struct	s_rooms
{
	char				*name;
	int					occupied;
	int					ant_count;
	int					points;
	int					x_coord;
	int					y_coord;
	int					marked;
	struct s_rooms		*next;
	struct s_tunnels 	*tun_list;
}				t_rooms;

typedef	struct	s_map
{
	struct	s_rooms	*end;
	struct	s_rooms	*start;
	int				all_count;
	int				valid;
}				t_map;

t_rooms		*lm_newroom(char *name, int x, int y);
t_rooms		*lm_addroom(t_map **map, char *name, int x, int y, int *flag);
t_tunnels	*lm_newtun(t_rooms *room);
t_tunnels	*lm_addtun(t_rooms *room1, t_rooms *room2);
t_ants	*lm_parse_map(t_map **map, char *argv[]);
void	lm_printtunnels(t_tunnels *head);
void	lm_printrooms(t_rooms *head);
void	lm_printants(t_ants *list, int count);
int	lm_all_scored(t_rooms *room);
void	lm_calcpoints_r(t_rooms *prev, t_rooms *room, int pts);
void	lm_calcpoints(t_map *map);
void	lm_move_ants(t_map map, t_ants *ants, int i, t_rooms *to_move);
int	lm_find_next_path(t_map map, t_ants *ants);
int	lm_all_crawled(t_rooms *room);
void		lm_valid_path(t_map *maps, t_rooms *prev, t_rooms *room);
int	is_room(char *str, t_map **map, int *flag);
int	is_link(char *str, t_map **map);
#endif