/*
# Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
# SPDX-License-Identifier: X11
*/

#include "cholesky_kernel.hpp"


extern "C" void cholesky_kernel(int diagSize, double* matrixA) {

   dataType dataA[MAXN][MAXN];

   for(int i = 0; i < diagSize; i++){
      for (int j = 0; j < diagSize; j++) {
      dataA[i][j] = matrixA[i*diagSize + j];
      }
   }

   double tmp1=sqrt(dataA[0][0]);

   dataA[0][0] = tmp1;
   Loop_first_col:
   for (int i = 1; i < diagSize; i++){
      dataA[i][0] = dataA[i][0]/tmp1;
   }

   Loop_col:
   for (int j = 1; j < diagSize; ++j){
      dataType tmp = 0;

      Loop_diag:
      for(int k = 0; k < j; k++){
         tmp += dataA[j][k]*dataA[j][k];
      }

      dataA[j][j] = sqrt(dataA[j][j] - tmp);

      if (j < diagSize - 1){
      Loop_row:
      for(int i = j+1; i < diagSize; ++i){
         dataType tmp2=0;
         Loop_vec_mul:
         for(int k = 0; k < j; k++){
            tmp2 += dataA[i][k]*dataA[j][k];
         }
         dataA[i][j] = (dataA[i][j] - tmp2)/dataA[j][j];
      }
      }
   }

   for (int i = 0; i < diagSize; i++) {
      for (int j = 0; j < diagSize; j++) {
         matrixA[i * diagSize + j] = dataA[i][j];
      }
   }
}