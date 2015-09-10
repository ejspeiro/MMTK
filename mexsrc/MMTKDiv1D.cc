/*!
\file MMTKDiv1D.cc

\brief MEX file for the Div1D class.

\author: Eduardo J. Sanchez (ejspeiro) - esanchez at mail dot sdsu dot edu
*/
/*
Copyright (C) 2015, Computational Science Research Center, San Diego State
University. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Modifications to source code should be reported to: esanchez@mail.sdsu.edu
and a copy of the modified files should be reported once modifications are
completed. Documentation related to said modifications should be included.

2. Redistributions of source code must be done through direct
downloads from the project's GitHub page: http://www.csrc.sdsu.edu/mtk

3. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

4. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

5. Usage of the binary form on proprietary applications shall require explicit
prior written permission from the the copyright holders.

6. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

The copyright holders provide no reassurances that the source code provided does
not infringe any patent, copyright, or any other intellectual property rights of
third parties. The copyright holders disclaim any liability to any recipient for
claims brought against recipient by any third party for infringement of that
parties intellectual property rights.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#if __cplusplus == 201103L

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

#include "mex.h"

#include "mtk.h"

using namespace std;

static int MTKDiv1D(int order_accuracy,
                    mtk::Real tau,
                    mtk::Real *outS,
                    mtk::Real *outM,
                    mtk::Real *outQ);

static int MTKDiv1DReturnAsDenseMatrix(int order_accuracy,
                                       mtk::Real west_bndy_x,
                                       mtk::Real east_bndy_x,
                                       int num_cells,
                                       mtk::Real tau,
                                       mtk::Real *outMatrix);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

  int order_accuracy;  // kk inside MTK.
  int num_cells;       // scaler to matrix size.

  mtk::Real *outMatrix;  // Where to place our output.
  mtk::Real *outS;       // output Stencil.
  mtk::Real *outQ;       // output Weights.
  mtk::Real *outM;       // output Mimetic Coefficients.

  mtk::Real west_bndy_x; // Start of the Interval.
  mtk::Real east_bndy_x; // End of the Interval.
  mtk::Real tau;         // Mimetic tolerance (optional).

//   if (nrhs >= 1 && nrhs <= 2) {
//
//     order_accuracy = mxGetScalar(prhs[0]);
//
//     if (nrhs == 1 && order_accuracy >= 8) {
//       std::cout << "Default mimetic threshold set as 1e-6."<<std::endl;
//       tau = 1e-6;
//     }
//     if (nrhs == 2 && order_accuracy < 8) {
//       std::cout << "Order of accuracy does not need mimetic threshold. If provided it will be ignored."<<std::endl;
//       tau = mxGetScalar(prhs[1]);
//     }
//     if(nrhs == 2 && order_accuracy >= 8) {
//       tau = mxGetScalar(prhs[1]);
//     }
//     if (nlhs != 3) {
//       mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","3 outputs are needed: S, M, Q.");
//     }
//     if (nlhs == 3) {
//
//       // Stencil
//       plhs[0] = mxCreateDoubleMatrix((mwSize) 1,(mwSize) order_accuracy,mxREAL);
//
//       //Mimetic coefficients Rows
//       plhs[1] = mxCreateDoubleMatrix( (mwSize) (order_accuracy/2-1), (mwSize) (3*order_accuracy/ 2), mxREAL);
//
//       // Weights
//       plhs[2] = mxCreateDoubleMatrix((mwSize) 1,(mwSize) order_accuracy, mxREAL);
//
//       outS = mxGetPr(plhs[0]);
//       outM =mxGetPr(plhs[1]);
//       outQ = mxGetPr(plhs[2]);
//
//       mtk_1d_div(order_accuracy, tau, outS ,outM,outQ);
//     }
//   } else {
//
//     if (nrhs > 5) {
//       mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "At most 5 inputs are permited: (order, a, b, cells, tau).");
//     }
//
//     if (nrhs < 4) {
//       mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "At leats 4 inputs are required: (order, a, b, cells).");
//     }
//
//     if (nlhs != 1) {
//       mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output is needed.");
//     }
//
//     order_accuracy = mxGetScalar(prhs[0]);
//
//     west_bndy_x = mxGetScalar(prhs[1]);
//
//     east_bndy_x = mxGetScalar(prhs[2]);
//
//     num_cells = mxGetScalar(prhs[3]);
//
//     if (num_cells < 3*order_accuracy - 1) {
//       mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs", "Number of cells too small for required order.");
//     }
//
//     if (order_accuracy >= 8) {
//       std::cout << "Order of accuracy too high. Mimetic threshold will be applied." << std::endl;
//     }
//
//     if (nrhs == 5 && order_accuracy >= 8) {
//       tau = mxGetScalar(prhs[4]);
//     }
//
//     if(nrhs == 5 && order_accuracy <8 ) {
//       std::cout << "Order of accuracy does not need mimetic threshold. If provided it will be ignored."<<std::endl;
//       tau = mxGetScalar(prhs[4]);
//     }
//
//     if(nrhs == 4 && order_accuracy >= 8) {
//       //Default threshold, used only if order >=8
//       std::cout << "Default mimetic threshold set as 1e-6."<<std::endl;
//       tau = 1.0e-6;
//     }
//
//     plhs[0] = mxCreateDoubleMatrix((mwSize) (num_cells + 2),
//                                    (mwSize) (num_cells + 1),
//                                    mxREAL);
//
//     outMatrix =  mxGetPr(plhs[0]);
//
//     MTKDiv1DReturnAsDenseMatrix(order_accuracy, west_bndy_x, east_bndy_x, num_cells, tau, outMatrix);
//   }
}

static int MTKDiv1D(int order_accuracy,
                    mtk::Real tau,
                    mtk::Real *outS,
                    mtk::Real *outM,
                    mtk::Real *outQ) {

//   mtk::MTK_1DDiv *div = new  mtk::MTK_1DDiv(order_accuracy,tau);
//
//   int Number_of_Extra_Rows=order_accuracy/2-1;
//
//   div = div->Construct1DDiv();
//
//   if (div == nullptr) {
//     return EXIT_FAILURE;
//   }
//
//   mtk::Real *ww;
//   mtk::Real *ss;
//   mtk::MTK_DenseMatrix *ee;
//   mtk::MTK_DenseMatrix *eeT;
//
//   ss = div->ReturnStencil();
//
//   ww = div->ReturnWeights();
//
//   for(auto ii = 0; ii < order_accuracy; ii++) {
//     outQ[ii]= ww[ii];
//     outS[ii]= ss[ii];
//   }
//
//   ee = div->ReturnMimeticCoefficients();
//   eeT= new mtk::MTK_DenseMatrix(3*order_accuracy/2,Number_of_Extra_Rows);
//   eeT->Transpose(*ee,*eeT);
//
//   for(auto ii=0;ii<3*order_accuracy/2*Number_of_Extra_Rows;ii++) {
//   out M[ii]=eeT->DenseMatrix_To_Real(*eeT)[ii];
//   }
//
//   delete [] ww;
//   delete [] ss;
//   delete [] ee;
}

static int MTKDiv1DReturnAsDenseMatrix(int order_accuracy,
                                       mtk::Real west_bndy_x,
                                       mtk::Real east_bndy_x,
                                       int num_cells,
                                       mtk::Real tau,
                                       mtk::Real *outMatrix) {

//   int nn = num_cells + 2;
//   int mm = num_cells + 1;
//
//   mtk::MTK_DenseMatrix *dd;
//   mtk::MTK_DenseMatrix *ddT;
//
//   mtk::MTK_1DDiv *div = new  mtk::MTK_1DDiv(order_accuracy,tau);
//
//   div = div->Construct1DDiv();
//
//   ddT = new mtk::MTK_DenseMatrix(mm,nn);
//
//   if (div == nullptr) {
//     std::cout << "Problem constructing the matrix... " << std::endl;
//     return EXIT_FAILURE;
//   }
//
//   dd = div->ReturnAsMatrix(num_cells, west_bndy_x, east_bndy_x);
//
//   dd->Transpose(*dd,*ddT);
//
//   for(auto ii = 0; ii < mm*nn; ii++) {
//     outMatrix[ii]=ddT->DenseMatrix_To_Real(*ddT)[ii];
//   }
//
//   delete [] ddT;
}

#endif
