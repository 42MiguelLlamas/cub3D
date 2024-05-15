#include "../cube.h"

void	init_texture(t_texture *texture, t_ident ident)
{
    texture->id = ident;
    texture->path = NULL;
}

void	init_color(t_color *color, t_ident ident)
{
    color->id = ident;
    color->r = 0;
    color->g = 0;
    color->b = 0;
}

void	init_mapcheck(t_mapcheck *mc)
{
    mc->no = 0;   
	mc->so = 0;
	mc->we = 0;
	mc->ea = 0;
	mc->f = 0;
	mc->c = 0;
	mc->in_map = 0;
}

void	init_data(t_data *game)
{
    game->mapname = NULL;
    game->map = NULL;
    init_texture(&game->north, NO);
    init_texture(&game->south, SO);
    init_texture(&game->west, WE);
    init_texture(&game->east, EA);
    init_color(&game->floor, F);
    init_color(&game->ceiling, C);
    init_mapcheck(&game->mapcheck);
    game->rows = 0;
    game->cols = 0;
}
