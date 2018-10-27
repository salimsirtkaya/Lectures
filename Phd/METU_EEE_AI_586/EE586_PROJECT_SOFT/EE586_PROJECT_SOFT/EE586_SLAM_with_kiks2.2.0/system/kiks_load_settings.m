% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function retstr=kiks_load_settings
global KIKS_COMPUTER_SPEED KIKS_KSEND_CONSTANT KIKS_CALIBRATE_BAUD KIKS_KSEND_VARIATION KIKS_COMPUTER_SPEED
% loads computer-specific settings
retstr='';
datapath = which('kiks_data.mat');
if ~isempty(datapath)
    kiks_status(sprintf('Loading settings from %s\n',datapath));
    KIKS_COMPUTER_SPEED=0;
    load kiks_data
    if KIKS_KSEND_CONSTANT>0
        retstr=sprintf('Calibrated at %d baud (KIKS_KSEND_CONSTANT=%1.1f +-%1.1f%%)\nComputer speed index is %1.2f',KIKS_CALIBRATE_BAUD,KIKS_KSEND_CONSTANT,abs(KIKS_KSEND_VARIATION/(2*KIKS_KSEND_CONSTANT))*100,KIKS_COMPUTER_SPEED);
    else
        retstr=sprintf('Computer speed index is %1.2f',KIKS_COMPUTER_SPEED);
    end;
    
    if KIKS_COMPUTER_SPEED==0
        retstr=[retstr '\nWarning: Computer speed not measured, please run kiks_calibrate again.\n<KiKS warning> Type "help kiks_calibrate" for more information.'];
    end;
    
    return;
else
    KIKS_CALIBRATE_BAUD=9600;
    KIKS_KSEND_CONSTANT=0;
    KIKS_KSEND_VARIATION=0;
    KIKS_COMPUTER_SPEED=0;
    retstr=sprintf('Warning: Could not load computer-specific settings;\n<KiKS warning> type "help kiks_calibrate" for more information.');
end;
