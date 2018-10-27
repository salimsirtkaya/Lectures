function kBraitenbergG(ref, ksp, action)
%KPROXIMITYG   Display the value of the proximity sensors of Khepera
%
%kProximityG(ref)
%  Display the value of the proximity sensors as an histogram or
%  polar plot
%   Use the "Start" and "Stop" buttons to control 
%   the animation.                                
%  Use the communication parameters specified with kcmd.
%
% Written by Skye Legon, 2/99.
%            Yves Piguet, 8/98.
% parts copyright (c) 1998/99 K-Team SA

%   Adapted from Demo by Ned Gulley, 6-21-93; jae Roh, 10-15-96
% parts Copyright (c) 1984-96 by The MathWorks, Inc.
%   $Revision: 5.7 $  $Date: 1996/10/16 21:47:48 $

% Possible actions:
% initialize
% close
% info

% Information regarding the play status will be held in
% the axis user data according to the following table:

global y   % save robot position as global

if isempty(y)
	y = [0;0;0];
end

play= 1;
stop=-1;

XAxis = [-200 200];
YAxis = [-200 200];

if nargin<2
   ksp = 0.7;
end

if nargin<3,
    action='initialize';
end;

gain = [-5,-15,-18,6,4,4,3,5;4,4,6,-18,-15,-5,5,3] / 400;
offset = 20 * [1;1];

gain = gain * ksp;
offset = offset * ksp;

% put parameters in a string for callback

refstring = sprintf('[%f %f %f %f]',ref);
kspstring = sprintf('%f',ksp);

if strcmp(action,'initialize'),
    oldFigNumber=watchon;

    figNumber=figure( ...
        'Name','Khepera Braitenberg Simulation (c) K-Team SA 1999', ...
        'NumberTitle','off', ...
        'Visible','off');
    colordef(figNumber,'black')
    axes( ...
        'Units','normalized', ...
        'Position',[0.05 0.10 0.75 0.85], ...
        'Visible','off');

    text(0,0,'Press the "Start" button to see the Braitenberg demo', ...
        'HorizontalAlignment','center');
    axis([-1 1 -1 1]);

    eval('set(gcf, ''doublebuffer'', ''on'')','');
	 % unsupported feature of Matlab 5.2 to suppress flashing
	 % eval is used to avoid fatal errors with previous versions

    %===================================
    % Information for all buttons
    labelColor=[0.8 0.8 0.8];
    yInitPos=0.90;
    xPos=0.85;
    btnLen=0.10;
    btnWid=0.10;
    % Spacing between the button and the next command's label
    spacing=0.05;

    %====================================
    % The CONSOLE frame
    frmBorder=0.02;
    yPos=0.05-frmBorder;
    frmPos=[xPos-frmBorder yPos btnLen+2*frmBorder 0.9+2*frmBorder];
    h=uicontrol( ...
        'Style','frame', ...
        'Units','normalized', ...
        'Position',frmPos, ...
        'BackgroundColor',[0.50 0.50 0.50]);
    
    %====================================
    % The START button
    btnNumber=1;
    yPos=0.90-(btnNumber-1)*(btnWid+spacing);
    labelStr='Start';
    cmdStr='start';
    %callbackStr='kBraitenbergG(''start'');';
    callbackStr=['kBraitenbergG(' refstring ',' kspstring ',''start'');'];

    % Generic button information
    btnPos=[xPos yPos-spacing btnLen btnWid];
    startHndl=uicontrol( ...
        'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'String',labelStr, ...
        'Interruptible','on', ...
        'Callback',callbackStr);

    %====================================
    % The STOP button
    btnNumber=2;
    yPos=0.90-(btnNumber-1)*(btnWid+spacing);
    labelStr='Stop';
    % Setting userdata to -1 (=stop) will stop the demo.
    callbackStr='set(gca,''Userdata'',-1)';
    
    % Generic  button information
    btnPos=[xPos yPos-spacing btnLen btnWid];
    stopHndl=uicontrol( ...
        'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'Enable','off', ...
        'String',labelStr, ...
        'Callback',callbackStr);

    %====================================
    % The RESET button
    btnNumber=3;
    yPos=0.90-(btnNumber-1)*(btnWid+spacing);
    labelStr='Reset';
    callbackStr='if ~exist(''y'') global y; end; y=[0;0;0];';
    
    % Generic  button information
    btnPos=[xPos yPos-spacing btnLen btnWid];
    resetHndl=uicontrol( ...
        'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'Enable','off', ...
        'String',labelStr, ...
        'Callback',callbackStr);

    %====================================
    % The INFO button
    labelStr='Info';
    callbackStr=['kBraitenbergG(' refstring ',' kspstring ',''info'');'];
    infoHndl=uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'position',[xPos 0.20 btnLen 0.10], ...
        'string',labelStr, ...
        'call',callbackStr);

    %====================================
    % The CLOSE button
    labelStr='Close';
    callbackStr='close(gcf)';
    closeHndl=uicontrol( ...
        'Style','push', ...
        'Units','normalized', ...
        'position',[xPos 0.05 btnLen 0.10], ...
        'string',labelStr, ...
        'call',callbackStr);
    
    % Uncover the figure
    hndlList=[startHndl stopHndl resetHndl infoHndl closeHndl];
    set(figNumber,'Visible','on', ...
        'UserData',hndlList);

    watchoff(oldFigNumber);
    figure(figNumber);

elseif strcmp(action,'start'),
    axHndl=gca;
    figNumber=gcf;
    hndlList=get(figNumber,'UserData');
    startHndl=hndlList(1);
    stopHndl=hndlList(2);
    resetHndl=hndlList(3);
    infoHndl=hndlList(4);
    closeHndl=hndlList(5);
    set([startHndl resetHndl closeHndl infoHndl],'Enable','off');
    set(stopHndl,'Enable','on');

    % ====== Start of Demo
    set(figNumber,'Backingstore','off');
    % The graphics axis limits are set to values known 
    % to contain the solution.
    set(axHndl, ...
        'XLim',XAxis,'YLim',YAxis, ...
        'Userdata',play, ...
        'XTick',[],'YTick',[], ...
        'Drawmode','fast', ...
        'Visible','on', ...
        'NextPlot','add', ...
        'Userdata',play);
    xlabel('X');
    ylabel('Y');

    % Save L steps and plot like a comet tail.
    L = 50;
    Y = y*ones(1,L);
 
    cla;
    head = line( ...
        'color','r', ...
        'Marker','.', ...
        'markersize',25, ...
        'erase','xor', ...
        'xdata',y(1),'ydata',y(2));
    body = line( ...
        'color','y', ...
        'LineStyle','-', ...
        'erase','none', ...
        'xdata',[],'ydata',[]);
    tail=line( ...
        'color','b', ...
        'LineStyle','-', ...
        'erase','none', ...
        'xdata',[],'ydata',[]);

   WHEEL_RADIUS = 7.81;
   AXLE_LENGTH = 53;
   MM_PER_ENC = pi * 2 * WHEEL_RADIUS / 600;
 
 	kSetEncoders(ref,0,0);  % reset to zero
 	oldPosition = kGetEncoders(ref) * MM_PER_ENC;
 	x1 = y(1);
 	x2 = y(2);
 	Theta = y(3);

   % The main loop
   while (get(axHndl,'Userdata')==play)
 	   sensors = kProximity(ref);			% read the proximity sensors
	   speed = gain * sensors + offset;	% calculate the speed
		kSetSpeed(ref,speed(2),speed(1));		% write the speed

		newPosition = kGetEncoders(ref) * MM_PER_ENC;
		dTheta = (newPosition - oldPosition)' * [-1;1] / AXLE_LENGTH;
		l = (newPosition - oldPosition)' * [1; 1] / 2;
		x1 = x1(end)+cos(Theta + dTheta / 2)*l;
		x2 = x2(end)+sin(Theta + dTheta / 2)*l;
		Theta = Theta + dTheta;
		y = [x1;x2;Theta];
		oldPosition = newPosition;

      % Update the plot
      Y = [y Y(:,1:L-1)];
      set(head,'xdata',Y(1,1),'ydata',Y(2,1))
      set(body,'xdata',Y(1,1:2),'ydata',Y(2,1:2))
      set(tail,'xdata',Y(1,L-1:L),'ydata',Y(2,L-1:L))
      drawnow;

   end;    % Main loop ...
    % ====== End of Demo
    kStop(ref);
    set([startHndl resetHndl closeHndl infoHndl],'Enable','on');
    set(stopHndl,'Enable','off');

elseif strcmp(action,'info');
    helptext = strvcat( ...
       'Program for graphical simulation of Khepera Braitenberg vehicle.',...
       ' ',...
       'Authors: Skye Legon, 2/99',...
       '         Yves Piguet, 8/98',...
       ' ',...
       'Copyright 1999 K-Team SA');
    helpwin(helptext,'Khepera Information');

end;    % if strcmp(action, ...

