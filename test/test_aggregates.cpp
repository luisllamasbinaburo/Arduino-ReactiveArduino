#include <unity.h>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

static bool isPositive(int v) { return v > 0; }

void test_count(void)
{
	int arr[4] = {10, 20, 30, 40};
	ObservableArray<int> src(arr, 4);
	auto& agg = src.Count();
	Sink<int> s;
	agg.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(4, s.values.size());
	TEST_ASSERT_EQUAL_INT(4, s.values.back());
}

void test_countdown(void)
{
	int arr[4] = {0, 0, 0, 0};
	ObservableArray<int> src(arr, 4);
	auto& agg = src.CountDown(3);
	Sink<int> s;
	agg.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size()); // 2, 1, 0
	TEST_ASSERT_EQUAL_INT(0, s.values.back());
}

void test_sum(void)
{
	int arr[4] = {1, 2, 3, 4};
	ObservableArray<int> src(arr, 4);
	auto& agg = src.Sum();
	Sink<int> s;
	agg.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(10, s.values.back());
}

void test_min(void)
{
	int arr[5] = {5, 2, 8, 1, 3};
	ObservableArray<int> src(arr, 5);
	auto& agg = src.Min();
	Sink<int> s;
	agg.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.back());
}

void test_max(void)
{
	int arr[5] = {5, 2, 8, 1, 3};
	ObservableArray<int> src(arr, 5);
	auto& agg = src.Max();
	Sink<int> s;
	agg.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(8, s.values.back());
}

void test_average_float(void)
{
	float arr[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	ObservableArray<float> src(arr, 4);
	auto& agg = src.Average();
	Sink<float> s;
	agg.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 2.5f, s.values.back());
}

void test_rms_float(void)
{
	float arr[2] = {3.0f, 4.0f};
	ObservableArray<float> src(arr, 2);
	auto& agg = src.RMS();
	Sink<float> s;
	agg.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 3.5355339f, s.values.back());
}

void test_any(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& agg = src.Any(isPositive);
	Sink<bool> s;
	agg.Subscribe(s);
	TEST_ASSERT_TRUE(s.values.back());
}

void test_all_true(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& agg = src.All(isPositive);
	Sink<bool> s;
	agg.Subscribe(s);
	TEST_ASSERT_TRUE(s.values.back());
}

void test_all_detects_failure(void)
{
	int arr[3] = {1, -2, 3};
	ObservableArray<int> src(arr, 3);
	auto& agg = src.All(isPositive);
	Sink<bool> s;
	agg.Subscribe(s);
	TEST_ASSERT_FALSE(s.values.back());
}

void test_none(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& agg = src.None(isPositive);
	Sink<bool> s;
	agg.Subscribe(s);
	TEST_ASSERT_FALSE(s.values.back());
}

void test_none_detects_match(void)
{
	int arr[3] = {-1, 2, -3};
	ObservableArray<int> src(arr, 3);
	auto& agg = src.None(isPositive);
	Sink<bool> s;
	agg.Subscribe(s);
	TEST_ASSERT_FALSE(s.values.back());
}
