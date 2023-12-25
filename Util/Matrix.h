#ifndef CHESS_MATRIX_H
#define CHESS_MATRIX_H

#include <iostream>

template <typename T>
class MatrixIterator;

template <typename T>
class Matrix {

protected:
    int rows, cols;
    T **data;

public:

    Matrix(int rows, int cols) : rows(rows), cols(cols)
    {
        data = new T* [rows];
        for (int i = 0; i < rows; i++)
            data[i] = new T[cols];
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    void free_memory()
    {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    T& at(int i, int j) const
    {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw std::out_of_range("Index out of bounds");
        return data[i][j];
    }

    int get_rows() const
    {
        return rows;
    }

    int get_cols() const
    {
        return cols;
    }

    void print() const
    {
        std::cout << "\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                std::cout << data[i][j] << "\t";
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    void add_row()
    {
        T** new_data = new T* [rows + 1];
        for (int i = 0; i < rows; i++)
            new_data[i] = data[i];

        new_data[rows] = new T[cols];
        std::swap(data, new_data);
        rows++;
    }

    void add_column()
    {
        T** new_data = new T* [rows];
        for (int i = 0; i < rows; i++)
        {
            new_data[i] = new T[cols + 1];
            for (int j = 0; j < cols; j++)
                new_data[i][j] = data[i][j];
            delete data[i];
        }

        std::swap(data, new_data);
        cols++;
    }

    void delete_row(int row_to_delete)
    {
        if (row_to_delete >= rows or row_to_delete < 0)
            throw std::out_of_range("Index out of bounds");

        T** new_data = new T* [rows - 1];
        for (int i = 0, k = 0; i < rows; i++)
        {
            if (i != row_to_delete)
                new_data[k++] = data[i];
            else
                delete[] data[i];
        }

        std::swap(data, new_data);
        rows--;
    }

    void delete_column(int col_to_delete)
    {
        if (col_to_delete >= cols or col_to_delete < 0)
            throw std::out_of_range("Index out of bounds");

        T** new_data = new T* [rows];
        for (int i = 0; i < rows; i++)
        {
            new_data[i] = new T[cols - 1];
            for (int j = 0, k = 0; j < cols; j++)
            {
                if (j != col_to_delete)
                    new_data[i][k++] = data[i][j];
            }

            delete[] data[i];
        }

        std::swap(data, new_data);
        cols--;
    }

    int find_element(T elem)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (data[i][j] == elem)
                    return (i * rows + j);
            }
        }

        throw std::out_of_range("Element wasn't found");
    }

    T** begin() const
    {
        return data;
    }

    T** end() const
    {
        return data + rows;
    }

    Matrix<T> transpose() const
    {
        Matrix<T> result(cols, rows);

        // Using iterators to iterate over the original matrix
        for (auto row = begin(); row != end(); ++row)
        {
            for (size_t col = 0; col < cols; ++col)
            {
                result[col][row - begin()] = (*row)[col];
            }
        }

        return result;
    }

    T* operator[](size_t index) const
    {
        return data[index];
    }

};









template <typename T>
class MatrixIterator {
private:
    Matrix<T>& matrix;
    size_t row, col;

public:
    MatrixIterator(Matrix<T>& mat, size_t r, size_t c) : matrix(mat), row(r), col(c) {}

    T& operator*() const
    {
        return matrix.data[row][col];
    }

    MatrixIterator& operator++()
    {
        ++col;
        if (col == matrix.cols)
        {
            ++row;
            col = 0;
        }
        return *this;
    }

    MatrixIterator& operator--() {
        if (col == 0)
        {
            --row;
            col = matrix.cols - 1;
        }

        else
        {
            --col;
        }

        return *this;
    }

    MatrixIterator operator+(size_t n) const
    {
        MatrixIterator temp = *this;
        temp.col += n;
        temp.row += temp.col / matrix.cols;
        temp.col %= matrix.cols;
        return temp;
    }

    MatrixIterator operator-(size_t n) const
    {
        MatrixIterator temp = *this;
        temp.col -= n;
        while (temp.col >= matrix.cols)
        {
            temp.col += matrix.cols;
            --temp.row;
        }
        return temp;
    }

    bool operator==(const MatrixIterator& other) const
    {
        return (&matrix == &other.matrix) && (row == other.row) && (col == other.col);
    }

    bool operator!=(const MatrixIterator& other) const
    {
        return *this != other;
    }
};


#endif // CHESS_MATRIX_H
