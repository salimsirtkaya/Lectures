function res=kiks_arena_walls
global KIKS_ARENA_WALLS KIKS_ARENA_COLORMASK_ORIG;

if (isempty(KIKS_ARENA_WALLS)) 
    KIKS_ARENA_WALLS=uint16(kiks_generate_wall_polygons(uint16(KIKS_ARENA_COLORMASK_ORIG)));
end;

res = KIKS_ARENA_WALLS;
