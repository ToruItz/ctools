#ifndef CTOOLS_MATRIX_H
#define CTOOLS_MATRIX_H

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <ostream>

template <typename Type>
class Matrix {

    Type** matrix;

    unsigned long long sizeX;

    unsigned long long sizeY;


    void clear(){
        for (int i = 0; i < sizeY; ++i) {
            if(sizeX < 2) delete matrix[i];
            else delete [] matrix[i];
        }
        if(sizeY < 2) delete matrix;
        else delete [] matrix;
    }

    void realloc(int x, int y){
        Type** buffer = new Type*[y];
        for (int i = 0; i < y; ++i) {
            buffer[i] = new Type[x];
            for (int j = 0; j < x; ++j)
                if(j >= sizeX || i >= sizeY)
                    buffer[i][j] = 0;
                else
                    buffer[i][j] = matrix[i][j];
        }
        clear();
        matrix = buffer;
        sizeX = x;
        sizeY = y;
    }

public:

    Matrix() : sizeX(1), sizeY(1){
        this->matrix = new Type*[this->sizeY];
        for (int i = 0; i < this->sizeY; ++i) {
            this->matrix[i] = new Type[this->sizeX];
            for (int j = 0; j < this->sizeX; ++j) {
                this->matrix[i][j] = 0;
            }
        }
    }

    Matrix(Type **matrix, unsigned long long int sizeX, unsigned long long int sizeY) : sizeX(sizeX),     sizeY(sizeY) {
        for (int i = 0; i < sizeY; ++i)
            for (int j = 0; j < sizeX; ++j)
                this->matrix[i][j] = matrix[i][j];
    }

    virtual ~Matrix() {
        for (int i = 0; i < sizeY; ++i) {
            if(sizeX < 2) delete matrix[i];
            else delete [] matrix[i];
        }
        if(sizeY < 2) delete matrix;
        else delete [] matrix;
    }

    Matrix operator = (const Matrix& matrix){
        clear();

        this->sizeX = matrix.sizeX;
        this->sizeY = matrix.sizeY;

        this->matrix = new Type*[this->sizeY];
        for (int i = 0; i < this->sizeY; ++i) {
            this->matrix[i] = new Type[this->sizeX];
            for (int j = 0; j < this->sizeX; ++j) {
                this->matrix[i][j] = matrix.matrix[i][j];
            }
        }
    }

    Type get(int i, int j){
        return matrix[i][j];
    }

    Type* getl(int i){
        Type* line = new Type[sizeX];
        for (int j = 0; j < sizeX; ++j) {
            line[j] = matrix[i][j];
        }
        return line;
    }

    Type* getc(int i){
        Type* col = new Type[sizeY];
        for (int j = 0; j < sizeY; ++j) {
            col[i] = matrix[j][i];
        }
        return col;
    }

    void set(Type value, int i, int j){
        matrix[i][j] = value;
    }

    void setl(const Type* line, int i){
        for (int j = 0; j < sizeX; ++j) {
            matrix[i][j] = line[j];
        }
    }

    void setc(const Type* col, int i){
        for (int j = 0; j < sizeX; ++j) {
            matrix[j][i] = col[j];
        }
    }

    void add(Type value, int i, int j){
        if(i > sizeY || j > sizeX) realloc(j + 1, i + 1);
        matrix[i][j] = value;
    }

    void addl(const Type* line){
        realloc(sizeX, sizeY + 1);
        for (int i = 0; i < sizeX; ++i) {
            matrix[sizeY - 1][i] = line[i];
        }
    }

    void addc(const Type* col){
        realloc(sizeX + 1, sizeY);
        for (int i = 0; i < sizeY; ++i) {
            matrix[i][sizeX - 1] = col[i];
        }
    }

    Type* operator [] (int i){return this->matrix[i];}

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        for (int i = 0; i < matrix.sizeY; ++i) {
            os << "{";
            for (int j = 0; j < matrix.sizeY; ++j) {
                os << " " << matrix.matrix[i][j];
            }
            os << " }\n";
        }
        return os;
    }

};

#endif //MATRIX_MATRIX_H

#endif //CTOOLS_MATRIX_H
