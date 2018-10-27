%%Salim SIRTKAYA EE706 Project
%% Convert the navigation frame velocities to
%% body frame velocities
function [V_bx, V_by, V_bz] = Convert_nav2body(filename)
load filename;