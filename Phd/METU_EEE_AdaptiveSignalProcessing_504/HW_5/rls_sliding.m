%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5,               %
% Sliding Window RLS Implementation   %
% Salim Sirtkaya, 112434-6            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [W1,alpha] = rls_sliding(x,d,f_order,L,lambda)

delta = 0.001; % for initialization of the P matrix
N = length(x);

P = eye(f_order)/delta;

W(1,1:2) =0;% zeros(1,f_order);
W1(1:L+1,1:2)=0;
alpha(1)=0;
alpha(2)=0;

for k=3:N-L-1
    for t=k:k+L-1
        X = [ x(t-1) ; x(t-2) ];
        z = P * X ;
        g = z / (lambda+ X' * z);
        alpha(t) = d(t) -  W(t-2,:) * X;
        W(t-1,:) = W(t-2,:)+alpha(t)*g.';
        P = (P-g*z.') / lambda;
    end
    
    W1(k+L-1,:)=W(t-1,:);
    W(:,:)=0;
    P = eye(f_order)/delta;
end;