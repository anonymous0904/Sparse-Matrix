#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {

    if(nrLines<=0 or nrCols<=0){
        throw invalid_argument("Arguments nrLines and nrCols must be positive");
    }
    nr_lines=nrLines;
    nr_cols=nrCols;
    vector=new TElem [5];
    vector_cols=new int [nrCols+1];
    vector_lines=new int [5];
    for(int i=0;i<nr_cols;i++){
        vector_cols[i]=-1;
    }
    vector_cols[nrCols]=0;
    capacity=5;
    nrElem=0;

}
void Matrix::print_vector_cols() {
    for(int i=0;i<=this->nr_cols;i++){
        cout<<i<<" : "<< this->vector_cols[i]<<' ';
    }
    cout<<endl;
}

void Matrix::print_vector_lines() {
    for(int i=0;i<nrElem;i++){
        cout<<i<<" : "<< this->vector_lines[i]<<' ';
    }
    cout<<endl;
}

void Matrix::print_vector_elem() {
    int i=0;
    while(i<nrElem){
        cout<<i<<" : "<< this->vector[i]<<' ';
        i++;
    }
    cout<<endl;
}

int Matrix::nrLines() const {
    return this->nr_lines;
}

int Matrix::nrColumns() const {
    return this->nr_cols;
}

void Matrix::grow_vector() {
    int* aux1=new int [capacity*2];
    int* aux2=new TElem [capacity*2];
    for(int i=0;i<nrElem;i++){
        aux1[i]=vector_lines[i];
        aux2[i]=vector[i];
    }
    delete [] vector_lines;
    delete [] vector;
    vector_lines=aux1;
    vector=aux2;
    capacity*=2;
}

void Matrix::shrink_vector() {
    int* aux1=new int[capacity/2];
    int* aux2=new TElem[capacity/2];
    for(int i=0;i<nrElem;i++){
        aux1[i]=vector_lines[i];
        aux2[i]=vector[i];
    }
    delete[]vector_lines;
    delete[]vector;
    vector_lines=aux1;
    vector=aux2;
    capacity/=2;
}

TElem Matrix::element(int i, int j) const {

    if (i >= nr_lines or i < 0) {
        throw invalid_argument("Invalid line index");
    }
    if (j < 0 or j >= nr_cols) {
        throw invalid_argument("Invalid column index");
    }
    if (vector_cols[j] < 0) {
        return NULL_TELEM;//no elem!=0 on column j
    }
    int idx = vector_cols[j], idx_col = j + 1;

    while (vector_cols[idx_col] < 0 and idx_col<nr_cols) {
        idx_col++;//searches the next column with an elem!=0 after column j
    }

    while (idx < vector_cols[idx_col]) {
        if (vector_lines[idx] == i) {
            return vector[idx];//searches in the vector the element on the col j before reaching the next col with elems!=0
        }
        idx++;
    }
    return NULL_TELEM;//no elem!=0 found
}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i >= nr_lines or i < 0) {
        throw invalid_argument("Invalid line index");
    }
    if (j < 0 or j >= nr_cols) {
        throw invalid_argument("Invalid column index");
    }

    int pos = -1;
    int idx=vector_cols[j];
    int idx_col = j+1;

    while(vector_cols[idx_col]<0){
        idx_col++;
    }

    if(vector_cols[j]>=0) {//if there are elements!=0 on the column
        while (idx < vector_cols[idx_col]and vector_lines[idx]<=i) {
            if (vector_lines[idx] == i) {
                pos = idx;//position in vector
                break;
            }
            idx++;
        }
    }

    if (e == NULL_TELEM) {
        if (pos==-1) {
            return NULL_TELEM;
        }
        TElem elem_modif = vector[pos];

        for (int k = pos; k < nrElem-1; k++) {
            vector[k] = vector[k+1];
            vector_lines[k] = vector_lines[k+1];
        }
        nrElem--;
        if(vector_cols[j+1]-vector_cols[j]==1){//only one elem!=0 on the column, now it's none
            vector_cols[j]=-1;
        }

        for(int k=j+1;k<nr_cols+1;k++){
            if(vector_cols[k]>=0){
                vector_cols[k]=vector_cols[k]-1;//decrementing because the values in the 2 vectors where shifted
            }
        }

        if (nrElem <= capacity/4) {
            shrink_vector();
        }
        return elem_modif;
    }
    else {
        if (pos != -1) {//if the elem!=0
            TElem elem_modif = vector[pos];
            vector[pos] = e;
            return elem_modif;
        }
        else {//change a value from zero to e-->add elements to the vectors
            if (nrElem == capacity) {
                grow_vector();
            }
            nrElem++;
            idx_col = j+1;
            while (vector_cols[idx_col] < 0) {
                idx_col++;
            }
            idx = vector_cols[j];

            if(idx<0){
                while(idx<vector_cols[idx_col]){
                    idx++;
                }
            }
            else {
                while (vector_lines[idx] < i and idx<vector_cols[idx_col]) {
                    idx++;
                }
            }
            for (int k = nrElem-1; k > idx; k--) {
                vector[k] = vector[k-1];
                vector_lines[k] = vector_lines[k-1];
            }
            vector[idx] = e;
            vector_lines[idx] = i;

            if(vector_cols[j]<0){
                vector_cols[j]=idx;
            }
            for (int k = j+1; k <= nr_cols; k++) {
                if(vector_cols[k]>=0) {
                    vector_cols[k]++;
                }
            }
            vector_cols[nr_cols] = nrElem;
            return NULL_TELEM;
        }
    }
}

Matrix::~Matrix() {
    delete [] vector_cols;
    delete [] vector_lines;
    delete [] vector;
}


