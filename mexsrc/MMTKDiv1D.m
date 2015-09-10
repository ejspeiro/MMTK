% MMTKDiv1D Create a mimetic one-dimensional divergence operator.
%
%   div = MMTKDiv1D(k, w, e, n, tau) Returns the divergence order k as a n + 2
%                                    by n + 1 matrix, in the interval (w,e) with
%                                    discretized using n cells with the given
%                                    mimetic threshold tau (optional).
%
%   [s, m, q] = MMTKDiv1D(k, tau)    Returns the divergence order k as the
%                                    interior stencil s, mimetic coefficients m,
%                                    mimetic weights q and mimetic threshold tau
%                                    (optional).
%
% For more information, see
% <a href="http://www.csrc.sdsu.edu/mimetic-book/">
% Mimetic Discretization Methods</a>.
%
