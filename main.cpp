#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

// Type alias for cleaner code
using Matrix = std::vector<std::vector<int>>; 

// Function prototypes
bool readMatrices(const std::string& filename, int& N, Matrix& A, Matrix& B);
void printMatrix(const Matrix& mat);
void addMatrices(const Matrix& A, const Matrix& B);
void multiplyMatrices(const Matrix& A, const Matrix& B);
void printDiagonals(const Matrix& mat, const std::string& label);
void swapRows(Matrix mat, int row1, int row2, const std::string& label);
void swapColumns(Matrix mat, int col1, int col2, const std::string& label);
void updateElement(Matrix mat, int row, int col, int newValue, const std::string& label); 

int main() {
    std::string filename;
    std::cout << "Enter the matrix input file name: ";
    std::cin >> filename; 

    int N = 0; 
    Matrix A, B;

    // 1. Read values from file and print them 
    if (!readMatrices(filename, N, A, B)) { 
        return 1; // Exit with error code if file couldn't be read 
    }

    std::cout << "\nMatrix A:\n"; 
    printMatrix(A); 
    std::cout << "\nMatrix B:\n"; 
    printMatrix(B);

    // 2. Add two matrices 
    addMatrices(A, B);

    // 3. Multiply two matrices 
    multiplyMatrices(A, B);

    // 4. Get the sums of matrix diagonal elements 
    printDiagonals(A, "Matrix A");

    // 5. Swap matrix rows (Passing by value to preserve original matrix) 
    swapRows(A, 0, 1, "Matrix A (Swapping Row 0 and Row 1)");

    // 6. Swap matrix columns 
    swapColumns(A, 0, 2, "Matrix A (Swapping Column 0 and Column 2)");

    // 7. Update a matrix element 
    updateElement(A, 1, 1, 99, "Matrix A (Updating element at (1,1) to 99)");

    return 0;
} 

// 1. Read values from file
bool readMatrices(const std::string& filename, int& N, Matrix& A, Matrix& B) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    } 

    if (!(file >> N) || N <= 0) { 
        std::cerr << "Error: Invalid matrix size N." << std::endl; 
        return false; 
    }

    // Resize matrices to N x N 
    A.assign(N, std::vector<int>(N)); 
    B.assign(N, std::vector<int>(N));

    // Read Matrix A 
    for (int i = 0; i < N; ++i) { 
        for (int j = 0; j < N; ++j) { 
            if (!(file >> A[i][j])) { 
                std::cerr << "Error: Failed to read element for Matrix A at (" << i << "," << j << ")" << std::endl; 
                return false; 
            } 
        } 
    }

    // Read Matrix B 
    for (int i = 0; i < N; ++i) { 
        for (int j = 0; j < N; ++j) { 
            if (!(file >> B[i][j])) { 
                std::cerr << "Error: Failed to read element for Matrix B at (" << i << "," << j << ")" << std::endl; 
                return false; 
            } 
        } 
    }

    file.close(); 
    return true;
} 

// Helper function to print matrices with aligned columns
void printMatrix(const Matrix& mat) {
    if (mat.empty()) return;
    for (const auto& row : mat) {
        for (int val : row) {
            std::cout << std::setw(4) << val << " ";
        }
        std::cout << "\n";
    }
} 

// 2. Add two matrices
void addMatrices(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix result(N, std::vector<int>(N)); 

    for (int i = 0; i < N; ++i) { 
        for (int j = 0; j < N; ++j) { 
            result[i][j] = A[i][j] + B[i][j]; 
        } 
    }
    std::cout << "\nMatrix Sum (A + B):\n"; 
    printMatrix(result);
} 

// 3. Multiply two matrices
void multiplyMatrices(const Matrix& A, const Matrix& B) {
    int N = A.size();
    Matrix result(N, std::vector<int>(N, 0)); 

    for (int i = 0; i < N; ++i) { 
        for (int j = 0; j < N; ++j) { 
            for (int k = 0; k < N; ++k) { 
                result[i][j] += A[i][k] * B[k][j]; 
            } 
        } 
    }
    std::cout << "\nMatrix Product (A * B):\n"; 
    printMatrix(result);
} 

// 4. Get sums of diagonal elements
void printDiagonals(const Matrix& mat, const std::string& label) {
    int N = mat.size();
    int mainSum = 0;
    int secondarySum = 0; 

    for (int i = 0; i < N; ++i) { 
        mainSum += mat[i][i]; 
        secondarySum += mat[i][N - 1 - i]; 
    }
    std::cout << "\n" << label << " Diagonals:\n"; 
    std::cout << " Main Diagonal Sum: " << mainSum << "\n"; 
    std::cout << " Secondary Diagonal Sum: " << secondarySum << "\n";
} 

// 5. Swap matrix rows
void swapRows(Matrix mat, int row1, int row2, const std::string& label) {
    int N = mat.size();
    if (row1 >= 0 && row1 < N && row2 >= 0 && row2 < N) {
        std::swap(mat[row1], mat[row2]);
        std::cout << "\n" << label << ":\n";
        printMatrix(mat);
    } else {
        std::cout << "\nError: Row indices out of bounds for swapping.\n";
    }
} 

// 6. Swap matrix columns
void swapColumns(Matrix mat, int col1, int col2, const std::string& label) {
    int N = mat.size();
    if (col1 >= 0 && col1 < N && col2 >= 0 && col2 < N) {
        for (int i = 0; i < N; ++i) {
            std::swap(mat[i][col1], mat[i][col2]);
        }
        std::cout << "\n" << label << ":\n";
        printMatrix(mat);
    } else {
        std::cout << "\nError: Column indices out of bounds for swapping.\n";
    }
} 

// 7. Update a matrix element
void updateElement(Matrix mat, int row, int col, int newValue, const std::string& label) {
    int N = mat.size();
    if (row >= 0 && row < N && col >= 0 && col < N) {
        mat[row][col] = newValue;
        std::cout << "\n" << label << ":\n";
        printMatrix(mat);
    } else {
        std::cout << "\nError: Element indices out of bounds for updating.\n";
    }
}
