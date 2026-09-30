#include <unity.h>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

static int g_actionCount = 0;
static void countAction(int) { g_actionCount++; }
static int g_cbCount = 0;
static void countCb() { g_cbCount++; }

void test_do(void)
{
	g_actionCount = 0;
	g_cbCount = 0;
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	src.Do(countAction);
	TEST_ASSERT_EQUAL_INT(3, g_actionCount);
}

void test_do_nothing(void)
{
	int arr[2] = {1, 2};
	ObservableArray<int> src(arr, 2);
	src.DoNothing(); // must not crash
	TEST_ASSERT_TRUE(true);
}

void test_finally(void)
{
	g_actionCount = 0;
	g_cbCount = 0;
	int arr[2] = {1, 2};
	ObservableArray<int> src(arr, 2);
	src.Finally(countCb);
	TEST_ASSERT_EQUAL_INT(1, g_cbCount);
}

void test_do_and_finally(void)
{
	g_actionCount = 0;
	g_cbCount = 0;
	int arr[2] = {1, 2};
	ObservableArray<int> src(arr, 2);
	src.DoAndFinally(countAction, countCb);
	TEST_ASSERT_EQUAL_INT(2, g_actionCount);
	TEST_ASSERT_EQUAL_INT(1, g_cbCount);
}

void test_to_property(void)
{
	int arr[2] = {10, 20};
	ObservableArray<int> src(arr, 2);
	int out = 0;
	src.ToProperty(out);
	TEST_ASSERT_EQUAL_INT(20, out);
}

void test_to_array(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	int out[3] = {0, 0, 0};
	auto& a = src.ToArray(out, 3);
	TEST_ASSERT_EQUAL_INT(3, out[2]);
	TEST_ASSERT_EQUAL_INT(3, a.GetIndex());
}

void test_to_circular_buffer(void)
{
	int arr[5] = {1, 2, 3, 4, 5};
	ObservableArray<int> src(arr, 5);
	int out[3] = {0, 0, 0};
	src.ToCircularBuffer(out, 3);
	// circular overwrite of a 3-slot buffer with 5 values -> {4, 5, 3}
	TEST_ASSERT_EQUAL_INT(4, out[0]);
	TEST_ASSERT_EQUAL_INT(5, out[1]);
	TEST_ASSERT_EQUAL_INT(3, out[2]);
}

void test_digital_output(void)
{
	int arr[1] = {1};
	ObservableArray<int> src(arr, 1);
	src.ToDigitalOutput(13);
	TEST_ASSERT_EQUAL_INT(OUTPUT, (int)g_pinModeMode);
	TEST_ASSERT_EQUAL_INT(13, (int)g_digitalPin);
	TEST_ASSERT_EQUAL_INT(1, (int)g_digitalValue);
}

void test_analog_output(void)
{
	int arr[1] = {128};
	ObservableArray<int> src(arr, 1);
	src.ToAnalogOutput(9);
	TEST_ASSERT_EQUAL_INT(9, (int)g_analogPin);
	TEST_ASSERT_EQUAL_INT(128, g_analogValue);
}

void test_serial_output(void)
{
	int arr[1] = {42};
	ObservableArray<int> src(arr, 1);
	src.ToSerial();
	TEST_ASSERT_EQUAL_INT(1, Serial.printCount);
}
