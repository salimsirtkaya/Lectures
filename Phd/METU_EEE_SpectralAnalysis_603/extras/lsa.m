function a=lsa(y,w)
%
% lsa.m compute the complex amplitudes of 
% sinusoidal components given the frequencies by a least-squares
% solution to the data.
%
% Model:
%   y(n)=sum_{k=1}^p  a_k e^{jw(k)n} + e(n), n= 0,...,N-1 (*)
%
%
%   y   -> 1d data vector
%   w   -> sinusoidal frequencies
%   a   <- the complex amplitude amplitude
%

y=y(:);
w=w(:);

A=exp(sqrt(-1)* (0:length(y)-1)'*w');
a=A\y;

