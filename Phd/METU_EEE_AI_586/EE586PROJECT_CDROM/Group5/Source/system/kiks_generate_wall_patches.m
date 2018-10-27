% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_generate_wall_patches(arena)

KIKS_ARENA_CONTOUR = kiks_contour(arena);
[KIKS_ARENA_BWLABEL,nowallobjs] = bwlabel(arena,4);
figure; hold on;
for i=1:nowallobjs
    KIKS_WALL_COORDS = kiks_blob2polygon(KIKS_ARENA_BWLABEL,KIKS_ARENA_CONTOUR,i);
    if ~isempty(KIKS_WALL_COORDS) plot(KIKS_WALL_COORDS(:,2),KIKS_WALL_COORDS(:,1)); end;
end;
