
%%%find the Ambiant light

port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication


lights=kAmbient(ref);

lights
    
    kiks_kclose(ref); % close the port