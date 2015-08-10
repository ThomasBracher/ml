/*
 * MnistParser_test.cc
 *
 *  Created on: 30 juil. 2015
 *      Author: thomas
 */

#include "gtest/gtest.h"
#include "../src/MnistParser.h"
#include <vector>
#include <exception>

using neurons::MnistLabelParser;
using neurons::MnistImageParser;
using neurons::MnistData;

TEST(MnistLabelParser, shouldReturnTheFirstNumbersCorrectly) {
    MnistLabelParser parser("data/train-labels-idx1-ubyte");
    ASSERT_EQ(std::vector<double>({ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 }), parser.getLabel(0).getData());
    ASSERT_EQ(std::vector<double>({ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }), parser.getLabel(1).getData());
    ASSERT_EQ(std::vector<double>({ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }), parser.getLabel(2).getData());
    ASSERT_EQ(std::vector<double>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }), parser.getLabel(3).getData());
    ASSERT_EQ(std::vector<double>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }), parser.getLabel(4).getData());
    ASSERT_EQ(std::vector<double>({ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }), parser.getLabel(5).getData());
}

TEST(MnistLabelParser, shouldNotPermitReadOnNonExistingIndex) {
    MnistLabelParser parser("data/train-labels-idx1-ubyte");
    try {
        parser.getLabel(-1);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
    parser.getLabel(60000);
    try {
        parser.getLabel(60001);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
}

TEST(MnistImageParser, shouldReturnTheNthImageVectorized) {
    MnistImageParser parser("data/train-images-idx3-ubyte");
    std::vector<double> image = parser.getImage(0);
    std::ostringstream oss;
    for (std::size_t i = 7 * 28; i < 8 * 28; i++) {
        oss << image[i] << " ";
    }
    ASSERT_STREQ("0 0 0 0 0 0 0 0.192157 0.933333 0.992157 0.992157 0.992157 0.992157 0.992157 0.992157 0.992157 0.992157 0.984314 0.364706 0.321569 0.321569 0.219608 0.152941 0 0 0 0 0 ", oss.str().c_str());
}

TEST(MnistImageParser, shouldNotPermitReadOnNonExistingIndex) {
    MnistImageParser parser("data/train-images-idx3-ubyte");
    try {
        parser.getImage(-1);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
    parser.getImage(60000);
    try {
        parser.getImage(60001);
        FAIL() << "Should be out of bound";
    } catch (std::exception& e) {}
}

TEST(MnistData, shouldContainsTheSampleAskedFor) {
    MnistData data(3, 50);
    ASSERT_EQ(std::vector<double>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 }), data.getLabel(0).getData());
    MnistImageParser parser("data/train-images-idx3-ubyte");
    ASSERT_EQ(parser.getImage(3), data.getImage(0));
    ASSERT_EQ(47, data.size());
}

