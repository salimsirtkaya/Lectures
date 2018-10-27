function kiks_load

[filename,pathname] = uigetfile({'*.kad';'*.tif'},'Load arena');

if length(filename)>1
    arena = [pathname filename];
    kiks_arena(arena);
end;