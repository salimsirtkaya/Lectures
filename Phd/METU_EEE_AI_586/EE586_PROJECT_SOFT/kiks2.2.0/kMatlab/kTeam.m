function kTeam(ref)
%KTEAM   Display the list of members of the K-Team
%
%kTeam(ref)
%  Use the reference obtained with kopen.

% Written by Yves Piguet, 9/98.

kcmd(ref,'k-team',1)
