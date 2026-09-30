#include <unity.h>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

static int addOne(int v) { return v + 1; }
static float half(int v) { return (float)v / 2.0f; }
static int sumInt(int acc, int v) { return acc + v; }

void test_select(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& t = src.Select(addOne);
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_EQUAL_INT(4, s.values.back());
}

void test_map(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& t = src.Map<float>(half);
	Sink<float> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.5f, s.values.back());
}

void test_cast(void)
{
	int arr[3] = {1, 2, 3};
	ObservableArray<int> src(arr, 3);
	auto& t = src.Cast<float>();
	Sink<float> s;
	t.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.001f, 3.0f, s.values.back());
}

void test_reduce(void)
{
	int arr[4] = {1, 2, 3, 4};
	ObservableArray<int> src(arr, 4);
	auto& t = src.Reduce<int>(sumInt, 0);
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(10, s.values.back());
}

void test_limit(void)
{
	int arr[5] = {0, 1, 5, 9, 10};
	ObservableArray<int> src(arr, 5);
	auto& t = src.Limit(1, 9);
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values[0]);
	TEST_ASSERT_EQUAL_INT(9, s.values.back());
}

void test_limit_upper(void)
{
	int arr[4] = {0, 5, 10, 15};
	ObservableArray<int> src(arr, 4);
	auto& t = src.LimitUpper(10);
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(10, s.values.back());
}

void test_limit_lower(void)
{
	int arr[4] = {0, 5, 10, 15};
	ObservableArray<int> src(arr, 4);
	auto& t = src.LimitLower(5);
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(5, s.values[0]);
}

void test_scale(void)
{
	float arr[3] = {0.0f, 5.0f, 10.0f};
	ObservableArray<float> src(arr, 3);
	auto& t = src.Scale(0.0f, 10.0f, 0.0f, 100.0f);
	Sink<float> s;
	t.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.001f, 50.0f, s.values[1]);
	TEST_ASSERT_FLOAT_WITHIN(0.001f, 100.0f, s.values.back());
}

void test_abs(void)
{
	// TransformationAbs is not exposed through a fluent method, so it is
	// exercised directly through its public Operator interface.
	TransformationAbs<int> t;
	Sink<int> s;
	t._childObservers.Add(&s);
	t.OnNext(-3);
	t.OnNext(0);
	t.OnNext(3);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_EQUAL_INT(3, s.values[0]);
	TEST_ASSERT_EQUAL_INT(3, s.values[2]);
}

void test_adc_to_voltage(void)
{
	int arr[2] = {0, 512};
	ObservableArray<int> src(arr, 2);
	auto& t = src.AdcToVoltage();
	Sink<float> s;
	t.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.001f, (512.0f * 5.0f) / 1023.0f, s.values.back());
}

void test_toggle(void)
{
	int arr[3] = {1, 1, 1};
	ObservableArray<int> src(arr, 3);
	auto& t = src.Toggle();
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(1, s.values[0]); // first toggle -> HIGH
	TEST_ASSERT_EQUAL_INT(0, s.values[1]);
	TEST_ASSERT_EQUAL_INT(1, s.values[2]);
}

void test_threshold(void)
{
	int arr[4] = {0, 2, 8, 10};
	ObservableArray<int> src(arr, 4);
	auto& t = src.Threshold(5);
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(0, s.values[1]); // 2 is still LOW
	TEST_ASSERT_EQUAL_INT(1, s.values.back()); // 8 and 10 are HIGH
}

void test_elapsed_millis(void)
{
	ObservableProperty<int> src;
	auto& t = src.ElapsedMillis();
	Sink<unsigned long> s;
	t.Subscribe(s);
	g_millis = 100; src = 1;
	g_millis = 250; src = 2;
	TEST_ASSERT_TRUE(s.values[0] == 100UL);
	TEST_ASSERT_TRUE(s.values[1] == 150UL);
}

void test_timestamp_millis(void)
{
	ObservableProperty<int> src;
	auto& t = src.Millis();
	Sink<unsigned long> s;
	t.Subscribe(s);
	g_millis = 100; src = 1;
	g_millis = 250; src = 2;
	TEST_ASSERT_TRUE(s.values[0] == 100UL);
	TEST_ASSERT_TRUE(s.values[1] == 250UL);
}

void test_frequency(void)
{
	ObservableProperty<int> src;
	auto& t = src.Frequency();
	Sink<float> s;
	t.Subscribe(s);
	g_millis = 100; src = 1; // 1000 / 100 = 10 Hz
	g_millis = 200; src = 2; // 1000 / 100 = 10 Hz
	TEST_ASSERT_FLOAT_WITHIN(0.01f, 10.0f, s.values[0]);
	TEST_ASSERT_FLOAT_WITHIN(0.01f, 10.0f, s.values[1]);
}

void test_to_bool(void)
{
	int arr[3] = {0, 1, 2};
	ObservableArray<int> src(arr, 3);
	auto& t = src.ToBool();
	Sink<bool> s;
	t.Subscribe(s);
	TEST_ASSERT_FALSE(s.values[0]);
	TEST_ASSERT_TRUE(s.values[1]);
	TEST_ASSERT_TRUE(s.values[2]);
}

void test_string_buffer(void)
{
	String sarr[2] = {String("ab"), String("cd")};
	ObservableArray<String> src(sarr, 2);
	auto& t = src.StringBuffer();
	Sink<String> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(2, s.values.size());
	TEST_ASSERT_TRUE(strcmp(s.values[1].c_str(), "abcd") == 0);
}

void test_split(void)
{
	String sarr[1] = {String("a;b;c")};
	ObservableArray<String> src(sarr, 1);
	auto& t = src.Split(';');
	Sink<String> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_TRUE(strcmp(s.values[0].c_str(), "a") == 0);
	TEST_ASSERT_TRUE(strcmp(s.values[2].c_str(), "c") == 0);
}

void test_join(void)
{
	String sarr[3] = {String("a"), String("b"), String("c")};
	ObservableArray<String> src(sarr, 3);
	auto& t = src.Join('-');
	Sink<String> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(3, s.values.size());
	TEST_ASSERT_TRUE(strcmp(s.values[2].c_str(), "a-b-c") == 0);
}

void test_parse_int(void)
{
	String sarr[2] = {String("123"), String("45")};
	ObservableArray<String> src(sarr, 2);
	auto& t = src.ParseInt();
	Sink<int> s;
	t.Subscribe(s);
	TEST_ASSERT_EQUAL_INT(123, s.values[0]);
	TEST_ASSERT_EQUAL_INT(45, s.values[1]);
}

void test_parse_float(void)
{
	String sarr[2] = {String("3.5"), String("2.25")};
	ObservableArray<String> src(sarr, 2);
	auto& t = src.ParseFloat();
	Sink<float> s;
	t.Subscribe(s);
	TEST_ASSERT_FLOAT_WITHIN(0.001f, 3.5f, s.values[0]);
	TEST_ASSERT_FLOAT_WITHIN(0.001f, 2.25f, s.values[1]);
}
