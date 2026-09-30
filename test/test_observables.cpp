#include <unity.h>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

void test_range_ascending(void)
{
	ObservableRange<int> src(1, 5);
	Sink<int> s;
	src.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(5, s.values.size());
	TEST_ASSERT_EQUAL_INT(1, s.values[0]);
	TEST_ASSERT_EQUAL_INT(5, s.values.back());
}

void test_range_descending(void)
{
	ObservableRange<int> src(5, 1, -1);
	Sink<int> s;
	src.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(5, s.values.size());
	TEST_ASSERT_EQUAL_INT(1, s.values.back());
}

void test_range_defer(void)
{
	ObservableRangeDefer<int> src(1, 3);
	Sink<int> s;
	src.Subscribe(s);
	src.Next();
	src.Next();
	src.Next();
	src.Next(); // past the end
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_EQUAL_INT(1, s.completeCount);
}

void test_array(void)
{
	int arr[3] = {10, 20, 30};
	ObservableArray<int> src(arr, 3);
	Sink<int> s;
	src.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_EQUAL_INT(30, s.values.back());
}

void test_array_defer(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArrayDefer<int> src(arr, 3);
	Sink<int> s;
	src.Subscribe(s);
	src.Next();
	src.Next();
	src.Next();
	src.Next();
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
}

void test_property(void)
{
	ObservableProperty<int> src;
	Sink<int> s;
	src.Subscribe(s);
	src = 7;
	src = 8;
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
	src.Finish();
	src = 9; // ignored after completion
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
}

void test_manual_defer(void)
{
	ObservableManualDefer<int> src;
	Sink<int> s;
	src.Subscribe(s);
	src.Next();
	src.Next();
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
}

void test_timer_one_shot(void)
{
	ObservableTimerMillis<unsigned long> t(1000);
	Sink<unsigned long> s;
	t.Subscribe(s);
	g_millis = 500;  t.Update(); // not yet
	g_millis = 1000; t.Update(); // fire
	g_millis = 2000; t.Update(); // already expired
	TEST_ASSERT_EQUAL_INT(1, s.values.size());
	TEST_ASSERT_TRUE(s.values[0] == 1000UL);
}

void test_timer_rearm(void)
{
	ObservableTimerMillis<unsigned long> t(1000);
	Sink<unsigned long> s;
	t.Subscribe(s);
	g_millis = 1000; t.Update(); // fire
	t.Reset();                   // re-arm (startTime = 1000)
	g_millis = 1500; t.Update(); // not yet
	g_millis = 2000; t.Update(); // fire again
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
}

void test_interval_periodic(void)
{
	ObservableIntervalMillis<unsigned long> iv(1000);
	Sink<unsigned long> s;
	iv.Subscribe(s);
	g_millis = 1000; iv.Update(); // fire
	g_millis = 1500; iv.Update(); // not yet
	g_millis = 2000; iv.Update(); // fire
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
}

void test_analog_input(void)
{
	ObservableAnalogInput<int> src(0);
	Sink<int> s;
	src.Subscribe(s);
	g_analogRead = 42;
	src.Next();
	TEST_ASSERT_EQUAL_INT(42, s.values.back());
}

void test_digital_input(void)
{
	ObservableDigitalInput<int> src(1);
	Sink<int> s;
	src.Subscribe(s);
	g_digitalRead = 1;
	src.Next();
	TEST_ASSERT_EQUAL_INT(1, s.values.back());
}
