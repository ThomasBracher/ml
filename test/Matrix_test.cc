/*
 * Matrix_test.cc
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "gtest/gtest.h"
#include "../src/Matrix.h"

using neurons::Matrix;

TEST(MatrixTest, ShouldNotAcceptUnsufficientData) {
    try {
    	const Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0 });
        FAIL() << "matrix should not build with unsufficient data";
    } catch (std::exception& e) {
        SUCCEED() << "matrix throwed an expected error";
    }
}

void no_out_of_bound_allowed(const Matrix& matrix, const int& i, const int& j) {
    try {
        matrix.get(i, j);
        FAIL() << "matrix should not allow out of bound gets on " << i << ", " << j;
    } catch (std::exception& e) {}
}
TEST(MatrixTest, ShouldNotGetOutOfBoundPositions) {
	Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0, 0 });
    no_out_of_bound_allowed(matrix, -1, 0);
    no_out_of_bound_allowed(matrix, -1, -1);
    no_out_of_bound_allowed(matrix, 0, -1);
    no_out_of_bound_allowed(matrix, 3, 3);
    no_out_of_bound_allowed(matrix, 0, 3);
    no_out_of_bound_allowed(matrix, 2, 0);
}

TEST(MatrixTest, ToStringWhenInitializing) {
	Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0, 0 });
	EXPECT_STREQ("[ 0 0 0\n  0 0 0 ]", matrix.toString().c_str());
}

TEST(MatrixTest, MatrixShouldBeOkForProduct) {
    const Matrix matrix_a(2, 2, std::vector<double> { 1, 1, 2, 3 });
    const Matrix matrix_b(3, 1, std::vector<double> { 1, 1, 2 });
    try {
        matrix_a.product(matrix_b);
        FAIL() << "matrix size should not be legal";
    } catch (std::exception& e) {
        SUCCEED() << "throwed error";
    }
}

TEST(MatrixTest, RespectProductProperties) {
    const Matrix matrix_a(2, 2, std::vector<double> { 1, 1, 2, 3 });
    const Matrix matrix_b(2, 1, std::vector<double> { 1, 1 });
    EXPECT_STREQ("[ 2\n  5 ]", matrix_a.product(matrix_b).toString().c_str());

    const Matrix matrix_c(1, 3, std::vector<double> { 1, 2, 3 });
    const Matrix matrix_d(3, 1, std::vector<double> { -6, -1, 4 });
    EXPECT_STREQ("[ 4 ]", matrix_c.product(matrix_d).toString().c_str());
    EXPECT_STREQ("[ -6 -12 -18\n  -1 -2 -3\n  4 8 12 ]", matrix_d.product(matrix_c).toString().c_str());
}

TEST(MatrixTest, AddMatrixTogether) {
    const Matrix matrix_a(2, 3, std::vector<double> { 1, 3, 1, 5, 1, 7 });
    const Matrix matrix_b(2, 3, std::vector<double> { 1, 1, 0, 1, 1, -1 });
    EXPECT_STREQ("[ 2 4 1\n  6 2 6 ]", (matrix_a + matrix_b).toString().c_str());
}

TEST(MatrixTest, FillUpTheMatrix) {
    const Matrix matrix_a(2, 3, []() { return 1; });
    EXPECT_STREQ("[ 1 1 1\n  1 1 1 ]", matrix_a.toString().c_str());
}

TEST(MatrixTest, exponential) {
    const Matrix matrix(2, 2, []() { return 0; });
    EXPECT_STREQ("[ 1 1\n  1 1 ]", matrix.toExp().toString().c_str());
}

TEST(MatrixTest, unarySubstraction) {
    const Matrix matrix(2, 2, std::vector<double> { 0, 1, -1, -2 });
    EXPECT_STREQ("[ 0 -1\n  1 2 ]", (-matrix).toString().c_str());
}

TEST(MatrixTest, divisionWithInteger) {
    const Matrix matrix_a(2, 2, std::vector<double> { 0.2, 1, -1, -0.01 });
    EXPECT_STREQ("[ 5 1\n  -1 -100 ]", (1 / matrix_a).toString().c_str());

    const Matrix matrix_b(2, 2, std::vector<double> { 2, 22, -4, 0 });
    EXPECT_STREQ("[ 1 11\n  -2 0 ]", (matrix_b / 2).toString().c_str());

    try {
    	const Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0 });
        const Matrix result = 1 / matrix;
        FAIL() << "matrix should not permit zero division";
    } catch (std::exception& e) {
    }
    try {
        const Matrix result = matrix_a / 0;
        FAIL() << "matrix should not permit zero division, got: " << result.toString();
    } catch (std::exception& e) {
        SUCCEED() << "matrix did managed zero division";
    }
}

TEST(MatrixTest, ScalarMultiplication) {
    const Matrix matrix_a(2, 2, std::vector<double> { 1, 1, 2, 3 });
	EXPECT_STREQ("[ 1 1\n  2 3 ]", matrix_a.toString().c_str());
	EXPECT_STREQ("[ 4 4\n  8 12 ]", (matrix_a * 4).toString().c_str());
    const Matrix matrix_b(4, 2, std::vector<double> { 1, 2, 3, -1, -2, -4, 2, 2 });
    EXPECT_STREQ("[ -1 -2\n  -3 1\n  2 4\n  -2 -2 ]", (-1 * matrix_b).toString().c_str());

    try {
    	const Matrix matrix(2, 3, std::vector<double> { 0, 0, 0, 0, 0 });
        FAIL() << "matrix should not build with unsufficient data";
    } catch (std::exception& e) {
        SUCCEED() << "matrix throwed an expected error";
    }
}

TEST(MatrixTest, toGrayScaleImage) {
    const Matrix image(3, 2, std::vector<double> { 0, 0, 0, 0, 3, 255 });
    ASSERT_STREQ("P2\n3 2\n255\n0 0 \n0 0 \n3 255 \n", image.toPgm().c_str());
}

TEST(MatrixTest, zeros) {
    const Matrix matrix = neurons::zeros(3, 4);
    ASSERT_STREQ("[ 0 0 0 0\n  0 0 0 0\n  0 0 0 0 ]", matrix.toString().c_str());
}

TEST(MatrixTest, transpose) {
	Matrix matrix(2, 3, std::vector<double> { 0, 1, 0, 0, 1, 0 });
	ASSERT_STREQ("[ 0 0\n  1 1\n  0 0 ]", matrix.transpose().toString().c_str());
}

