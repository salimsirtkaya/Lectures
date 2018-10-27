

port=-1; % simulated Khepera
baud=9600; % use 9600 baud
ref=kiks_kopen([port,baud,1]); % open the port for communication

            for i=1:1:10
            kiks_ksend(['D,10,10' 10],ref)
        end
        
      
kiks_kclose(ref); % close the port