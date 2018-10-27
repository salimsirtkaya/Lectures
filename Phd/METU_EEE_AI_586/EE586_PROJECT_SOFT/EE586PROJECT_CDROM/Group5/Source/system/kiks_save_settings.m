% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function retstr=kiks_save_settings
global KIKS_SETTINGS_DIR KIKS_COMPUTER_SPEED KIKS_KSEND_CONSTANT KIKS_CALIBRATE_BAUD KIKS_KSEND_VARIATION
retstr='';
if ~isempty(KIKS_SETTINGS_DIR)
    datapath = [KIKS_SETTINGS_DIR '/kiks_data.mat'];
else
    datapath = which('kiks_data.mat');
end;

if ~isempty(datapath)
    kiks_status(sprintf('Saving settings to %s\n',datapath));
    try
        save(datapath,'KIKS_KSEND_CONSTANT','KIKS_CALIBRATE_BAUD','KIKS_KSEND_VARIATION','KIKS_COMPUTER_SPEED');
    catch
        kiks_status(sprintf('Error: Could not write to %s\n',datapath));
    end;
    return;
else
    if ~isempty(KIKS_SETTINGS_DIR)
        savepath = [KIKS_SETTINGS_DIR '/']
    else
        savepath = kiks_getsystempath;
    end;
    
    savepath = [savepath 'kiks_data.mat'];
    kiks_status(sprintf('Saving settings to %s\n',savepath));   
    try
        save(savepath,'KIKS_KSEND_CONSTANT','KIKS_CALIBRATE_BAUD','KIKS_KSEND_VARIATION','KIKS_COMPUTER_SPEED');
    catch
        kiks_status(sprintf('Error: Could not write to %s\n',savepath));
    end;      
end;
