//
//  AirMath.h
//  AirCpp
//
//  Created by Penghao on 14-1-13.
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

#ifndef __AirCpp__AirMath__
#define __AirCpp__AirMath__
#define AirMathAPI
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <cassert>
#include <cstdarg>
namespace AirCpp{
    namespace  AirMath{
        namespace LinearAlgebra{
            class AirDeterminant {
            public:
                unsigned int determinant_num;
                
                AirDeterminant(){
                    determinant_num = 1;
                }
                
                virtual ~AirDeterminant(){
                    
                };
                
                double get_X(double x){
                    return x;
                }
                
            };
            
            class AirDeterminant2 :public AirDeterminant{
            public:
                AirDeterminant2(){
                    determinant_num = 2;
                }
            };
            
            class AirDeterminant3 :public AirDeterminant{
            public:
                AirDeterminant3(){
                    determinant_num = 3;
                }
            };
            
            class AirDeterminant4 :public AirDeterminant{
            public:
                AirDeterminant4(){
                    determinant_num = 4;
                }
            };
            
            template <class Determinant>
            class AirMatrix;
            
            template <class Determinant>
            class AirPoint : public Determinant{
            public:
                double *elements;
                
                ~AirPoint(){
                    free(elements);
                }
                AirPoint(){
                    elements = (double *)calloc(Determinant::determinant_num, sizeof(double));
                }
                
                AirPoint(const AirPoint &point){
                    elements = (double *)calloc(Determinant::determinant_num, sizeof(double));
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] = point[i];
                    }
                }
                
                AirPoint( AirPoint &point){
                    elements = (double *)calloc(Determinant::determinant_num, sizeof(double));
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] = point[i];
                    }
                }
                
                AirPoint(double element, ...){
                    elements = (double *)calloc(Determinant::determinant_num, sizeof(double));
                    elements[0] = element;
                    va_list list;
                    double value;
                    va_start(list, element);
                    for(int i=1;i<Determinant::determinant_num;i++){
                        value = va_arg(list, double);
                        elements[i] = value;
                    }
                    va_end(list);
                }
                
                double& operator [](const int &i)
                {
                    return elements[i];
                }
                const double&  operator [](const int &i) const
                {
                    return elements[i];
                }
                
                AirPoint* operator *(const double &f){
                    AirPoint *result = new AirPoint();
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*result).elements[i]=elements[i] * f;
                    }
                    return result;
                }
                
                AirPoint* operator +(const AirPoint &p){
                    AirPoint *result = new AirPoint();
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*result)[i] = (*this)[i] + p[i];
                    }
                    return result;
                }
                
                AirPoint* operator -(const AirPoint &p){
                    AirPoint *result = new AirPoint();
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*result)[i]= (*this)[i] - p[i];
                    }
                    return result;
                }
                
                AirPoint*  operator *(const AirMatrix<Determinant> &mat){
                    AirPoint *rs = new AirPoint();
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        for (int j = 0; j < Determinant::determinant_num; ++j) {
                            (*rs)[i] += elements[j]*mat[j][i];
                        }
                    }
                    return rs;
                }

                double operator *(const AirPoint &p){
                    double result = 0;
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        result +=p[i]*elements[i];
                    }
                    return result;
                }
                
                void operator ()(double element, ...){
                    elements[0] = element;
                    va_list list;
                    double value;
                    va_start(list, element);
                    for(int i=1;i<Determinant::determinant_num;i++){
                        value = va_arg(list, double);
                        elements[i] = value;
                    }
                    va_end(list);
                }
                
                void operator *=(const double &f){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] *= f;
                    }
                }
                
                
                void operator +=(const AirPoint &p){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] += p[i];
                    }
                }
                
                void operator -=(AirPoint &p){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] -= p[i];
                    }
                }
                
                void operator -=(const AirPoint &p){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] -= p[i];
                    }
                }
                
                AirPoint & operator =(const AirPoint &p){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] = p[i];
                    }
                    return *this;
                }
                
                AirPoint & operator =(AirPoint &p){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        elements[i] = p[i];
                    }
                    return *this;
                }
                
                bool operator == (const AirPoint &p){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        if(elements[i] != p[i]){
                            return false;
                        }
                    }
                    return true;
                }
                
                bool isNULL(){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        if(fabs(elements[i]) >= 0.001){
                            return false;
                        }
                    }
                    return true;
                }
                
                
                void desc() const{
                    printf("( ");
                    for (int j = 0; j < Determinant::determinant_num; ++j) {
                        printf("%.2f ", elements[j]);
                    }
                    printf(")\n");
                }
            };
            
            template <class Determinant>
            class test : public AirPoint<Determinant>{
                
            };
            
            template <class Determinant>
            class AirMatrix : public Determinant{
            public:
                AirPoint<Determinant> *rows;
                AirMatrix(){
                    rows = new AirPoint<Determinant>[Determinant::determinant_num];
                }
                
                AirMatrix(AirMatrix &mat){
                    rows = new AirPoint<Determinant>[Determinant::determinant_num];
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*this)[i] = mat[i];
                    }
                }
                
                AirMatrix(double element, ...){
                    rows = new AirPoint<Determinant>[Determinant::determinant_num];
                    va_list list;
                    double value;
                    va_start(list, element);
                    for(int i=0;i<Determinant::determinant_num;++i){
                        for (int j = 0 ; j<Determinant::determinant_num;++j) {
                            if (i == j&& j == 0) {
                                value = element;
                            }else{
                                value = va_arg(list, double);
                            }
                            (*rows[i])[j] = value;
                        }
                    }
                    va_end(list);
                }
                
                ~AirMatrix(){
                    delete [] rows;
                }
                
                
                
                AirPoint<Determinant>& operator [](int i)
                {
                    return rows[i];
                }
                
                const AirPoint<Determinant>& operator [](int i) const
                {
                    return rows[i];
                }
                
                
                AirMatrix & operator = (const AirMatrix &mat)
                {
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*this)[i] = mat[i];
                        
                    }
                    return *this;
                };
                
                AirMatrix & operator = (AirMatrix &mat)
                {
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*this)[i] = mat[i];
                    }
                    return *this;
                };
                
                
                bool operator == (AirMatrix &mat) const{
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        if ((*rows[i]) != mat[i]) {
                            return false;
                        }
                    }
                    return true;
                }
                
                bool isNULL(){
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        if (!(*rows[i]).isNULL()) {
                            return false;
                        }
                    }
                    return true;
                }
                
                AirPoint<Determinant> *operator *(const AirPoint<Determinant> &p){
                    AirPoint<Determinant> *rs = new AirPoint<Determinant>();
                    for (int m = 0; m < Determinant::determinant_num; ++m) {
                        (*rs)[m] = (*this)[m]*p;
                    }
                    return rs;
                }
                
                AirMatrix* operator *(const AirMatrix<Determinant> &mat){
                    AirMatrix *rs = new AirMatrix();
                    for (int m = 0; m < Determinant::determinant_num; ++m) {
                        (*rs)[m] = *((*this)[m]*mat);
                    }
                    return rs;
                }
                
                AirMatrix* operator ^ (int k)
                {
                    double tmp;
                    AirMatrix tmpMat = *this;
                    AirMatrix *rs = new AirMatrix();
                    int i, j, m, n;
                    if (k<0) {
                        for (i = 0; i > k; --i) {
                            for (j = 0; j < Determinant::determinant_num; ++j) {
                                (*rs)[j][j] = 1;
                            }
                            for (m = 0; m < Determinant::determinant_num; ++m) {
                                if (fabs(tmpMat[m][m])<=0.0001) {
                                    //对角线元素等于0，需要交换
                                    for (n = m+1; n < Determinant::determinant_num; ++n) {
                                        if (fabs(tmpMat[n][m])>0.0001) {
                                            AirPoint<Determinant> row = tmpMat[m];
                                            tmpMat[m] = tmpMat[n];
                                            tmpMat[n] = row;
                                        }
                                    }
                                }
                                if (fabs(tmpMat[m][m])<=0.0001) {
                                    return rs;
                                }else{
                                    for (n = 0; n < Determinant::determinant_num; ++n) {
                                        if (m == n) {
                                            (*rs)[n] *= 1.0/tmpMat[m][n];
                                            tmpMat[n] *= 1.0/tmpMat[m][n];
                                        }else{
                                            tmp = tmpMat[n][m] / tmpMat[m][m];
                                            ;
                                            (*rs)[n] -= *((*rs)[m]*tmp);
                                            tmpMat[n] -= *(tmpMat[m]*tmp);
                                        }
                                        if (fabs(tmpMat[n][n])<=0.0001) {
                                            return rs;
                                        }
                                    }
                                }
                            }
                        }
                    }else{
                        assert(k < 0);
                    }
                    return rs;
                };
                
                void desc() const{
                    printf("{\n");
                    for (int i = 0; i < Determinant::determinant_num; ++i) {
                        (*this)[i].desc();
                    }
                    printf("}\n");
                }
            };
            
            typedef AirPoint<AirDeterminant2> AirPoint2;
            typedef AirPoint<AirDeterminant3> AirPoint3;
            typedef AirPoint<AirDeterminant4> AirPoint4;
            
            typedef AirMatrix<AirDeterminant2> AirMatrix2X2;
            typedef AirMatrix<AirDeterminant3> AirMatrix3X3;
            typedef AirMatrix<AirDeterminant4> AirMatrix4X4;
            
        }
    }
}
#endif /* defined(__AirCpp__AirMath__) */