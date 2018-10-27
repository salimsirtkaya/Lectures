%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EE - 504 Homework #5, RLS Implementation   %
% Salim Sirtkaya, 112434-6                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [W] = rls(x,d,nord,f_order,lambda)

delta = 0.001; % for initialization of the P matrix
N = size(x);

P = eye(f_order)/delta;

W(1,:) = zeros(1,f_order);

for k=2:N-f_order+1
    X = [ x(k) ; x(k-1) ];
    z = P * X ;
    g  = z / (lambda+ X * z);
    alpha = d(k) - X.W(k-1,:).';
    W(k,:) = W(k-1,:)+alpha*g.';
    P = (P-g*z.') / lambda;
end;