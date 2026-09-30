#include <unity.h>
#include <algorithm>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

void test_median3_bruteforce(void)
{
	int p[3] = {0, 1, 2};
	do
	{
		ObservableArray<int> src(p, 3);
		auto& f = src.Median3();
		Sink<int> s;
		f.Subscribe(s);
		TEST_ASSERT_EQUAL_INT(1, s.values.back());
	} while (std::next_permutation(p, p + 3));
}

void test_median5_bruteforce(void)
{
	int p[5] = {0, 1, 2, 3, 4};
	do
	{
		ObservableArray<int> src(p, 5);
		auto& f = src.Median5();
		Sink<int> s;
		f.Subscribe(s);
		TEST_ASSERT_EQUAL_INT(2, s.values.back());
	} while (std::next_permutation(p, p + 5));
}

void test_moving_average(void)
{
	float seq[5] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
	ObservableArray<float> src(seq, 5);
	auto& f = src.MovingAverage(3);
	Sink<float> s;
	f.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(5, s.values.size());
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 2.0f, s.values[2]); // (1+2+3)/3
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 4.0f, s.values[4]); // (3+4+5)/3
}

void test_moving_rms(void)
{
	float seq[2] = {3.0f, 4.0f};
	ObservableArray<float> src(seq, 2);
	auto& f = src.MovingRMS(2);
	Sink<float> s;
	f.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 3.5355339f, s.values.back()); // sqrt((9+16)/2)
}

void test_on_rising(void)
{
	int arr[4] = {1, 2, 1, 0};
	ObservableArray<int> src(arr, 4);
	auto& f = src.OnRising();
	Sink<int> s;
	f.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(2, s.values[0]);
}

void test_on_falling(void)
{
	int arr[4] = {1, 2, 1, 0};
	ObservableArray<int> src(arr, 4);
	auto& f = src.OnFalling();
	Sink<int> s;
	f.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
	TEST_ASSERT_EQUAL_INT(1, s.values[0]);
	TEST_ASSERT_EQUAL_INT(0, s.values[1]);
}

void test_low_pass(void)
{
	float arr[1] = {1.0f};
	ObservableArray<float> src(arr, 1);
	auto& f = src.LowPass(0.5);
	Sink<float> s;
	f.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.5f, s.values[0]);
}

void test_high_pass(void)
{
	float arr[1] = {1.0f};
	ObservableArray<float> src(arr, 1);
	auto& f = src.HighPass(0.5);
	Sink<float> s;
	f.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.5f, s.values[0]);
}

void test_pass_stop_band(void)
{
	float arr[1] = {1.0f};
	ObservableArray<float> src(arr, 1);
	auto& pb = src.PassBand(0.1, 0.9);
	Sink<float> sp;
	pb.Subscribe(sp);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.8f, sp.values[0]); // high(0.9) - low(0.1)

	auto& sb = src.StopBand(0.1, 0.9);
	Sink<float> ss;
	sb.Subscribe(ss);
	TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.2f, ss.values[0]); // 1.0 - 0.8
}

void test_is_equal(void)
{
	int arr[4] = {1, 2, 3, 0};
	ObservableArray<int> src(arr, 4);
	auto& f = src.IsEqual(2);
	Sink<int> s;
	f.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(2, s.values[0]);
}

void test_is_less(void)
{
	int arr[4] = {1, 2, 3, 0};
	ObservableArray<int> src(arr, 4);
	auto& f = src.IsLess(3);
	Sink<int> s;
	f.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size()); // 1, 2, 0 are < 3
}

void test_is_zero(void)
{
	int arr[4] = {1, 2, 3, 0};
	ObservableArray<int> src(arr, 4);
	auto& f = src.IsZero();
	Sink<int> s;
	f.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(0, s.values[0]);
}

void test_debounce(void)
{
	ObservableProperty<int> src;
	auto& f = src.DebounceMillis(10);
	Sink<int> s;
	f.Subscribe(s);
	g_millis = 0;  src = 1; // elapsed 0  -> dropped
	g_millis = 20; src = 2; // elapsed 20 -> emitted
	g_millis = 25; src = 3; // elapsed 5  -> dropped
	g_millis = 35; src = 4; // elapsed 15 -> emitted
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
	TEST_ASSERT_EQUAL_INT(2, s.values[0]);
	TEST_ASSERT_EQUAL_INT(4, s.values[1]);
}

void test_window(void)
{
	ObservableProperty<int> src;
	auto& f = src.WindowMillis(100);
	Sink<int> s;
	f.Subscribe(s);
	g_millis = 0;   src = 1; // opens window, elapsed 0 -> emitted
	g_millis = 50;  src = 2; // elapsed 50 -> emitted
	g_millis = 200; src = 3; // elapsed 200 -> dropped
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
}
