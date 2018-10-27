function doa=root_music_doa(Y,n,d)
%
% The MUSIC method for direction of arrival estimation
%
% call doa=root_music_doa(Y,n,d)
%
%      Y    <- the ULA data
%      n    <- the number of sources
%      d    <- sensor spacing in wavelengths
%      doa  -> the vector of DOA estimates

% Copyright 1996 by R. Moses

[m,N]=size(Y);

% compute the sample covariance matrix
R=Y*Y'/N;

% do the eigendecomposition; use svd because it sorts eigenvalues
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

% compute the doas
doa=asin(w/d/pi/2)*180/pi;
