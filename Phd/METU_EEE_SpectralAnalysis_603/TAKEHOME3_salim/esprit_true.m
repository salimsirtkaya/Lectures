function w=esprit(r,n,m)
%
% The ESPRIT method for frequency estimation.
%
%  w=esprit(y,n,m);
%
%      r  ->  the true ACS
%      n  ->  the model order
%      m  ->  the order of the covariance matrix in (4.5.14)
%      w  <-  the frequency estimates
%


R=toeplitz(r(1:m));

% to use the forward-backward approach, uncomment the next line
% R=(R+fliplr(eye(m))*R.'*fliplr(eye(m)))/2;

% get the eigendecomposition of R; use svd because it sorts eigenvalues
[U,D,V]=svd(R);
S=U(:,1:n);

phi = S(1:m-1,:)\S(2:m,:);

w=-angle(eig(phi));
