%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5, RLS Implementation   %
% Salim Sirtkaya, 112434-6                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [W,alpha] = rls(x,d,f_order,lambda)

delta = 0.001; % for initialization of the P matrix
N = length(x);

P = eye(f_order)/delta;

W(1,:) = zeros(1,f_order);
alpha(1)=0;
alpha(2)=0;

for k=3:N-f_order+1
    X = [ x(k-1) ; x(k-2) ];
    z = P * X ;
    g  = z / (lambda+ X' * z);
    alpha(k) = d(k) -  W(k-2,:) * X;
    W(k-1,:) = W(k-2,:)+alpha(k)*g.';
    P = (P-g*z.') / lambda;
end;