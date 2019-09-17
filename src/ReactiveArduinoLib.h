/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEARDUINOLIB_h
#define _REACTIVEARDUINOLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ReactiveArduinoCore.h"

#include "Observables/Observables.h"
#include "Observers/Observers.h"

#include "Operators/Operators.h"
#include "Transformations/Transformations.h"
#include "Filters/Filters.h"
#include "Aggregates/Aggregates.h"

namespace Reactive
{
#pragma region Observables
	template <typename T>
	auto ManualDefer() -> ObservableManualDefer<T>&
	{
		return *(new ObservableManualDefer<T>());
	}

	template <typename T>
	auto FromRange(T start, T end, T step = 1) -> ObservableRange<T>&
	{
		return *(new ObservableRange<T>(start, end, step));
	}

	template <typename T>
	auto FromRangeDefer(T start, T end, T step = 1) -> ObservableRangeDefer<T>&
	{
		return *(new ObservableRangeDefer<T>(start, end, step));
	}

	template <typename T>
	auto FromArray(T* array, size_t length) -> ObservableArray<T>&
	{
		return *(new ObservableArray<T>(array, length));
	}

	template <typename T>
	auto FromArrayDefer(T* array, size_t length) -> ObservableArrayDefer<T>&
	{
		return *(new ObservableArrayDefer<T>(array, length));
	}

	template <typename T>
	auto Property() -> ObservableProperty<T>&
	{
		return *(new ObservableProperty<T>());
	}

	inline auto FromAnalogInput(uint8_t pin, uint8_t pinMode = INPUT) -> ObservableAnalogInput<int>&
	{
		return *(new ObservableAnalogInput<int>(pin, pinMode));
	}

	inline auto FromDigitalInput(uint8_t pin, uint8_t pinMode = INPUT) -> ObservableDigitalInput<int>&
	{
		return *(new ObservableDigitalInput<int>(pin, pinMode));
	}

	inline auto TimerMillis(unsigned long interval) -> ObservableTimerMillis<unsigned long>&
	{
		return *(new ObservableTimerMillis<unsigned long>(interval));
	}

	inline auto TimerMicros(unsigned long interval) -> ObservableTimerMicros<unsigned long>&
	{
		return *(new ObservableTimerMicros<unsigned long>(interval));
	}

	inline auto IntervalMillis(unsigned long interval, unsigned long delay = 0) -> ObservableIntervalMillis<unsigned long>&
	{
		return *(new ObservableIntervalMillis<unsigned long>(interval, delay));
	}

	inline auto IntervalMicros(unsigned long interval, unsigned long delay = 0) -> ObservableIntervalMicros<unsigned long>&
	{
		return *(new ObservableIntervalMicros<unsigned long>(interval, delay));
	}

	inline auto FromSerial(char separator = '\n') -> ObservableSerial<String>&
	{
		return *(new ObservableSerial<String>(separator));
	}

	template <typename T>
	auto FromSerial() -> ObservableSerial<T>&
	{
		return *(new ObservableSerial<T>());
	}

	template <typename T>
	auto FromSerial(char separator) -> ObservableSerial<T>&
	{
		return *(new ObservableSerial<String>());
	}

	template <>
	inline auto FromSerial<String>() -> ObservableSerial<String>&
	{
		return *(new ObservableSerial<String>());
	}

	template <>
	inline auto FromSerial<char>() -> ObservableSerial<char>&
	{
		return *(new ObservableSerial<char>());
	}

	template <>
	inline auto FromSerial<int>() -> ObservableSerial<int>&
	{
		return *(new ObservableSerial<int>());
	}

	template <>
	inline auto FromSerial<float>() -> ObservableSerial<float>&
	{
		return *(new ObservableSerial<float>());
	}

	template <>
	inline auto FromSerial<double>() -> ObservableSerial<double>&
	{
		return *(new ObservableSerial<double>());
	}
#pragma endregion


#pragma region Observers
	template <typename T>
	ObserverDo<T>& Do(ReactiveAction<T> action)
	{
		return *(new ObserverDo<T>(action));
	}

	template <typename T>
	ObserverFinally<T>& Finally(ReactiveCallback action)
	{
		return *(new ObserverFinally<T>(action));
	}

	template <typename T>
	ObserverDoAndFinally<T>& DoAndFinally(ReactiveAction<T> doAction, ReactiveCallback finallyAction)
	{
		return *(new ObserverDoAndFinally<T>(doAction, finallyAction));
	}

	template <typename T>
	ObserverDoNothing<T>& DoNothing()
	{
		return *(new ObserverDoNothing<T>());
	}

	template <typename T>
	ObserverProperty<T>& ToProperty(T& property)
	{
		return *(new ObserverProperty<T>(property));
	}

	template <typename T>
	ObserverArray<T>& ToArray(T* array, size_t length)
	{
		return *(new ObserverArray<T>(array, length));
	}

	template <typename T>
	ObserverCircularBuffer<T>& ToCircularBuffer(T* array, size_t length)
	{
		return *(new ObserverCircularBuffer<T>(array, length));
	}

	template <typename T>
	ObserverDigitalOutput<T>& ToDigitalOutput(uint8_t pin)
	{
		return *(new ObserverDigitalOutput<T>(pin));
	}

	template <typename T>
	ObserverAnalogOutput<T>& ToAnalogOutput(uint8_t pin)
	{
		return *(new ObserverAnalogOutput<T>(pin));
	}

	template <typename T>
	ObserverSerial<T>& ToSerial()
	{
		return *(new ObserverSerial<T>());
	}

#pragma endregion


#pragma region Operators
	template <typename T>
	OperatorWhere<T>& Where(ReactivePredicate<T> condition)
	{
		return *(new OperatorWhere<T>(condition));
	}

	template <typename T>
	OperatorDistinct<T>& Distinct()
	{
		return *(new OperatorDistinct<T>());
	}

	template <typename T>
	OperatorFirst<T>& First()
	{
		return *(new OperatorFirst<T>());
	}

	template <typename T>
	OperatorLast<T>& Last()
	{
		return *(new OperatorLast<T>());
	}

	template <typename T>
	OperatorSkip<T>& Skip(size_t num)
	{
		return *(new OperatorSkip<T>(num));
	}

	template <typename T>
	OperatorSkipUntil<T>& SkipUntil(ReactivePredicate<T> condition)
	{
		return *(new OperatorSkipUntil<T>(condition));
	}

	template <typename T>
	OperatorSkipWhile<T>& SkipWhile(ReactivePredicate<T> condition)
	{
		return *(new OperatorSkipWhile<T>(condition));
	}


	template <typename T>
	OperatorTake<T>& Take(size_t num)
	{
		return *(new OperatorTake<T>(num));
	}


	template <typename T>
	OperatorTakeAt<T>& TakeAt(size_t index)
	{
		return *(new OperatorTakeAt<T>(index));
	}


	template <typename T>
	OperatorTakeFirst<T>& TakeFirst()
	{
		return *(new OperatorTakeFirst<T>());
	}


	template <typename T>
	OperatorTakeLast<T>& TakeLast()
	{
		return *(new OperatorTakeLast<T>());
	}


	template <typename T>
	OperatorTakeUntil<T>& TakeUntil(ReactivePredicate<T> condition)
	{
		return *(new OperatorTakeUntil<T>(condition));
	}


	template <typename T>
	OperatorTakeWhile<T>& TakeWhile(ReactivePredicate<T> condition)
	{
		return *(new OperatorTakeWhile<T>(condition));
	}

	template <typename T>
	OperatorBatch<T>& Batch(size_t num)
	{
		return *(new OperatorBatch<T>(num));
	}

	template <typename T>
	OperatorIf<T>& If(ReactivePredicate<T> condition, ReactiveAction<T> action)
	{
		return *(new OperatorIf<T>(condition, action));
	}

	template <typename T>
	OperatorForEach<T>& ForEach(ReactiveAction<T> action)
	{
		return *(new OperatorForEach<T>(action));
	}

	template <typename T>
	OperatorTimeoutMillis<T>& TimeoutMillis(ReactiveAction<T> action)
	{
		return *(new OperatorTimeoutMillis<T>(action));
	}

	template <typename T>
	OperatorTimeoutMicros<T>& TimeoutMicros(ReactiveAction<T> action)
	{
		return *(new OperatorTimeoutMicros<T>(action));
	}

	template <typename T>
	OperatorReset<T>& Reset()
	{
		return *(new OperatorReset<T>());
	}

	template <typename T>
	OperatorNoReset<T>& NotReset()
	{
		return *(new OperatorNoReset<T>());
	}

	template <typename T>
	OperatorLoop<T>& Loop()
	{
		return *(new OperatorLoop<T>());
	}

	template <typename T>
	OperatorRepeat<T>& Repeat(size_t N)
	{
		return *(new OperatorRepeat<T>(N));
	}


#pragma endregion


#pragma region Transformations
	template <typename T>
	TransformationSelect<T>& Select(ReactiveFunction<T> function)
	{
		return *(new TransformationSelect<T>(function));
	}

	template <typename Torig, typename Tdest>
	TransformationCast<Torig, Tdest>& Cast()
	{
		return *(new TransformationCast<Torig, Tdest>());
	}

	template <typename Torig, typename Tdest>
	TransformationMap<Torig, Tdest>& Select(ReactiveMap<Torig, Tdest> map)
	{
		return *(new TransformationMap<Torig, Tdest>(map));
	}

	template <typename Torig, typename Tdest>
	TransformationMap<Torig, Tdest>& Map(ReactiveMap<Torig, Tdest> map)
	{
		return *(new TransformationMap<Torig, Tdest>(map));
	}

	template <typename T>
	TransformationReduce<T>& Reduce(ReactiveCompound<T> function)
	{
		return *(new TransformationReduce<T>(function));
	}

	template <typename T>
	TransformationUpperLimit<T>& LimitUpper(T upperLimit)
	{
		return *(new TransformationUpperLimit<T>(upperLimit));
	}

	template <typename T>
	TransformationLowerLimit<T>& LimitLower(T lowerLimit)
	{
		return *(new TransformationLowerLimit<T>(lowerLimit));
	}

	template <typename T>
	TransformationLimit<T>& Limit(T lowerLimit, T upperLimit)
	{
		return *(new TransformationLimit<T>(lowerLimit, upperLimit));
	}

	template <typename T>
	TransformationScale<T>& Scale(T factor)
	{
		return *(new TransformationScale<T>(0, 1, 0, factor));
	}

	template <typename T>
	TransformationScale<T>& Scale(T input_min, T input_max, T output_min, T output_max)
	{
		return *(new TransformationScale<T>(input_min, input_max, output_min, output_max));
	}

	template <typename T>
	TransformationTimestampMillis<T>& Millis()
	{
		return *(new TransformationTimestampMillis<T>());
	}

	template <typename T>
	TransformationTimestampMicros<T>& Micros()
	{
		return *(new TransformationTimestampMicros<T>());
	}

	template <typename T>
	TransformationElapsedMillis<T>& ElapsedMillis()
	{
		return *(new TransformationElapsedMillis<T>());
	}

	template <typename T>
	TransformationElapsedMicros<T>& ElapsedMicros()
	{
		return *(new TransformationElapsedMicros<T>());
	}

	template <typename T>
	TransformationFrequency<T>& Frequency()
	{
		return *(new TransformationFrequency<T>());
	}

	template <typename T>
	TransformationThreshold<T>& Threshold(T threshold)
	{
		return *(new TransformationThreshold<T>(threshold));
	}

	template <typename T>
	TransformationThreshold<T>& Threshold(T threshold, bool state)
	{
		return *(new TransformationThreshold<T>(threshold, state));
	}

	template <typename T>
	TransformationThreshold<T>& DoubleThreshold(T lowThreshold, T highThreshold)
	{
		return *(new TransformationThreshold<T>(lowThreshold, highThreshold));
	}

	template <typename T>
	TransformationThreshold<T>& DoubleThreshold(T lowThreshold, T highThreshold, bool state)
	{
		return *(new TransformationThreshold<T>(lowThreshold, highThreshold, state));
	}

	template <typename T>
	TransformationToggle<T>& Toggle(bool state = false)
	{
		return *(new TransformationToggle<T>(state));
	}

	template <typename T>
	TransformationAdcToVoltage<T>& AdcToVoltage(T input_max = 1023, T output_max = 5.0)
	{
		return *(new TransformationAdcToVoltage<T>(input_max, output_max));
	}

	template <typename T>
	TransformationSplit<T>& Split(char separator = ',')
	{
		return *(new TransformationSplit<T>(separator));
	}

	template <typename T>
	TransformationJoin<T>& Join(char separator = ',')
	{
		return *(new TransformationJoin<T>(separator));
	}

	template <typename T>
	TransformationStringBuffer <T>& StringBuffer()
	{
		return *(new TransformationStringBuffer <T>());
	}

	template <typename T>
	TransformationToBool<T>& ToBool()
	{
		return *(new TransformationToBool<T>());
	}

	template <typename T>
	TransformationParseInt<T>& ParseInt()
	{
		return *(new TransformationParseInt<T>());
	}

	template <typename T>
	TransformationParseFloat<T>& ParseFloat()
	{
		return *(new TransformationParseFloat<T>());
	}
#pragma endregion


#pragma region Filters
	template <typename T>
	FilterOnRising<T>& OnRising()
	{
		return *(new FilterOnRising<T>());
	}

	template <typename T>
	FilterOnFalling<T>& OnFalling()
	{
		return *(new FilterOnFalling<T>());
	}

	template <typename T>
	FilterMedian3<T>& Median3()
	{
		return *(new FilterMedian3<T>());
	}

	template <typename T>
	FilterMedian5<T>& Median5()
	{
		return *(new FilterMedian5<T>());
	}

	template <typename T>
	FilterMovingAverage<T>& MovingAverage(size_t N)
	{
		return *(new FilterMovingAverage<T>(N));
	}

	template <typename T>
	FilterMovingRMS<T>& MovingRMS(size_t N)
	{
		return *(new FilterMovingRMS<T>(N));
	}

	template <typename T>
	FilterLowPass<T>& LowPass(const double alpha)
	{
		return *(new FilterLowPass<T>(alpha));
	}

	template <typename T>
	FilterHighPass<T>& HighPass(const double alpha)
	{
		return *(new FilterHighPass<T>(alpha));
	}

	template <typename T>
	FilterStopBand<T>& StopBand(const double alpha1, const double alpha2)
	{
		return *(new FilterStopBand<T>(alpha1, alpha2));
	}

	template <typename T>
	FilterPassBand<T>& PassBand(const double alpha1, const double alpha2)
	{
		return *(new FilterPassBand<T>(alpha1, alpha2));
	}

	template <typename T>
	FilterDebounceMillis<T>& DebounceMillis(const unsigned long interval)
	{
		return *(new FilterDebounceMillis<T>(interval));
	}

	template <typename T>
	FilterDebounceMicros<T>& DebounceMicros(const unsigned long interval)
	{
		return *(new FilterDebounceMicros<T>(interval));
	}

	template <typename T>
	FilterWindowMillis<T>& WindowMillis(const unsigned long interval)
	{
		return *(new FilterWindowMillis<T>(interval));
	}

	template <typename T>
	FilterWindowMicros<T>& WindowMicros(const unsigned long interval)
	{
		return *(new FilterWindowMicros<T>(interval));
	}

	template <typename T>
	FilterIsLessOrEqual<T>& IsLessOrEqual(T value)
	{
		return *(new FilterIsLessOrEqual<T>(value));
	}

	template <typename T>
	FilterIsLess<T>& IsLess(T value)
	{
		return *(new FilterIsLess<T>(value));
	}

	template <typename T>
	FilterIsGreaterOrEqual<T>& IsGreaterOrEqual(T value)
	{
		return *(new FilterIsGreaterOrEqual<T>(value));
	}

	template <typename T>
	FilterIsGreater<T>& IsGreater(T value)
	{
		return *(new FilterIsGreater<T>(value));
	}

	template <typename T>
	FilterIsNotEqual<T>& IsNotEqual(T value)
	{
		return *(new FilterIsNotEqual<T>(value));
	}

	template <typename T>
	FilterIsEqual<T>& IsEqual(T value)
	{
		return *(new FilterIsEqual<T>(value));
	}

	template <typename T>
	FilterIsNotZero<T>& IsNotZero()
	{
		return *(new FilterIsNotZero<T>());
	}

	template <typename T>
	FilterIsZero<T>& IsZero()
	{
		return *(new FilterIsZero<T>());
	}
#pragma endregion


#pragma region Aggregates
	template <typename T>
	AggregateCount<T>& Count()
	{
		return *(new AggregateCount<T>());
	}

	template <typename T>
	AggregateCountdown<T>& CountDown(size_t N)
	{
		return *(new AggregateCountdown<T>(N));
	}

	template <typename T>
	AggregateSum<T>& Sum()
	{
		return *(new AggregateSum<T>());
	}

	template <typename T>
	AggregateMin<T>& Min()
	{
		return *(new AggregateMin<T>());
	}

	template <typename T>
	AggregateMax<T>& Max()
	{
		return *(new AggregateMax<T>());
	}

	template <typename T>
	AggregateAverage<T>& Average()
	{
		return *(new AggregateAverage<T>());
	}

	template <typename T>
	AggregateRMS<T>& RMS()
	{
		return *(new AggregateRMS<T>());
	}

	template <typename T>
	AggregateAny<T>& Any(ReactivePredicate<T> condition)
	{
		return *(new AggregateAny<T>(condition));
	}

	template <typename T>
	AggregateAll<T>& All(ReactivePredicate<T> condition)
	{
		return *(new AggregateAll<T>(condition));
	}

	template <typename T>
	AggregateNone<T>& None(ReactivePredicate<T> condition)
	{
		return *(new AggregateNone<T>(condition));
	}
#pragma endregion
};

#endif
