function KproximityG(ref, action)
%KPROXIMITYG   Display the value of the proximity sensors of Khepera
%
%kProximityG(ref)
%  Display the value of the proximity sensors as an histogram
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

% Information regarding the play status will be held in
% the Userdata of the start button handle (which is stored in 
% the figure Userdata) according to the following table:
% (can't use axis Userdata as it gets clobbered by the bar command)
play= 1;
stop=-1;

maxValue = 1024;		% maximum value of a sensor

refstring = sprintf('[%f %f %f %f]',ref);
   
if nargin < 2,
    action='initialize';
end;

if strcmp(action,'initialize'),
    oldFigNumber=watchon;

    figNumber=figure( ...
        'Name','Khepera Proximity Sensors (c) K-Team SA 1999', ...
        'NumberTitle','off', ...
        'Visible','off');
    colordef(figNumber,'black')
    axes( ...
        'Units','normalized', ...
        'Position',[0.07 0.10 0.75 0.85], ...
        'Visible','off');

    text(0,0,'Press the "Start" button to begin', ...
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
    btnHt=0.10;
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
    callbackStr=['kProximityG(' refstring ',''start'');'];

    % Generic button information
    btnPos=[xPos yPos-spacing btnLen btnWid];
    startHndl=uicontrol( ...
        'Style','pushbutton', ...
        'Units','normalized', ...
        'Position',btnPos, ...
        'String',labelStr, ...
        'Interruptible','on', ...
        'Userdata',stop, ...
        'Callback',callbackStr);
   %====================================
   % The MODE popup button
   btnNumber=2;
   yPos=0.90-(btnNumber-1)*(btnHt+spacing);
   textStr='Style';
   popupStr=reshape(' hist  polar',6,2)';
   
   % Generic button information
   btnPos1=[xPos yPos-spacing+btnHt/2 btnWid btnHt/2];
   btnPos2=[xPos yPos-spacing btnWid btnHt/2];
   popupHndl=uicontrol( ...
      'Style','text', ...
      'Units','normalized', ...
      'Position',btnPos1, ...
      'String',textStr);
   btnPos=[xPos yPos-spacing btnWid btnHt/2];
   popupHndl=uicontrol( ...
      'Style','popup', ...
      'Units','normalized', ...
      'Position',btnPos2, ...
      'String',popupStr);
   
    %====================================
    % The STOP button
    btnNumber=3;
    yPos=0.90-(btnNumber-1)*(btnHt+spacing);
    labelStr='Stop';
    % Setting userdata to -1 (=stop) will stop the demo.
    %callbackStr='set(gca,''Userdata'',-1)';
    callbackStr='eval(''v=get(gcf,''''Userdata'''');set(v(1),''''Userdata'''',-1);'')';
    
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
    % The INFO button
    labelStr='Info';
    callbackStr=['kProximityG(' refstring ',''info'');'];
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
    hndlList=[startHndl popupHndl stopHndl infoHndl closeHndl];
    set(figNumber,'Visible','on', ...
        'UserData',hndlList);

    watchoff(oldFigNumber);
    figure(figNumber);

elseif strcmp(action,'start'),
    figNumber=gcf;
    hndlList=get(figNumber,'UserData');
    startHndl=hndlList(1);
    popupHndl=hndlList(2);
    stopHndl=hndlList(3);
    infoHndl=hndlList(4);
    closeHndl=hndlList(5);
    set(startHndl,'Userdata',play);
    set([startHndl closeHndl infoHndl],'Enable','off');
    set(stopHndl,'Enable','on');
    set(figNumber,'Backingstore','off');
        
    % ====== Start of Demo
    
    sensorOrder = [8,1:7];	% back left sensor displayed first
    sensorAngles = pi / 180 * [180,135,100,80,45,0,260,280];

    % The main loop
    
    style = 0;  % initialize to impossible value to force plot setup
    sensors = kProximity(ref);
	 sensors = sensors(sensorOrder);

    while (get(startHndl,'Userdata')==play)
    	% initialize plots if we're just starting, or if we change modes
    	if style ~= get(popupHndl,'Value');
    		style = get(popupHndl,'Value');
    		if style==1 % hist
         	barHndl = bar(sensors(sensorOrder));
         	set(barHndl,'EraseMode','background')
         	vertices = get(barHndl,'Vertices');
         	faces = get(barHndl,'Faces');
          	axis([0.5,8.5,0,maxValue+6]); % 1024 + 6 = 1030
         else % polar
				% simplified polar routine with fixed max radius 
				rmax = maxValue;
				sensors(find(sensors<50)) = 50; % set lower bound
				r = sensors';
				theta = sensorAngles(sensorOrder);
				[dmy, ix] = sort(theta);
				theta = kron(theta(ix),[1,1]) + repmat([-0.03,0.03],1,length(ix));
				% draw circle
				phi = pi * (0:0.05:2);
				plot(rmax*cos(phi), rmax*sin(phi));
				r = kron(r(ix),[1,1]);
				polarHndl = fill(r.*cos(theta), r.*sin(theta), 'g');
				set(polarHndl,'EraseMode','background');
				axis('equal');
				axis((rmax + 6) * [-1,1,-1,1]); % 1024 + 6 = 1030
				drawnow
         end
      end

      sensors = kProximity(ref);
  		sensors = sensors(sensorOrder);

      if style==1 % hist
      	for i=1:length(sensors)
      		vertices(faces(i,2:3),2) = sensors(i);
      	end
      	set(barHndl,'Vertices',vertices);
      else % polar
			sensors(find(sensors<50)) = 50; % set lower bound
			r = sensors';
			r = kron(r(ix),[1,1]);
			vertices = [r.*cos(theta); r.*sin(theta)]';
			set(polarHndl,'Vertices',vertices);
      end
      drawnow
    end;    % Main loop ...
    
    % ====== End of Demo
    set([startHndl closeHndl infoHndl],'Enable','on');
    set(stopHndl,'Enable','off');
    
elseif strcmp(action,'info')
    helptext = strvcat( ...
       'Program for graphical display of Khepera proximity sensors.',...
       ' ',...
       'Authors: Skye Legon, 2/99',...
       '         Yves Piguet, 8/98',...
       ' ',...
       'Copyright 1999 K-Team SA');
    helpwin(helptext,'Khepera Information');
    
end;    % if strcmp(action, ...

