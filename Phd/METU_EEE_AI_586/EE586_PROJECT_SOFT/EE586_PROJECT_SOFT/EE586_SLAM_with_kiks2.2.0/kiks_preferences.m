function kiks_preferences
global KIKS_SIM_LIGHT_FEXP KIKS_SIM_PROX_NOISE KIKS_K213_NOISE KIKS_SIM_PROX_EMAX KIKS_SIM_PROX_EMIN KIKS_SIM_PROX_EEXP KIKS_ARENA_DEFAULT_COLOR KIKS_MOVIENAME KIKS_MOVIE_QUALITY KIKS_MOVIE_COMPRESSION KIKS_LOG_HISTORY KIKS_SIM_PROX_DIST KIKS_MMPERPIXEL KIKS_K213_2DMODE KIKS_SIM_PROX_STEP KIKS_K213_STEP KIKS_K213_NONORMALIZE KIKS_SETTINGS_DIR KIKS_ROUNDOBJECT_RADIUS KIKS_COLOR_CYLINDER KIKS_OBJECT_BALL_RADIUS KIKS_COLOR_BALL KIKS_COLOR_ROBOT KIKS_TRACE_MAX

% Object properties 
% Note that colors only affect the reading of the linear vision module & sensors, 
% not the KiKS visualization.
KIKS_COLOR_CYLINDER=70;     % cylinder grayscale color (255=white, 0=black)
KIKS_COLOR_BALL=25;         % ball grayscale color (255=white, 0=black)
KIKS_COLOR_ROBOT=120;       % robot grayscale color (255=white, 0=black)
% set to -X for a black/white stripe pattern with X black stripes

% Distance between sample points for proximity sensors
% Note: this number should be a divisor of 50
KIKS_SIM_PROX_STEP=5; % mm
% Proximity sensor error settings
KIKS_SIM_PROX_EMAX = 0.25;  % Max relative error caused by noise when sensor reading is 1
KIKS_SIM_PROX_EMIN = 0.10;  % Max relative error caused by noise when sensor reading is 1000
KIKS_SIM_PROX_EEXP = 3;     % The larger Eexp, the less frequent large errors are. 
                            % KIKS_SIM_PROX_EEXP=1   ==> Errors are evenly distributed across the error range,
                            % KIKS_SIM_PROX_EEXP=Inf ==> No errors,
                            % KIKS_SIM_PROX_EEXP>1   ==> Large errors are less common than small errors,
                            % KIKS_SIM_PROX_EEXP<1   ==> Large errors are more common than small errors.
% Amount of background noise for proximity sensors
KIKS_SIM_PROX_NOISE=1;    % percent, 100% = proximity sensors are completely random

% Ambient light sensor settings
KIKS_SIM_LIGHT_FEXP=5;      % The higher you set this value, the larger field-of-view light sensors have.

% Distance between sample points for k213 turret simulation
KIKS_K213_STEP=10;          % mm
% Amount of background noise for k213 camera
KIKS_K213_NOISE=10;         % percent, 100% = camera image is completely random

% Uncomment to shut off normalization of k213 image (fixed shutter speed modification)
%KIKS_K213_NONORMALIZE=1;

% Resolution of the internal map in millimeters per pixel. Default = 2^1.
% Set to higher value for faster, but less accurate, collision detection.
% Set to lower for slower, more accurate collision detection.
% For best results, set to 2^n where n is no higher than 3.
KIKS_MMPERPIXEL=2^1;

% Default wall color (1-255)
KIKS_ARENA_DEFAULT_COLOR=255;

% Movie settings. Uncomment KIKS_MOVIENAME to have KiKS record movies of
% your behaviors. Note that movie creation will slow down the simulation
% significantly.
% For more information about creating movies in Matlab, see
% http://www.mathworks.com/access/helpdesk/help/techdoc/ref/avifile.shtml
% Also search for the function avifile in kiks_kopen if you need to
% further customize movie creation settings.
%KIKS_MOVIENAME='demo';
KIKS_MOVIE_COMPRESSION='Indeo5';
KIKS_MOVIE_QUALITY=50;

% Maximum log history size (rows)
KIKS_LOG_HISTORY=1000;

% Maximum number of robot trace points
KIKS_TRACE_MAX=8^5;