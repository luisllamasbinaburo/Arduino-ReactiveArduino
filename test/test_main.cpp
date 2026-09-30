// Single Unity test runner for the ReactiveArduino unit tests.
//
// PlatformIO links every *.cpp file in `test/` into a single test binary, so
// there must be exactly one main(), setUp() and tearDown(). Test functions live
// in the per-topic test_*.cpp files and are declared/run here.
#include <unity.h>
#include "ReactiveArduinoLib.h"
using namespace Reactive;
#include "TestHelpers.h"

void setUp(void) { resetMocks(); }
void tearDown(void) {}

// ---- test_aggregates.cpp ----
void test_count(void);
void test_countdown(void);
void test_sum(void);
void test_min(void);
void test_max(void);
void test_average_float(void);
void test_rms_float(void);
void test_any(void);
void test_all_true(void);
void test_all_detects_failure(void);
void test_none(void);
void test_none_detects_match(void);

// ---- test_filters.cpp ----
void test_median3_bruteforce(void);
void test_median5_bruteforce(void);
void test_moving_average(void);
void test_moving_rms(void);
void test_on_rising(void);
void test_on_falling(void);
void test_low_pass(void);
void test_high_pass(void);
void test_pass_stop_band(void);
void test_is_equal(void);
void test_is_less(void);
void test_is_zero(void);
void test_debounce(void);
void test_window(void);

// ---- test_observables.cpp ----
void test_range_ascending(void);
void test_range_descending(void);
void test_range_defer(void);
void test_array(void);
void test_array_defer(void);
void test_property(void);
void test_manual_defer(void);
void test_timer_one_shot(void);
void test_timer_rearm(void);
void test_interval_periodic(void);
void test_analog_input(void);
void test_digital_input(void);

// ---- test_observers.cpp ----
void test_do(void);
void test_do_nothing(void);
void test_finally(void);
void test_do_and_finally(void);
void test_to_property(void);
void test_to_array(void);
void test_to_circular_buffer(void);
void test_digital_output(void);
void test_analog_output(void);
void test_serial_output(void);

// ---- test_operators.cpp ----
void test_where(void);
void test_distinct(void);
void test_first(void);
void test_last(void);
void test_skip(void);
void test_take(void);
void test_take_at(void);
void test_take_first(void);
void test_take_last(void);
void test_take_until(void);
void test_take_while(void);
void test_skip_until(void);
void test_skip_while(void);
void test_batch(void);
void test_foreach(void);
void test_if(void);
void test_timeout_millis(void);
void test_repeat(void);
void test_do_reset(void);
void test_not_reset(void);

// ---- test_transformations.cpp ----
void test_select(void);
void test_map(void);
void test_cast(void);
void test_reduce(void);
void test_limit(void);
void test_limit_upper(void);
void test_limit_lower(void);
void test_scale(void);
void test_abs(void);
void test_adc_to_voltage(void);
void test_toggle(void);
void test_threshold(void);
void test_elapsed_millis(void);
void test_timestamp_millis(void);
void test_frequency(void);
void test_to_bool(void);
void test_string_buffer(void);
void test_split(void);
void test_join(void);
void test_parse_int(void);
void test_parse_float(void);

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_count);
	RUN_TEST(test_countdown);
	RUN_TEST(test_sum);
	RUN_TEST(test_min);
	RUN_TEST(test_max);
	RUN_TEST(test_average_float);
	RUN_TEST(test_rms_float);
	RUN_TEST(test_any);
	RUN_TEST(test_all_true);
	RUN_TEST(test_all_detects_failure);
	RUN_TEST(test_none);
	RUN_TEST(test_none_detects_match);

	RUN_TEST(test_median3_bruteforce);
	RUN_TEST(test_median5_bruteforce);
	RUN_TEST(test_moving_average);
	RUN_TEST(test_moving_rms);
	RUN_TEST(test_on_rising);
	RUN_TEST(test_on_falling);
	RUN_TEST(test_low_pass);
	RUN_TEST(test_high_pass);
	RUN_TEST(test_pass_stop_band);
	RUN_TEST(test_is_equal);
	RUN_TEST(test_is_less);
	RUN_TEST(test_is_zero);
	RUN_TEST(test_debounce);
	RUN_TEST(test_window);

	RUN_TEST(test_range_ascending);
	RUN_TEST(test_range_descending);
	RUN_TEST(test_range_defer);
	RUN_TEST(test_array);
	RUN_TEST(test_array_defer);
	RUN_TEST(test_property);
	RUN_TEST(test_manual_defer);
	RUN_TEST(test_timer_one_shot);
	RUN_TEST(test_timer_rearm);
	RUN_TEST(test_interval_periodic);
	RUN_TEST(test_analog_input);
	RUN_TEST(test_digital_input);

	RUN_TEST(test_do);
	RUN_TEST(test_do_nothing);
	RUN_TEST(test_finally);
	RUN_TEST(test_do_and_finally);
	RUN_TEST(test_to_property);
	RUN_TEST(test_to_array);
	RUN_TEST(test_to_circular_buffer);
	RUN_TEST(test_digital_output);
	RUN_TEST(test_analog_output);
	RUN_TEST(test_serial_output);

	RUN_TEST(test_where);
	RUN_TEST(test_distinct);
	RUN_TEST(test_first);
	RUN_TEST(test_last);
	RUN_TEST(test_skip);
	RUN_TEST(test_take);
	RUN_TEST(test_take_at);
	RUN_TEST(test_take_first);
	RUN_TEST(test_take_last);
	RUN_TEST(test_take_until);
	RUN_TEST(test_take_while);
	RUN_TEST(test_skip_until);
	RUN_TEST(test_skip_while);
	RUN_TEST(test_batch);
	RUN_TEST(test_foreach);
	RUN_TEST(test_if);
	RUN_TEST(test_timeout_millis);
	RUN_TEST(test_repeat);
	RUN_TEST(test_do_reset);
	RUN_TEST(test_not_reset);

	RUN_TEST(test_select);
	RUN_TEST(test_map);
	RUN_TEST(test_cast);
	RUN_TEST(test_reduce);
	RUN_TEST(test_limit);
	RUN_TEST(test_limit_upper);
	RUN_TEST(test_limit_lower);
	RUN_TEST(test_scale);
	RUN_TEST(test_abs);
	RUN_TEST(test_adc_to_voltage);
	RUN_TEST(test_toggle);
	RUN_TEST(test_threshold);
	RUN_TEST(test_elapsed_millis);
	RUN_TEST(test_timestamp_millis);
	RUN_TEST(test_frequency);
	RUN_TEST(test_to_bool);
	RUN_TEST(test_string_buffer);
	RUN_TEST(test_split);
	RUN_TEST(test_join);
	RUN_TEST(test_parse_int);
	RUN_TEST(test_parse_float);

	return UNITY_END();
}
