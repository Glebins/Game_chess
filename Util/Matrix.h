#ifndef CHESS_MATRIX_H
#define CHESS_MATRIX_H

#include <iostream>

template <typename T>
class MatrixIterator;

/**
 * @brief Generic Matrix class template.
 *
 * The Matrix class template provides a generic implementation for a matrix
 * with common operations such as element access, matrix manipulations, and printing.
 *
 * @tparam T Type of elements stored in the matrix.
 */
template <typename T>
class Matrix {

protected:
    int rows, cols;
    T **data;

public:
    /**
     * Constructor
     * @brief Creates matrix and allocates memory
     * @param rows
     * @param cols
     */
    Matrix(int rows, int cols) : rows(rows), cols(cols)
    {
        data = new T* [rows];
        for (int i = 0; i < rows; i++)
            data[i] = new T[cols];
    }

    /**
     * Destructor
     * @brief free memory
     */
    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    /**
     * @brief free memory from array of rows and cols
     */
    void free_memory()
    {
        for (int i = 0; i < rows; i++)
            delete[] data[i];
        delete[] data;
    }

    /**
     * @brief Returns or sets the element with given coordinates
     * @param i
     * @param j
     * @throw std::out_of_range if there is no element with such position in the matrix
     * @return reference on element with coordinates i, j
     */
    T& at(int i, int j) const
    {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
            throw std::out_of_range("Index out of bounds");
        return data[i][j];
    }

    /**
     * @brief returns number of rows
     * @return number of rows
     */
    int get_rows() const
    {
        return rows;
    }

    /**
     * @brief returns number of cols
     * @return number of cols
     */
    int get_cols() const
    {
        return cols;
    }

    /**
     * @brief print the matrix to the standard (console) out
     */
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

    /**
     * @brief adds another row to the bottom of matrix
     */
    void add_row()
    {
        T** new_data = new T* [rows + 1];
        for (int i = 0; i < rows; i++)
            new_data[i] = data[i];

        new_data[rows] = new T[cols];
        std::swap(data, new_data);
        rows++;
    }

    /**
     * @brief adds another column to the right
     */
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

    /**
     * @brief delete given row
     * @param row you want to delete
     * @throw std::out_of_range if there is no so much rows in the matrix
     */
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

    /**
     * @brief delete given column
     * @throw std::out_of_range if there is no so much cols in the matrix
     * @param col you want to delete
     */
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

    /**
     * @brief find element in table
     * @param elem
     * @throw std::out_of_range if there is no such element in the matrix
     * @return position of element in the matrix
     */
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

    /**
     * @brief returns pointer to the beginning of data
     * @return pointer to begin
     */
    T** begin() const
    {
        return data;
    }

    /**
     * @brief returns pointer to the ending of data
     * @return pointer to end
     */
    T** end() const
    {
        return data + rows;
    }

    /**
     * @brief transpose the matrix
     * @return transposed matrix
     */
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

    /**
     * @brief overloading [] operator to get element
     * @param index
     * @throw std::out_of_range if there is no such element in the matrix
     * @return data by index
     */
    T* operator[](size_t index) const
    {
        return data[index];
    }

};






/**
 * @brief Iterator class for the Matrix class.
 *
 * The MatrixIterator class provides an iterator for the Matrix class,
 * allowing iteration over the elements of a matrix in a convenient way.
 *
 * @tparam T Type of elements stored in the matrix.
 */
template <typename T>
class MatrixIterator {
private:
    Matrix<T>& matrix;
    size_t row, col;

public:
    /**
     * @brief Constructor for MatrixIterator.
     *
     * @param mat Reference to the associated matrix.
     * @param r Initial row index.
     * @param c Initial column index.
     */
    MatrixIterator(Matrix<T>& mat, size_t r, size_t c) : matrix(mat), row(r), col(c) {}

    /**
     * @brief Dereference operator.
     *
     * @return Reference to the element at the current iterator position.
     */
    T& operator*() const
    {
        return matrix.data[row][col];
    }

    /**
     * @brief Pre-increment operator.
     *
     * Advances the iterator to the next element in the matrix.
     *
     * @return Reference to the updated iterator.
     */
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

    /**
     * @brief Pre-decrement operator.
     *
     * Moves the iterator to the previous element in the matrix.
     *
     * @return Reference to the updated iterator.
     */
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

    /**
     * @brief Addition operator.
     *
     * Advances the iterator by the specified number of positions.
     *
     * @param n Number of positions to advance.
     * @return New iterator pointing to the updated position.
     */
    MatrixIterator operator+(size_t n) const
    {
        MatrixIterator temp = *this;
        temp.col += n;
        temp.row += temp.col / matrix.cols;
        temp.col %= matrix.cols;
        return temp;
    }

    /**
     * @brief Subtraction operator.
     *
     * Moves the iterator back by the specified number of positions.
     *
     * @param n Number of positions to move back.
     * @return New iterator pointing to the updated position.
     */
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

    /**
     * @brief Equality operator.
     *
     * @param other Another MatrixIterator to compare with.
     * @return True if the iterators are equal, false otherwise.
     */
    bool operator==(const MatrixIterator& other) const
    {
        return (&matrix == &other.matrix) && (row == other.row) && (col == other.col);
    }

    /**
     * @brief Inequality operator.
     *
     * @param other Another MatrixIterator to compare with.
     * @return True if the iterators are not equal, false otherwise.
     */
    bool operator!=(const MatrixIterator& other) const
    {
        return !(*this == other);
    }
};


#endif // CHESS_MATRIX_H
