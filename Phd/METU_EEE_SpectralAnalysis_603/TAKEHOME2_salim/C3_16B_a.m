%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%% Computer Exercise 3-16 - a %%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all;
close all;
% Generate 10 realzations of data with length=256
L=256;
no_sample=256;
no_real=10;
a=[1 -1.6408 2.2044 -1.4808 0.8145];
b=[1 1.5857 0.9604];
RY=Generate_data(a,b,no_sample,no_real);

for w=1:L
    H(w)=(b(1)+b(2)*exp(-i*2*pi*w/L)+b(3)*exp(-i*2*2*pi*w/L))/...
         (a(1)+a(2)*exp(-i*2*pi*w/L)+a(3)*exp(-i*2*2*pi*w/L)+a(4)*exp(-i*3*2*pi*w/L)+a(5)*exp(-i*4*2*pi*w/L));

    H(w)=H(w)*H(w)';
end

for n=1:L
    freq1(n)=2*(n-1)/L;
end

figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART A -->The true spectrum');
XLABEL('x pi');
YLABEL('True Spectrum');

% Estimate the parameters of the AR & ARMA models 
% (yulewalker,lsar,lsarma,modified yulewalker) for 10 realizations
for k=1:10
    [a_yw_4(:,k),sig_yw_4(k)]=yulewalker(RY(k,:),4);
    [a_yw_8(:,k),sig_yw_8(k)]=yulewalker(RY(k,:),8);
    [a_yw_12(:,k),sig_yw_12(k)]=yulewalker(RY(k,:),12);
    [a_yw_16(:,k),sig_yw_16(k)]=yulewalker(RY(k,:),16);
    
    [a_lsar_4(:,k),sig_lsar_4(k)]=lsar(RY(k,:),4);
    [a_lsar_8(:,k),sig_lsar_8(k)]=lsar(RY(k,:),8); 
    [a_lsar_12(:,k),sig_lsar_12(k)]=lsar(RY(k,:),12);
    [a_lsar_16(:,k),sig_lsar_16(k)]=lsar(RY(k,:),16);
    
    [a_myw1_4(:,k),gamma_myw1_4(:,k)]=mywarma(RY(k,:),4,2,4);
    [a_myw1_8(:,k),gamma_myw1_8(:,k)]=mywarma(RY(k,:),8,4,8); 
    [a_myw1_12(:,k),gamma_myw1_12(:,k)]=mywarma(RY(k,:),12,6,12); 
    [a_myw2_4(:,k),gamma_myw2_4(:,k)]=mywarma(RY(k,:),4,2,8);  
    [a_myw2_8(:,k),gamma_myw2_8(:,k)]=mywarma(RY(k,:),8,4,16);
    [a_myw2_12(:,k),gamma_myw2_12(:,k)]=mywarma(RY(k,:),12,6,24);
    
    [a_lsarma_4(:,k),b_lsarma_4(:,k),sig_lsarma_4(k)]=lsarma(RY(k,:),4,2,8); 
    [a_lsarma_8(:,k),b_lsarma_8(:,k),sig_lsarma_8(k)]=lsarma(RY(k,:),8,4,16); 
    [a_lsarma_12(:,k),b_lsarma_12(:,k),sig_lsarma_12(k)]=lsarma(RY(k,:),12,6,24); 
end

%Compute the power spectral densities of these estimates

for k=1:10
    % PSD estimate of the yule walker method for order=4
    HH=freqz(1,a_yw_4(:,k),L,'whole');
    PSD_yw_4(k,1:L)=HH';
    PSD_yw_4(k,1:L)=abs(PSD_yw_4(k,1:L).^2*sig_yw_4(k));
    % PSD estimate of the yule walker method for order=8
    HH=freqz(1,a_yw_8(:,k),L,'whole');
    PSD_yw_8(k,1:L)=HH';
    PSD_yw_8(k,1:L)=abs(PSD_yw_8(k,1:L).^2*sig_yw_8(k));
    % PSD estimate of the yule walker method for order=12
    HH=freqz(1,a_yw_12(:,k),L,'whole');
    PSD_yw_12(k,1:L)=HH';
    PSD_yw_12(k,1:L)=abs(PSD_yw_12(k,1:L).^2*sig_yw_12(k));
    % PSD estimate of the yule walker method for order=16
    HH=freqz(1,a_yw_16(:,k),L,'whole');
    PSD_yw_16(k,1:L)=HH';
    PSD_yw_16(k,1:L)=abs(PSD_yw_16(k,1:L).^2*sig_yw_16(k));    
    
    %PSD estimate of LS(AR) method for order=4
    HH=freqz(1,a_lsar_4(:,k),L,'whole');
    PSD_lsar_4(k,1:L)=HH';
    PSD_lsar_4(k,1:L) = abs(PSD_lsar_4(k,:)).^2*sig_lsar_4(k);
    %PSD estimate of LS(AR) method for order=8
    HH=freqz(1,a_lsar_8(:,k),L,'whole');
    PSD_lsar_8(k,1:L)=HH';
    PSD_lsar_8(k,1:L) = abs(PSD_lsar_8(k,1:L)).^2*sig_lsar_8(k);
    %PSD estimate of LS(AR) method for order=12
    HH=freqz(1,a_lsar_12(:,k),L,'whole');
    PSD_lsar_12(k,1:L)=HH';
    PSD_lsar_12(k,1:L) = abs(PSD_lsar_12(k,:)).^2*sig_lsar_12(k);
    %PSD estimate of LS(AR) method for order=16
    HH=freqz(1,a_lsar_16(:,k),L,'whole');
    PSD_lsar_16(k,1:L)=HH';
    PSD_lsar_16(k,1:L) = abs(PSD_lsar_16(k,1:L)).^2*sig_lsar_16(k);    
    
    %PSD estimate of LS(ARMA) method for order=4
    HH=freqz(b_lsarma_4(:,k),a_lsarma_4(:,k),L,'whole');
    PSD_lsarma_4(k,1:L)=HH';
    PSD_lsarma_4(k,1:L) = abs(PSD_lsarma_4(k,:)).^2*sig_lsarma_4(k);
    %PSD estimate of LS(ARMA) method for order=8
    HH=freqz(b_lsarma_8(:,k),a_lsarma_8(:,k),L,'whole');
    PSD_lsarma_8(k,1:L)=HH';
    PSD_lsarma_8(k,1:L) = abs(PSD_lsarma_8(k,1:L)).^2*sig_lsarma_8(k);
    %PSD estimate of LS(ARMA) method for order=12
    HH=freqz(b_lsarma_12(:,k),a_lsarma_12(:,k),L,'whole');
    PSD_lsarma_12(k,1:L)=HH';
    PSD_lsarma_12(k,1:L) = abs(PSD_lsarma_12(k,1:L)).^2*sig_lsarma_12(k);    
    
    %PSD estimate of Modified Yule Walker Method with M=n and order=4,2
    PSD_myw1_4(k,1:L)=argamse(gamma_myw1_4(:,k),a_myw1_4(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=n and order=8,4
    PSD_myw1_8(k,1:L)=argamse(gamma_myw1_8(:,k),a_myw1_8(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=n and order=12,6
    PSD_myw1_12(k,1:L)=argamse(gamma_myw1_12(:,k),a_myw1_12(:,k),L)';
    
    %PSD estimate of Modified Yule Walker Method with M=2n and order=4,2
    PSD_myw2_4(k,1:L)=argamse(gamma_myw2_4(:,k),a_myw2_4(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=2n and order=8,4
    PSD_myw2_8(k,1:L)=argamse(gamma_myw2_8(:,k),a_myw2_8(:,k),L)';
    %PSD estimate of Modified Yule Walker Method with M=2n and order=12,6
    PSD_myw2_12(k,1:L)=argamse(gamma_myw2_12(:,k),a_myw2_12(:,k),L)';    
    
end

%%Average PSD estimates
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PSD_yw_4_ave=0;
for k=1:no_real
    PSD_yw_4_ave=(PSD_yw_4_ave+PSD_yw_4(k,:));
end
PSD_yw_4_ave=PSD_yw_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_yw_8_ave=0;
for k=1:no_real
    PSD_yw_8_ave=(PSD_yw_8_ave+PSD_yw_8(k,:));
end
PSD_yw_8_ave=PSD_yw_8_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
PSD_yw_12_ave=0;
for k=1:no_real
    PSD_yw_12_ave=(PSD_yw_12_ave+PSD_yw_12(k,:));
end
PSD_yw_12_ave=PSD_yw_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_yw_16_ave=0;
for k=1:no_real
    PSD_yw_16_ave=(PSD_yw_16_ave+PSD_yw_16(k,:));
end
PSD_yw_16_ave=PSD_yw_16_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsar_4_ave=0;
for k=1:no_real
    PSD_lsar_4_ave=(PSD_lsar_4_ave+PSD_lsar_4(k,:));
end
PSD_lsar_4_ave=PSD_lsar_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsar_8_ave=0;
for k=1:no_real
    PSD_lsar_8_ave=(PSD_lsar_8_ave+PSD_lsar_8(k,:));
end
PSD_lsar_8_ave=PSD_lsar_8_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsar_12_ave=0;
for k=1:no_real
    PSD_lsar_12_ave=(PSD_lsar_12_ave+PSD_lsar_12(k,:));
end
PSD_lsar_12_ave=PSD_lsar_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsar_16_ave=0;
for k=1:no_real
    PSD_lsar_16_ave=(PSD_lsar_16_ave+PSD_lsar_16(k,:));
end
PSD_lsar_16_ave=PSD_lsar_16_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma_4_ave=0;
for k=1:no_real
    PSD_lsarma_4_ave=(PSD_lsarma_4_ave+PSD_lsarma_4(k,:));
end
PSD_lsarma_4_ave=PSD_lsarma_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma_8_ave=0;
for k=1:no_real
    PSD_lsarma_8_ave=(PSD_lsarma_8_ave+PSD_lsarma_8(k,:));
end
PSD_lsarma_8_ave=PSD_lsarma_8_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_lsarma_12_ave=0;
for k=1:no_real
    PSD_lsarma_12_ave=(PSD_lsarma_12_ave+PSD_lsarma_12(k,:));
end
PSD_lsarma_12_ave=PSD_lsarma_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw1_4_ave=0;
for k=1:no_real
    PSD_myw1_4_ave=(PSD_myw1_4_ave+PSD_myw1_4(k,:));
end
PSD_myw1_4_ave=PSD_myw1_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw1_8_ave=0;
for k=1:no_real
    PSD_myw1_8_ave=(PSD_myw1_8_ave+PSD_myw1_8(k,:));
end
PSD_myw1_8_ave=PSD_myw1_8_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw1_12_ave=0;
for k=1:no_real
    PSD_myw1_12_ave=(PSD_myw1_12_ave+PSD_myw1_12(k,:));
end
PSD_myw1_12_ave=PSD_myw1_12_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw2_4_ave=0;
for k=1:no_real
    PSD_myw2_4_ave=(PSD_myw2_4_ave+PSD_myw2_4(k,:));
end
PSD_myw2_4_ave=PSD_myw2_4_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw2_8_ave=0;
for k=1:no_real
    PSD_myw2_8_ave=(PSD_myw2_8_ave+PSD_myw2_8(k,:));
end
PSD_myw2_8_ave=PSD_myw2_8_ave/no_real;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
PSD_myw2_12_ave=0;
for k=1:no_real
    PSD_myw2_12_ave=(PSD_myw2_12_ave+PSD_myw2_12(k,:));
end
PSD_myw2_12_ave=PSD_myw2_12_ave/no_real;

% %PSD estimate of Modified Yule Walker Method with M=n and order=4,4
% HH=freqz(1,a_myw1_4(:,k),L,'whole');
% PSD_myw1_4(k,1:L)=HH';
% PSD_myw1_4(k,1:L) = abs(PSD_myw1_4(k,1:L)).^2;
% %PSD estimate of Modified Yule Walker Method with M=n and order=8,8
% HH=freqz(1,a_myw1_8(:,k),L,'whole');
% PSD_myw1_8(k,1:L)=HH';
% PSD_myw1_8(k,1:L) = abs(PSD_myw1_8(k,1:L)).^2;
% %PSD estimate of Modified Yule Walker Method with M=2n and order=4,4
% HH=freqz(1,a_myw2_4(:,k),L,'whole');
% PSD_myw2_4(k,1:L)=HH';
% PSD_myw2_4(k,1:L) = abs(PSD_myw2_4(k,1:L)).^2;
% %PSD estimate of Modified Yule Walker Method with M=2n and order=8,8
% HH=freqz(1,a_myw2_8(:,k),L,'whole');
% PSD_myw2_8(k,1:L)=HH';
% PSD_myw2_8(k,1:L) = abs(PSD_myw2_8(k,1:L)).^2;
% 
%     for w=1:L
%         Gamma_sum1_1_4=0;
%         Gamma_sum1_2_4=0;
%         Gamma_sum2_1_4=0;
%         Gamma_sum2_2_4=0;
%         Gamma_sum1_1_8=0;
%         Gamma_sum1_2_8=0;
%         Gamma_sum2_1_8=0;
%         Gamma_sum2_2_8=0;        
%         
% %         % PSD estimate of the yule walker method for order=4
% %         PSD_yw_4(k,w)=(a_yw_4(1,k)+a_yw_4(2,k)*exp(-i*2*pi*w/L)+a_yw_4(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     a_yw_4(4,k)*exp(-i*3*2*pi*w/L)+a_yw_4(5,k)*exp(-i*4*2*pi*w/L));
% % 
% %         PSD_yw_4(k,w)=sig_yw_4(k)/(PSD_yw_4(k,w)*PSD_yw_4(k,w)');
% %         % PSD estimate of the yule walker method for order=8
% %         PSD_yw_8(k,w)=(a_yw_8(1,k)+a_yw_8(2,k)*exp(-i*2*pi*w/L)+a_yw_8(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     a_yw_8(4,k)*exp(-i*3*2*pi*w/L)+a_yw_8(5,k)*exp(-i*4*2*pi*w/L));
% % 
% %         PSD_yw_8(k,w)=sig_yw_8(k)/(PSD_yw_8(k,w)*PSD_yw_8(k,w)');        
%         
%         %PSD estimate of LS(AR) method for order=4
% %         PSD_lsar_4(k,w)=(a_lsar_4(1,k)+a_lsar_4(2,k)*exp(-i*2*pi*w/L)+a_lsar_4(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     a_lsar_4(4,k)*exp(-i*3*2*pi*w/L)+a_lsar_4(5,k)*exp(-i*4*2*pi*w/L));
% % 
% %         PSD_lsar_4(k,w)=sig_lsar_4(k)/(PSD_lsar_4(k,w)*PSD_lsar_4(k,w)');
% %         %PSD estimate of LS(AR) method for order=8
% %         PSD_lsar_8(k,w)=(a_lsar_8(1,k)+a_lsar_8(2,k)*exp(-i*2*pi*w/L)+a_lsar_8(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     a_lsar_8(4,k)*exp(-i*3*2*pi*w/L)+a_lsar_8(5,k)*exp(-i*4*2*pi*w/L));
% % 
% %         PSD_lsar_8(k,w)=sig_lsar_8(k)/(PSD_lsar_8(k,w)*PSD_lsar_8(k,w)');
%         
%         
%         %PSD estimate of Modified Yule Walker Method with M=n and order=4,4
%         for h=1:5
%             Gamma_sum1_1_4=Gamma_sum1_1_4+gamma_myw1_4(h)*exp(-i*(h-1)*2*pi*w/L);
%             Gamma_sum1_2_4=Gamma_sum1_2_4+gamma_myw1_4(h)*exp(-i*(1-h)*2*pi*w/L) ;           
%         end
%         PSD_myw1_4(k,w)=abs(Gamma_sum1_1_4+Gamma_sum1_2_4-gamma_myw1_4(1))*PSD_myw1_4(k,w);
%         
%         %PSD estimate of Modified Yule Walker Method with M=n and order=8,8
%         for h=1:5
%             Gamma_sum1_1_8=Gamma_sum1_1_8+gamma_myw1_8(h)*exp(-i*(h-1)*2*pi*w/L);
%             Gamma_sum1_2_8=Gamma_sum1_2_8+gamma_myw1_8(h)*exp(-i*(1-h)*2*pi*w/L);            
%         end
%         PSD_myw1_8(k,w)=abs(Gamma_sum1_1_8+Gamma_sum1_2_8-gamma_myw1_8(1))*PSD_myw1_8(k,w);
%         
%         %PSD estimate of Modified Yule Walker Method with M=2n for order=4,4
%         for h=1:5
%             Gamma_sum2_1_4=Gamma_sum2_1_4+gamma_myw2_4(h)*exp(-i*(h-1)*2*pi*w/L);
%             Gamma_sum2_2_4=Gamma_sum2_2_4+gamma_myw2_4(h)*exp(-i*(1-h)*2*pi*w/L);            
%         end
%         PSD_myw2_4(k,w)=abs(Gamma_sum2_1_4+Gamma_sum2_2_4-gamma_myw2_4(1))*PSD_myw2_4(k,w);
%         %PSD estimate of Modified Yule Walker Method with M=2n for order=8,8
%         for h=1:5
%             Gamma_sum2_1_8=Gamma_sum2_1_8+gamma_myw2_8(h)*exp(-i*(h-1)*2*pi*w/L);
%             Gamma_sum2_2_8=Gamma_sum2_2_8+gamma_myw2_8(h)*exp(-i*(1-h)*2*pi*w/L);            
%         end
%         PSD_myw2_8(k,w)=abs(Gamma_sum2_1_8+Gamma_sum2_2_8-gamma_myw2_8(1))*PSD_myw2_8(k,w);
%         
%         %PSD estimate of LS(ARMA) Method with order=4,4 K=2n        
% %         PSD_lsarma_4(k,w)=(b_lsarma_4(1,k)+b_lsarma_4(2,k)*exp(-i*2*pi*w/L)+b_lsarma_4(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     b_lsarma_4(4,k)*exp(-i*3*2*pi*w/L)+b_lsarma_4(5,k)*exp(-i*4*2*pi*w/L))/...
% %                     (a_lsarma_4(1,k)+a_lsarma_4(2,k)*exp(-i*2*pi*w/L)+a_lsarma_4(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     a_lsarma_4(4,k)*exp(-i*3*2*pi*w/L)+a_lsarma_4(5,k)*exp(-i*4*2*pi*w/L));
% 
% 
% %         PSD_lsarma_4(k,w)=sig_lsarma_4(k)*(PSD_lsarma_4(k,w)*PSD_lsarma_4(k,w)');
%        %PSD estimate of LS(ARMA) Method with order=8,8 K=2n        
% %         PSD_lsarma_8(k,w)=(b_lsarma_8(1,k)+b_lsarma_8(2,k)*exp(-i*2*pi*w/L)+b_lsarma_8(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     b_lsarma_8(4,k)*exp(-i*3*2*pi*w/L)+b_lsarma_8(5,k)*exp(-i*4*2*pi*w/L))/...
% %                     (a_lsarma_8(1,k)+a_lsarma_8(2,k)*exp(-i*2*pi*w/L)+a_lsarma_8(3,k)*exp(-i*2*2*pi*w/L)+...
% %                     a_lsarma_8(4,k)*exp(-i*3*2*pi*w/L)+a_lsarma_8(5,k)*exp(-i*4*2*pi*w/L));
% % 
% %         PSD_lsarma_8(k,w)=sig_lsarma_8(k)*(PSD_lsarma_8(k,w)*PSD_lsarma_8(k,w)');        
%         
%     end
% end

% Plot the PSD estimates of Yule Walker method for order=4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Yule Walker Estimate of order 4');
XLABEL('x pi');
YLABEL('Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_yw_4_ave(1:L/2)/PSD_yw_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_yw_4(k,1:L/2)/PSD_yw_4(k,1),'k');
end

% Plot the PSD estimates of Yule Walker method for order=8
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Yule Walker Estimate of order 8');
XLABEL('x pi');
YLABEL('Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_yw_8_ave(1:L/2)/PSD_yw_8_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_yw_8(k,1:L/2)/PSD_yw_8(k,1),'k');
end

% Plot the PSD estimates of Yule Walker method for order=12
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Yule Walker Estimate of order 12');
XLABEL('x pi');
YLABEL('Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_yw_12_ave(1:L/2)/PSD_yw_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_yw_12(k,1:L/2)/PSD_yw_12(k,1),'k');
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Plot the PSD estimates of Yule Walker method for order=16
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Yule Walker Estimate of order 16');
XLABEL('x pi');
YLABEL('Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_yw_16_ave(1:L/2)/PSD_yw_16_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_yw_16(k,1:L/2)/PSD_yw_16(k,1),'k');
end
% Plot the PSD estimates of LS(AR) method of order 4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART A -->LS(AR) Estimate of order 4');
XLABEL('x pi');
YLABEL('LS(AR) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsar_4_ave(1:L/2)/PSD_lsar_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsar_4(k,1:L/2)/PSD_lsar_4(k,1),'k');
end
% Plot the PSD estimates of LS(AR) method of order 8
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART A -->LS(AR) Estimate of order 8');
XLABEL('x pi');
YLABEL('LS(AR) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsar_8_ave(1:L/2)/PSD_lsar_8_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsar_8(k,1:L/2)/PSD_lsar_8(k,1),'k');
end
% Plot the PSD estimates of LS(AR) method of order 12
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(AR) Estimate of order 12');
XLABEL('x pi');
YLABEL('LS(AR) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsar_12_ave(1:L/2)/PSD_lsar_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsar_12(k,1:L/2)/PSD_lsar_12(k,1),'k');
end
% Plot the PSD estimates of LS(AR) method of order 16
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(AR) Estimate of order 16');
XLABEL('x pi');
YLABEL('LS(AR) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsar_16_ave(1:L/2)/PSD_lsar_16_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsar_16(k,1:L/2)/PSD_lsar_16(k,1),'k');
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Plot the PSD estimates of Modified Yule Walker method for M=n of order=4,2
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Modified Yule Walker Estimate for order=4,2 and M=n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw1_4_ave(1:L/2)/PSD_myw1_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw1_4(k,1:L/2))/PSD_myw1_4(k,1),'k');
end
% Plot the PSD estimates of Modified Yule Walker method for M=n of order=8,4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Modified Yule Walker Estimate for order=8,4 and M=n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw1_8_ave(1:L/2)/PSD_myw1_8_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw1_8(k,1:L/2))/PSD_myw1_8(k,1),'k');
end
% Plot the PSD estimates of Modified Yule Walker method for M=n of order=12,6
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Modified Yule Walker Estimate for order=12,6 and M=n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw1_12_ave(1:L/2)/PSD_myw1_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw1_12(k,1:L/2))/PSD_myw1_12(k,1),'k');
end

% Plot the PSD estimates of Modified Yule Walker method for M=2n of order =4,2
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Modified Yule Walker Estimate for order=4,2 and M=2n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw2_4_ave(1:L/2)/PSD_myw2_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw2_4(k,1:L/2))/PSD_myw2_4(k,1),'k');
end
% Plot the PSD estimates of Modified Yule Walker method for M=2n of order =8,4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Modified Yule Walker Estimate for order=8,4 and M=2n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw2_8_ave(1:L/2)/PSD_myw2_8_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw2_8(k,1:L/2))/PSD_myw2_8(k,1),'k');
end
% Plot the PSD estimates of Modified Yule Walker method for M=2n of order =12,6
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->Modified Yule Walker Estimate for order=12,6 and M=2n');
XLABEL('x pi');
YLABEL('Modified Yule Walker Estimate');
hold;
plot(freq1(1:L/2),PSD_myw2_12_ave(1:L/2)/PSD_myw2_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),(PSD_myw2_12(k,1:L/2))/PSD_myw2_12(k,1),'k');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55

% Plot the PSD estimates of LS(ARMA) method of order=4,2
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=4,2');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_4_ave(1:L/2)/PSD_lsarma_4_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_4(k,1:L/2)/PSD_lsarma_4(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of order=8,4
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=8,4');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_8_ave(1:L/2)/PSD_lsarma_8_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_8(k,1:L/2)/PSD_lsarma_8(k,1),'k');
end
% Plot the PSD estimates of LS(ARMA) method of order=12,6
figure;
plot(freq1(1:L/2),H(1:L/2)/H(1),'r','LineWidth',2.5);
TITLE('Exercise 3-16 PART B -->LS(ARMA) Estimate of order=12,6');
XLABEL('x pi');
YLABEL('LS(ARMA) Estimate');
hold;
plot(freq1(1:L/2),PSD_lsarma_12_ave(1:L/2)/PSD_lsarma_12_ave(1),'b','LineWidth',2.5);
for k=1:10
    plot(freq1(1:L/2),PSD_lsarma_12(k,1:L/2)/PSD_lsarma_12(k,1),'k');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% %%POLE-ZERO PLOTS
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% figure;
% zplane(b,a);
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the original filter');
% 
% figure;
% zplane(1,a_yw_4(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the YW method n=4');
% 
% figure;
% zplane(1,a_yw_8(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the YW method n=8');
% 
% figure;
% zplane(1,a_yw_12(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the YW method n=12');
% 
% figure;
% zplane(1,a_yw_16(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the YW method n=16');
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
% 
% 
% figure;
% zplane(1,a_lsar_4(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(AR) method n=4');
% 
% figure;
% zplane(1,a_lsar_8(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(AR) method n=8');
% 
% figure;
% zplane(1,a_lsar_12(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(AR) method n=12');
% 
% figure;
% zplane(1,a_lsar_16(1:5,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(AR) method n=16');
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% figure;
% zplane(b_lsarma_4(:,5)',a_lsarma_4(:,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(ARMA) method n=4 m=2');
% 
% figure;
% zplane(b_lsarma_8(:,5)',a_lsarma_8(:,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(ARMA) method n=8 m=4');
% 
% figure;
% zplane(b_lsarma_12(:,5)',a_lsarma_12(:,5)');
% TITLE('Exercise 3-16 PART B -->Pole-Zero Plot for the LS(ARMA) method n=12 m=6');
% 
% %%Pole-Zero Calculation for the Modified Yule Walker Method by Spectral Factorization
% 
