/*
 * Matrix.cpp
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "Matrix.h"

Matrix::Matrix(const std::size_t& rows, const std::size_t& cols,
		const std::vector<double>& _data) {
	if (_data.size() < rows * cols) {
		throw std::invalid_argument("Data contains not enough data");
	}
	this->rows = rows;
	this->cols = cols;
	this->data = _data;
}

Matrix::Matrix(const std::size_t& rows, const std::size_t& cols, const std::function<double(std::size_t, std::size_t)>& filler) {
	this->rows = rows;
	this->cols = cols;
	this->data = std::vector<double>(rows * cols);
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			this->data[i * cols + j] = filler(i, j);
		}
	}
}

const std::string Matrix::toString() const {
	std::string result("[");
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			result += " ";
			result += std::to_string((int) get(i, j));
		}
		if (i < rows - 1) {
			result += "\n ";
		}
	}
	result += " ]";
	return result;
}

const Matrix Matrix::multiply(const double& alpha) const {
    std::vector<double> new_data(this->rows * this->cols);
    for (std::size_t i = 0; i < this->rows; i++) {
        for (std::size_t j = 0; j < this->cols; j++) {
            new_data[i * this->cols + j] = alpha * get(i, j);
        }
    }
    return Matrix(this->rows, this->cols, new_data);
}

const Matrix Matrix::product(const Matrix& right) const {
    if (this->cols != right.rows) {
        throw std::invalid_argument("size should match");
    }
    Matrix product(rows, right.cols, std::vector<double>(this->rows * right.cols));
    for (std::size_t i = 0; i < this->rows; i++) {
        for (std::size_t j = 0; j < right.cols; j++) {
            double accumulator = 0;
            for (std::size_t k = 0; k < this->cols; k++) {
                accumulator += get(i, k) * right.get(k, j);
            }
            product.set(i, j, accumulator);
        }
    }
    return product;
}

double Matrix::get(const std::size_t& x, const std::size_t& y) const {
    return this->data[x * this->cols + y];
}

const Matrix Matrix::operator +(const Matrix& other) const {
    std::vector<double> new_data(this->rows * this->cols);
    for (std::size_t i = 0; i < new_data.size(); i++) {
        new_data[i] = this->data[i] + other.data[i];
    }
    return Matrix(this->rows, this->cols, new_data);
}

void Matrix::set(const std::size_t& i, const std::size_t& j, const double& value) {
	this->data[i * this->cols + j] = value;
}
