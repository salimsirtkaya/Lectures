function r = kFlush(ref)
%KFLUSH   Flush the buffer
%kflush(ref)
%  Use the reference obtained with kopen.
%  NOTE: this command waits for "timeout" seconds and then displays
%        the buffer with "Command not found" at the bottom.

disp('Buffer contents:')
disp(kcmd(ref,' ',1)) 