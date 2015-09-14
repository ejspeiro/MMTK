% FUNCTION_NAME - Div1D
% Creation of different high-order mimetic divergence operators with the MMTK.
%
% Other m-files required: None.
% Subfunctions: The MMTK.
% MAT-files required: None.
%
% See also: MMTKDiv1D.
%
% Author: Eduardo Sanchez, Ph.D.
% Computational Science Research Center.
% 5500 Campanile Drive, San Diego State University.
% Email: esanchez at mail dot sdsu dot edu
% Website: http://www-rohan.sdsu.edu/~sanche94/
% 2015-09-10 14:18:35

%------------- BEGIN CODE --------------

addpath('../mexsrc');

close all;
clear all;
clc;

west = 0.0;
east = 1.0;

kk = 2
[ss, mb, qq] = MMTKDiv1D(kk);
ss

num_cells = 3*kk - 1;
div = MMTKDiv1D(kk, west, east, num_cells);
div

kk = 4
[ss, mb, qq] = MMTKDiv1D(kk);
ss
mb
qq

num_cells = 3*kk - 1;
div = MMTKDiv1D(kk, west, east, num_cells);
div

%------------- END OF CODE --------------
