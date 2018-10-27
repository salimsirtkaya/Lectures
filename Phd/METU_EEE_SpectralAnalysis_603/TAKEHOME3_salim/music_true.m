function w=music_true(r,n,m)
%
% The Root MUSIC method for frequency estimation.
%
%  w=music(r,n,m);
%
%      y  ->  true ACS
%      n  ->  the model order
%      m  ->  the order of the covariance matrix in (4.5.14)
%      w  <-  the frequency estimates
%

% compute the true covariance matrix

R=toeplitz(r(1:m));

% get the eigendecomposition of R; use svd because it sorts eigenvalues
[U,D,V]=svd(R);
G=U(:,n+1:m);

GG = G*G';

% find the coefficients of the polynomial in (4.5.16)
 a = zeros(2*m-1,1);
  for j=-(m-1):(m-1)
    a(j+m) = sum( diag(GG,j) );
  end

% find the n roots of the a polynomial that are nearest and inside the unit circle,
ra=roots([a]);
rb=ra(abs(ra)<1);

% pick the n roots that are closest to the unit circle
[dumm,I]=sort(abs(abs(rb)-1));
w=angle(rb(I(1:n)));
