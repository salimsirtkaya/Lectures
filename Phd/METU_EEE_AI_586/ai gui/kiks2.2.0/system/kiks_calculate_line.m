function [ray_xvals,ray_yvals]=kiks_calculate_line(start,stop)

[rad,deg,dist]=kiks_calculate_angle(start,stop);
ray_xvals = round((0:dist)*cos(rad)+start(1));
ray_yvals = round((0:dist)*sin(rad)+start(2));