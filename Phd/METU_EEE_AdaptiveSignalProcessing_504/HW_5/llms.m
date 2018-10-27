function [A,E]= llms(x,d,alpha,nord,A_in)
%LMS                        [mhh3 3/92]
%-- Widrow-Hoff LMS adaptive filtering algorithm
% Adapted from lms.m written by j.mcclellan
%
%
% [A,E] = llms(x,d,alpha,nord,a0)
%       
%       x : input data to the adaptive filter
%       d : desired output vector
%   alpha : adaptive filtering update (step-size) parameter
%    nord : number of adaptive filter coefficients
%      a0 : (optional) initial guess for FIR filter coeffs
%           (row vector). If a0 is omitted, a0=0 is assumed
%     [A,E] = llms(x,d,alpha) uses A_in=0
%
%     The output matrix A contains filter coefficients
%         - The n'th row contains the filter coefficients at time n 
%         - The m'th column contains the m'th filter coeff vs. time
%         - The output vector E contains the error sequences vs. time
%
%

X=convolm(x,nord,'<');
[M,N] = size(X);

if nargin < 5
    A_in=zeros(1,N);  
end;

A_in = A_in(:).';

E(1) = d(1) - A_in*X(1,:).';
A(1,:) = A_in + alpha*E(1)*conj(X(1,:));

if M>1,
    for k=2:M,
        E(k) = d(k) - A(k-1,:)*X(k,:).';
        A(k,:) = A(k-1,:) + alpha*E(k)*conj(X(k,:));
    end;
end;