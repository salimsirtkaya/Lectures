%*********************************************
%*********************************************
% Data generator
%*********************************************
%*********************************************
function RY=Generate_data(a,b,no_sample,no_real)

% no_sample= number of data samples that will be generated
% no_real = number of realizations (data vectors) that will be generated
% alfa = the parameter that is used in defining the transfer function in Exercise 2.19
% a = Coefficients of the denumerator of H(q) (A(q))
% b = Coefficients of the numerator of H(q) (B(q))

NN=no_sample;

% generation of no_real realizations of y[n]

for K=1:no_real
    e=randn(1,NN);
    yy=filter(b,a,e);
    RY(K,1:NN)=yy;
end


