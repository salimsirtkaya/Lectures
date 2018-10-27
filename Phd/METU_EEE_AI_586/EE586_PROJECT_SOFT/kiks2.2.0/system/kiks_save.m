function kiks_save

[filename,pathname] = uiputfile({'*.kad'},'Save arena');

if length(filename)>1
    arena = [pathname filename];
    if isempty(findstr(lower([pathname filename]),'.kad'))
        arena = [arena '.kad'];
    end;
    %imwrite(uint8(KIKS_ARENA_COLORMASK_ORIG),arena,'TIFF');
    %if isempty(KIKS_ARENA_WALLS)
    %    walls=kiks_generate_wall_polygons(KIKS_ARENA_COLORMASK_ORIG);
    %else
    %    walls=KIKS_ARENA_WALLS;
    %end;
    walls=kiks_arena_walls;
    save(arena,'walls','-MAT');
    kiks_status(sprintf('Saved arena to %s\n',arena));
end;

%function kiks_save
%global KIKS_ARENA_MASK_ORIG KIKS_ARENA_COLORMASK_ORIG

%[filename,pathname] = uiputfile({'*.tif'},'Choose arena file to open');

%if length(filename)>1
%    arena = [pathname filename];
%    if isempty(findstr(lower([pathname filename]),'.tif'))
%        arena = [arena '.tif'];
%    end;
%    imwrite(uint8(KIKS_ARENA_COLORMASK_ORIG),arena,'TIFF');
%end;