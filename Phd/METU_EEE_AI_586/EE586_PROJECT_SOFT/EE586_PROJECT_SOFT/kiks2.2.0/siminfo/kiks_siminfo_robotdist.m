% function res=kiks_siminfo_robotdist
% returns the distance the simulated robot has travelled:
% [FWD BWD STRAIGHT]
% FWD: total distance moved forwards
% BWK: total distance moved backwards
% STRAIGHT: the distance, in a straight line, from
% the starting position (when kiks_kopen was called)
% to the current position of the Khepera.
% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------
function res=kiks_siminfo_robotdist
global KIKS_DIST_FWD;
global KIKS_DIST_BWD;
global KIKS_DIST_STRAIGHT;
res = [KIKS_DIST_FWD KIKS_DIST_BWD KIKS_DIST_STRAIGHT];