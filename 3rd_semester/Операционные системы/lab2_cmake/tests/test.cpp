#include "pch.h"
#include "C:\Users\user\Desktop\testlab2\testlab2\header.h"
#include <thread>
#include <Windows.h>

TEST(ArrayFunctionsTest, BasicAverage) {
    n = 3;
    int arr[] = { 1, 2, 3 };
    std::thread averageThread(average_func, arr);
    averageThread.join();
    EXPECT_EQ(average, 2);
}

TEST(ArrayFunctionsTest, SingleElement) {
    n = 1;
    int arr[] = { 5 };
    std::thread averageThread(average_func, arr);
    averageThread.join();
    EXPECT_EQ(average, 5);
}

TEST(ArrayFunctionsTest, NegativeNumbers) {
    n = 4;
    int arr[] = { -1, -2, -3, -4 };
    std::thread averageThread(average_func, arr);
    averageThread.join();
    EXPECT_EQ(average, -2);
}

TEST(ArrayFunctionsTest, BasicMinMax) {
    n = 5;
    int arr[] = { 5, 3, 8, 1, 9 };
    std::thread minMaxThread(min_max_func, arr);
    minMaxThread.join();
    ASSERT_EQ(indexes.size(), 2);
    std::set<int> indexSet(indexes.begin(), indexes.end());
    std::set<int> expected = { 3, 4 };
    EXPECT_EQ(indexSet, expected);
    EXPECT_EQ(arr[3], 1);  // min
    EXPECT_EQ(arr[4], 9);  // max
}

TEST(ArrayFunctionsTest, SameElements) {
    n = 4;
    int arr[] = { 7, 7, 7, 7 };
    std::thread averageThread(average_func, arr);
    std::thread minMaxThread(min_max_func, arr);
    averageThread.join();
    minMaxThread.join();
    EXPECT_EQ(average, 7);
    EXPECT_EQ(indexes.size(), 4);
}

TEST(ArrayFunctionsTest, MinMaxAtEdges) {
    n = 4;
    int arr[] = { 10, 5, 5, 1 };
    std::thread minMaxThread(min_max_func, arr);
    minMaxThread.join();
    ASSERT_EQ(indexes.size(), 2);
    std::set<int> indexSet(indexes.begin(), indexes.end());
    std::set<int> expected = { 0, 3 };
    EXPECT_EQ(indexSet, expected);
    EXPECT_EQ(arr[0], 10); // max
    EXPECT_EQ(arr[3], 1);  // min
}

TEST(ArrayFunctionsTest, ZeroValues) {
    n = 3;
    int arr[] = { 0, 0, 0 };
    std::thread averageThread(average_func, arr);
    std::thread minMaxThread(min_max_func, arr);
    averageThread.join();
    minMaxThread.join();
    EXPECT_EQ(average, 0);
    EXPECT_EQ(indexes.size(), 3);
}

TEST(ArrayFunctionsTest, MixedPositiveNegative) {
    n = 5;
    int arr[] = { -5, 10, -3, 7, 0 };
    std::thread averageThread(average_func, arr);
    averageThread.join();
    EXPECT_EQ(average, 1);
}

TEST(ArrayFunctionsTest, EmptyArray) {
    n = 0;
    int* arr = nullptr;

    std::thread minMaxThread(min_max_func, arr);
    std::thread averageThread(average_func, arr);
    minMaxThread.join();
    averageThread.join();

    EXPECT_EQ(average, 0);
    EXPECT_TRUE(indexes.empty());
}

TEST(ArrayFunctionsTest, ManyMinMax) {
    n = 6;
    int arr[] = { 1, 2, 1, 9, 3, 9 };
    std::thread minMaxThread(min_max_func, arr);
    minMaxThread.join();
    ASSERT_EQ(indexes.size(), 4);
    std::set<int> indexSet(indexes.begin(), indexes.end());
    std::set<int> expected = { 0, 2, 3, 5 };
    EXPECT_EQ(indexSet, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}