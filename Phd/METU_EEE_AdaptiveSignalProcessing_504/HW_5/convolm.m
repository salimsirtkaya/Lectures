function H = convolm(x,num_zeros,pad)
%convolm                        [jMc 2/89]
% creates a convolution matrix, optionally padded with zeros
%    convolm(X,P) creates a convolution matrix from 
%        the data vector x(1:N). The matrix will have p columns.
%    convolm(X,P,'<') will pad with 'p-1' zeros at the beginning of x
%    convolm(X,P,'>') will pad with 'p-1' zeros at the end of x 
%    convolm(X,P,'<>') will pad both end of the signal x with p-1 zeros
%
% RECALL : H = [ h(i,j) ] where h(i,j) = x(p+i-j)
% see HANKEL, CIRCULANT, CONVMTX

N=length(x); 
x=x(:); 

if nargin==3
    z = zeros(num_zeros-1,1);
    if pad == '<>'
           N= N + 2*(num_zeros-1); t=[z; x; z];
       elseif pad == '<'
           N= N + num_zeros-1;   t=[z; x]; 
       elseif pad == '>'
           N= N + num_zeros-1;   t=[x; z];
       end;
else
   t=x;
end;
   
H= zeros(N-num_zeros+1,num_zeros);
for i=1:num_zeros
    H(:,i) = t(num_zeros-i+1:N-i+1);
end;

       
           
           
           