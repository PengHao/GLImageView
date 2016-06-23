//
//  AirLinearRegression.h
//  AirCpp
//
//  Created by Penghao on 14-1-16.
//  Copyright (c) 2014年 PengHao.

//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#ifndef __AirCpp__AirLinearRegression__
#define __AirCpp__AirLinearRegression__

#include <iostream>
#include <vector>
#include "../AirObject/AirObject.h"
#include "AirMath.h"
namespace AirCpp {
    namespace  AirMath{
        namespace LinearAlgebra{
            typedef enum {
                SSReg = 0,  //回归平方和
                SSRes = 1,  //剩余平方和
                REGVar = 2, //回归平方差
                RESVar = 3, //剩余平方差
                SQUARE_INDEX_Count,
            }SQUARE_INDEX;
            
            typedef double SQUARE_POOR;
            
            template <class MDeterminant>
            class AirLinearRegression : public MDeterminant{
            private:
                unsigned long sample_count;
                AirMatrix<MDeterminant> *p_mat;
                AirPoint<MDeterminant> *p_Ys;
                AirPoint<MDeterminant> *p_result;
                SQUARE_POOR poor[4];
            public:
                AirLinearRegression():sample_count(0){
                }
                
                ~AirLinearRegression(){
                    release(p_mat);
                    release(p_Ys);
                    release(p_result);
                }
                
                void init(){
                    MDeterminant::init();
                    p_mat = new AirMatrix<MDeterminant>();
                    p_Ys = new AirPoint<MDeterminant>();
                    p_result = new AirPoint<MDeterminant>();
                }
                
                //add 以后 来求得它的线性矩阵
                //注意： 如果有常数项，我们则假设它是永远都是 x0=1
                void add_point(const AirPoint<MDeterminant> &point){
                    sample_count+=1;
                    (*p_mat)[0][0] = MDeterminant::determinant_num;
                    (*p_Ys)[0] += point[MDeterminant::determinant_num-1];
                    for (int i = 1; i < MDeterminant::determinant_num; ++i) {
                        (*p_Ys)[i]+=(point[i -1]*point[MDeterminant::determinant_num-1]);
                        (*p_mat)[0][i] += MDeterminant::get_X(point[i-1]);
                        (*p_mat)[i][0] = (*p_mat)[0][i];
                        (*p_mat)[i][i] += powf(MDeterminant::get_X(point[i-1]), 2);
                        for (int j = i+1; j < MDeterminant::determinant_num; j++) {
                            (*p_mat)[i][j] += point[i-1]*point[j-1];
                            (*p_mat)[j][i] = (*p_mat)[i][j];
                        }
                    }
                }
                
                //求线性矩阵的逆来求解方程组
                void linear_equations(double &average_y, AirPoint<MDeterminant> *point){
                    average_y = (*p_Ys)[0]/MDeterminant::determinant_num;
                    AirMatrix<MDeterminant> *rs = (*p_mat)^(-1);
                    (*rs).desc();
                    p_result = (*rs)*(*p_Ys);
                    point = p_result;
                }
                
                void analyze_square_poor(AirPoint<MDeterminant> &value){
                    if (poor == NULL) {
                        return;
                    }
                    double a = (*p_result)[0];
                    double b = (*p_Ys)[0]/sample_count;
                    
                    for (int j = 1; j < MDeterminant::determinant_num; ++j) {
                        a+=value[j-1]*(*p_result)[j];
                    }
                    poor[SSReg] += ((a - b) * (a - b));
                    poor[SSRes] += (value[MDeterminant::determinant_num-1] - a) * (value[MDeterminant::determinant_num-1] - a);
                }
                
                SQUARE_POOR *get_square_poor(){
                    poor[REGVar] = poor[SSReg] / sample_count;
                    if (sample_count - MDeterminant::determinant_num > 0.0)
                        poor[RESVar] = poor[SSRes] / (sample_count - MDeterminant::determinant_num); // 剩余方差
                    else
                        poor[RESVar] = 0.0;
                    
                    return poor;
                }
            };
        }
    }
}
#endif /* defined(__AirCpp__AirLinearRegression__) */
