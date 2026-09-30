#include <unity.h>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

static bool isEven(int v) { return v % 2 == 0; }
static bool lessThan3(int v) { return v < 3; }
static bool greaterThan3(int v) { return v > 3; }
static int g_actionCount = 0;
static void countAction(int) { g_actionCount++; }
static int g_cbCount = 0;
static void countCb() { g_cbCount++; }

void test_where(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.Where(isEven);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_EQUAL_INT(6, s.values.back());
}

void test_distinct(void)
{
	int arr[6] = {1, 1, 2, 2, 3, 3};
	ObservableArray<int> src(arr, 6);
	auto& op = src.Distinct();
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
}

void test_first(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	ObservableArray<int> src(arr, 5);
	auto& op = src.First();
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(1, s.values[0]);
	TEST_ASSERT_EQUAL_INT(1, s.completeCount);
}

void test_last(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	ObservableArray<int> src(arr, 5);
	auto& op = src.Last();
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(5, s.values[0]);
}

void test_skip(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.Skip(2);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(4, s.values.size());
	TEST_ASSERT_EQUAL_INT(3, s.values[0]);
}

void test_take(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.Take(3);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_EQUAL_INT(3, s.values.back());
}

void test_take_at(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	ObservableArray<int> src(arr, 5);
	auto& op = src.TakeAt(2);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(3, s.values[0]);
}

void test_take_first(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	ObservableArray<int> src(arr, 5);
	auto& op = src.TakeFirst();
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(1, s.values[0]);
}

void test_take_last(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	ObservableArray<int> src(arr, 5);
	auto& op = src.TakeLast();
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_EQUAL_INT(5, s.values[0]);
}

void test_take_until(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.TakeUntil(greaterThan3);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size()); // 1, 2, 3
}

void test_take_while(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.TakeWhile(lessThan3);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(2, s.values.size()); // 1, 2
}

void test_skip_until(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.SkipUntil(greaterThan3);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size()); // 4, 5, 6
	TEST_ASSERT_EQUAL_INT(4, s.values[0]);
}

void test_skip_while(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.SkipWhile(lessThan3);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(4, s.values.size()); // 3, 4, 5, 6
	TEST_ASSERT_EQUAL_INT(3, s.values[0]);
}

void test_batch(void)
{
	int arr[6] = {1, 2, 3, 4, 5, 6};
	ObservableArray<int> src(arr, 6);
	auto& op = src.Batch(3);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(6, s.values.size()); // no values dropped at boundaries
}

void test_foreach(void)
{
	g_actionCount = 0;
	g_cbCount = 0;
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& op = src.ForEach(countAction);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, g_actionCount);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
}

void test_if(void)
{
	g_actionCount = 0;
	g_cbCount = 0;
	int arr[4] = {1, 2, 3, 4};
	ObservableArray<int> src(arr, 4);
	auto& op = src.If(isEven, countAction);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(2, g_actionCount); // only for 2 and 4
	TEST_ASSERT_EQUAL_INT(4, s.values.size());
}

void test_timeout_millis(void)
{
	g_actionCount = 0;
	g_cbCount = 0;
	ObservableProperty<int> src;
	auto& op = src.TimeoutMillis(1000, countCb);
	Sink<int> s;
	op.Subscribe(s);
	src = 1; // resets the timer
	g_millis = 500;  op.Update(); // not expired
	TEST_ASSERT_EQUAL_INT(0, g_cbCount);
	g_millis = 1500; op.Update(); // expired
	TEST_ASSERT_EQUAL_INT(1, g_cbCount);
	TEST_ASSERT_EQUAL_INT(1, s.completeCount);
}

void test_repeat(void)
{
	int arr[2] = {1, 2};
	ObservableArray<int> src(arr, 2);
	auto& op = src.Repeat(2);
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(4, s.values.size()); // 1, 2, 1, 2
	TEST_ASSERT_EQUAL_INT(1, s.values[2]);
	TEST_ASSERT_EQUAL_INT(2, s.values[3]);
}

void test_do_reset(void)
{
	int arr[2] = {1, 2};
	ObservableArray<int> src(arr, 2);
	auto& op = src.DoReset();
	Sink<int> s;
	op.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
	op.Reset(); // resets the parent -> re-runs
	TEST_ASSERT_EQUAL_INT(4, s.values.size());
}

void test_not_reset(void)
{
	ObservableManualDefer<int> src;
	auto& op = src.NotReset();
	Sink<int> s;
	op.Subscribe(s);
	op.Reset(); // completes children without resetting the parent
	TEST_ASSERT_EQUAL_INT(1, s.completeCount);
}
