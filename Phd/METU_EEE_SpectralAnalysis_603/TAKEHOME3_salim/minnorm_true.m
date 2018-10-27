function w=minnorm_true(r,n,m)
%
% The Root Min-Norm frequency estimator.
%
%  w=minnorm(y,n,m);
%
%      r  ->  the true ACS
%      n  ->  the model order
%      m  ->  the order of the covariance matrix in (4.5.14)
%      w  <-  the frequency estimates
%

% compute the true covariance matrix

R=toeplitz(r(1:m));

% to use the forward-backward approach, uncomment the next line
% R=(R+fliplr(eye(m))*R.'*fliplr(eye(m)))/2;

% get the eigendecomposition of R; use svd because it sorts eigenvalues
[U,D,V]=svd(R);
S=U(:,1:n);
alpha = S(1,:)';
Sbar = S(2:m,:);

if norm(alpha) ~=1, 
   g = - Sbar * alpha / (1-alpha'*alpha);
else,
   error('The min-norm solution does not exist');
end

% find the n roots of the a polynomial that are nearest the unit circle,
ra= conj(roots([1;g]));

% pick the n roots that are closest to the unit circle
[dumm,I]=sort(abs(abs(ra)-1));
w=angle(ra(I(1:n)));
