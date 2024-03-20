#ifndef MATRIX1_MATRIX_H
#define MATRIX1_MATRIX_H

#endif //MATRIX1_MATRIX_H
#pragma once

typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
    int nr_lines;
    int nr_cols;
    TElem * vector;
    int* vector_cols;
    int* vector_lines;
    int capacity;
    int nrElem;

    //halves the capacity of a vector if the number of elements in it is less than
    // a quarter of its capacity
    void shrink_vector();

    //doubles the capacity of a vector if it is full
    void grow_vector();

public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;


    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);

    void print_vector_elem();
    void print_vector_lines();
    void print_vector_cols();

    // destructor
    ~Matrix();

};
