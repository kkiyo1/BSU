#include "pch.h"
#include <gtest/gtest.h>
#include "C:\Users\user\Desktop\kollok\kollok\header.h"
#include <iostream>
#include <string>

TEST(ArrayTest, ConstructorAndSize) {
    Array arr(5);
    EXPECT_EQ(arr.getSize(), 5);
}

TEST(ArrayTest, FactorialsCalculation) {
    Array arr(5);
    arr.factorials(5);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 6);
    EXPECT_EQ(arr[3], 24);
    EXPECT_EQ(arr[4], 120);
}

TEST(ArrayTest, NoDuplicates) {
    Array arr(6);
    arr[0] = 1; arr[1] = 2; arr[2] = 1;
    arr[3] = 3; arr[4] = 2; arr[5] = 4;

    Array result = arr.noDuplicates();
    EXPECT_EQ(result.getSize(), 4);
}

TEST(ArrayTest, ReverseArray) {
    Array arr(4);
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4;

    arr.reverse();
    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 2);
    EXPECT_EQ(arr[3], 1);
}

TEST(LinkedListTest, ConstructorAndEmptyList) {
    LinkedList list;
    EXPECT_EQ(list.getSize(), 0);
}

TEST(LinkedListTest, PushAndSize) {
    LinkedList list;
    list.push(1);
    list.push(2);
    list.push(3);

    EXPECT_EQ(list.getSize(), 3);
}

TEST(FactorialTest, BasicValues) {
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(5), 120);
    EXPECT_EQ(factorial(10), 3628800);
}

TEST(ArrayTest, EmptyArray) {
    Array arr(0);
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(ArrayTest, AccessOperatorOutOfBounds) {
    Array arr(3);
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr[-1], std::out_of_range);
}

TEST(ArrayTest, FactorialsWithSmallerCount) {
    Array arr(10);
    arr.factorials(3);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 6);
}

TEST(FactorialTest, EdgeCases) {
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(12), 479001600);
}

TEST(ArrayTest, NoDuplicatesWithAllSameElements) {
    Array arr(5);
    for (int i = 0; i < 5; i++) {
        arr[i] = 42;
    }

    Array result = arr.noDuplicates();
    EXPECT_EQ(result.getSize(), 1);
    EXPECT_EQ(result[0], 42);
}

TEST(LinkedListTest, SingleElementList) {
    LinkedList list;
    list.push(42);

    EXPECT_EQ(list.getSize(), 1);
    list.reverse();
    EXPECT_EQ(list.getSize(), 1);
}

TEST(ArrayTest, ReverseEmptyArray) {
    Array arr(0);
    EXPECT_NO_THROW(arr.reverse());
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(FactorialTest, NegativeNumber) {
    EXPECT_EQ(factorial(-1), 1);
}