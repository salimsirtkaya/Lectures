function r = kcmd(ref,cmd,multiline)
%KCMD     high-level command for communicating with Khepera
%
%kcmd(command, multiline)
%  send a single command to Khepera (command shouldn't contain
%  the cr)
%
%r = kcmd(command)
%  send a command to Khepera and set r to its reply (without cr)
%
%r = kcmd(command, multiline)
%  continue receiving until timeout if multiline

% Written by Yves Piguet, 8/98.
% Modified by Theodor Storm for use with KiKS, 3/01.

if nargin <= 2
	multiline = 0;
end

cmdlf = [cmd,10];	% add a linefeed
if multiline
% ---- KiKS modification begins ----
%  r = eval('ksend(cmdlf,ref,0)','ksends(cmdlf,ref,0)')
%  use static buffer if the dynamic buffer is not supported
   r=kiks_ksend(cmdlf,ref,0);	% let kiks_ksend handle this!
   				% (kiks_ksend will call ksend/ksends if 'ref'
   				% is a real robot)
else
%  r = eval('ksend(cmdlf,ref)','ksends(cmdlf,ref)');
   r=kiks_ksend(cmdlf,ref);	% let kiks_ksend handle this!
   				% (kiks_ksend will call ksend/ksends if 'ref'
   				% is a real robot)   
end
% ---- KiKS modification ends ----
