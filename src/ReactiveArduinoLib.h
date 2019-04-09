/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEARDUINOLIB_h
#define _REACTIVEARDUINOLIB_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ReactiveArduinoCore.h"

#include "Observables/Observables.h"
#include "Observers/Observers.h"

#include "Operators/Operators.h"
#include "Filters/Filters.h"
#include "Aggregates/Aggregates.h"


class Reactive
{
public:

#pragma region Operators
	template <typename T>
	static OperatorFirst<T>& First()
	{
		return *(new OperatorFirst<T>());
	}

	template <typename T>
	static OperatorLast<T>& Last()
	{
		return *(new OperatorLast<T>());
	}

	template <typename T>
	static OperatorDistinct<T>& Distinct() 
	{
		return *(new OperatorDistinct<T>());
	}
	
	template <typename T>
	static OperatorWhere<T>& Where(ReactiveCondition<T> condition)
	{
		return *(new OperatorWhere<T>(condition));
	}


	template <typename T>
	static OperatorSelect<T>& Select(ReactiveFunction<T> function)
	{
		return *(new OperatorSelect<T>(function));
	}

	template <typename T>
	static OperatorIf<T>& If(ReactiveCondition<T> condition, ReactiveAction<T> function)
	{
		return *(new OperatorIf<T>(condition, function));
	}

	template <typename T>
	static OperatorForEach<T>& ForEach(ReactiveAction<T> function)
	{
		return *(new OperatorForEach<T>(function));
	}

	template <typename Torig, typename Tdest>
	static OperatorMap<Torig, Tdest>& Map(ReactiveMap<Torig, Tdest> map)
	{
		return *(new OperatorMap<Torig, Tdest>(map));
	}

	template <typename T>
	static OperatorToggle<T>& Toggle(bool state = false)
	{
		return *(new OperatorToggle<T>(state));
	}

	template <typename Torig, typename Tdest>
	static OperatorCast<Torig, Tdest>& Cast()
	{
		return *(new OperatorCast<Torig, Tdest>());
	}

	template <typename T>
	static OperatorSkip<T>& Skip(size_t num)
	{
		return *(new OperatorSkip<T>(num));
	}

	template <typename T>
	static OperatorSkipUntil<T>& SkipUntil(ReactiveCondition<T> condition)
	{
		return *(new OperatorSkipUntil<T>(condition));
	}

	template <typename T>
	static OperatorSkipWhile<T>& SkipWhile(ReactiveCondition<T> condition)
	{
		return *(new OperatorSkipWhile<T>(condition));
	}


	template <typename T>
	static OperatorTake<T>& Take(size_t num)
	{
		return *(new OperatorTake<T>(num));
	}


	template <typename T>
	static OperatorTakeAt<T>& TakeAt(size_t index)
	{
		return *(new OperatorTakeAt<T>(index));
	}


	template <typename T>
	static OperatorTakeFirst<T>& TakeFirst()
	{
		return *(new OperatorTakeFirst<T>());
	}


	template <typename T>
	static OperatorTakeLast<T>& TakeLast()
	{
		return *(new OperatorTakeLast<T>());
	}


	template <typename T>
	static OperatorTakeUntil<T>& TakeUntil(ReactiveCondition<T> condition)
	{
		return *(new OperatorTakeUntil<T>(condition));
	}


	template <typename T>
	static OperatorTakeWhile<T>& TakeWhile(ReactiveCondition<T> condition)
	{
		return *(new OperatorTakeWhile<T>(condition));
	}

	template <typename T>
	static OperatorMillis<T>& Millis()
	{
		return *(new OperatorMillis<T>());
	}

	template <typename T>
	static OperatorMicros<T>& Micros()
	{
		return *(new OperatorMicros<T>());
	}

	template <typename T>
	static OperatorElapsedMillis<T>& ElapsedMillis()
	{
		return *(new OperatorElapsedMillis<T>());
	}

	template <typename T>
	static OperatorElapsedMicros<T>& ElapsedMicros()
	{
		return *(new OperatorElapsedMicros<T>());
	}

	template <typename T>
	static OperatorNoReset<T>& NotReset()
	{
		return *(new OperatorNoReset<T>());
	}

	template <typename T>
	static OperatorLoop<T>& Loop()
	{
		return *(new OperatorLoop<T>());
	}

	template <typename T>
	static OperatorRepeat<T>& Repeat(size_t N)
	{
		return *(new OperatorRepeat<T>(N));
	}

	template <typename T>
	static OperatorSplit<T>& Split(char separator = ',')
	{
		return *(new OperatorSplit<T>(separator));
	}

	template <typename T>
	static OperatorBuffer<T>& Buffer()
	{
		return *(new OperatorBuffer<T>());
	}

	template <typename T>
	static OperatorJoin<T>& Join(char separator = ',')
	{
		return *(new OperatorJoin<T>(separator));
	}

	template <typename Torig, typename Tdest>
	static OperatorParseInt<Torig, Tdest>& ParseInt()
	{
		return *(new OperatorParseInt<Torig, Tdest>());
	}

	static OperatorParseFloat<String, float> & ParseFloat()
	{
		return *(new OperatorParseFloat<String, float>());
	}
#pragma endregion


#pragma region Filters
	template <typename T>
	static FilterOnRising<T>& OnRising()
	{
		return *(new FilterOnRising<T>());
	}

	template <typename T>
	static FilterOnFalling<T>& OnFalling()
	{
		return *(new FilterOnFalling<T>());
	}

	template <typename T>
	static FilterMovingAverage<T>& MovingAverage(size_t N)
	{
		return *(new FilterMovingAverage<T>(N));
	}

	template <typename T>
	static FilterMedian3<T>& Median3()
	{
		return *(new FilterMedian3<T>());
	}

	template <typename T>
	static FilterMedian5<T>& Median5()
	{
		return *(new FilterMedian5<T>());
	}

	template <typename T>
	static FilterThreshold<T>& Threshold(T threshold)
	{
		return *(new FilterThreshold<T>(threshold));
	}

	template <typename T>
	static FilterThreshold<T>& Threshold(T threshold, bool state)
	{
		return *(new FilterThreshold<T>(threshold, state));
	}

	template <typename T>
	static FilterThreshold<T>& Threshold(T lowThreshold, T highThreshold)
	{
		return *(new FilterThreshold<T>(lowThreshold, highThreshold));
	}

	template <typename T>
	static FilterThreshold<T>& Threshold(T lowThreshold, T highThreshold, bool state)
	{
		return *(new FilterThreshold<T>(lowThreshold, highThreshold, state));
	}

	template <typename T>
	static FilterLowPass<T>& LowPass(const double alpha)
	{
		return *(new FilterLowPass<T>(alpha));
	}

	template <typename T>
	static FilterHighPass<T>& HighPass(const double alpha)
	{
		return *(new FilterHighPass<T>(alpha));
	}

	template <typename T>
	static FilterStopBand<T>& StopBand(const double alpha1, const double alpha2)
	{
		return *(new FilterStopBand<T>(alpha1, alpha2));
	}

	template <typename T>
	static FilterPassBand<T>& PassBand(const double alpha1, const double alpha2)
	{
		return *(new FilterPassBand<T>(alpha1, alpha2));
	}

	template <typename T>
	static FilterDebounceMillis<T>& DebounceMillis(const unsigned long interval)
	{
		return *(new FilterDebounceMillis<T>(interval));
	}

	template <typename T>
	static FilterDebounceMicros<T>& DebounceMicros(const unsigned long interval)
	{
		return *(new FilterDebounceMicros<T>(interval));
	}

	template <typename T>
	static FilterWindowMillis<T>& WindowMillis(const uint8_t clapNumber, const unsigned long interval)
	{
		return *(new FilterWindowMillis<T>(clapNumber, interval));
	}

	template <typename T>
	static FilterWindowMicros<T>& WindowMicros(const uint8_t clapNumber, const unsigned long interval)
	{
		return *(new FilterWindowMicros<T>(clapNumber, interval));
	}

	template <typename T>
	static FilterUpperLimit<T>& LimitUpper(T upperLimit)
	{
		return *(new FilterUpperLimit<T>(upperLimit));
	}

	template <typename T>
	static FilterLowerLimit<T>& LimitLower(T lowerLimit)
	{
		return *(new FilterLowerLimit<T>(lowerLimit));
	}

	template <typename T>
	static FilterLimit<T>& Limit(T lowerLimit, T upperLimit)
	{
		return *(new FilterLimit<T>(lowerLimit, upperLimit));
	}

	template <typename T>
	static FilterScale<T>& Scale(T input_min, T input_max, T output_min, T output_max)
	{
		return *(new FilterScale<T>(input_min, input_max, output_min, output_max));
	}

	template <typename T>
	static FilterIsLessOrEqual<T>& IsLessOrEqual(T value)
	{
		return *(new FilterIsLessOrEqual<T>(value));
	}

	template <typename T>
	static FilterIsLess<T>& IsLess(T value)
	{
		return *(new FilterIsLess<T>(value));
	}

	template <typename T>
	static FilterIsGreaterOrEqual<T>& IsGreaterOrEqual(T value)
	{
		return *(new FilterIsGreaterOrEqual<T>(value));
	}

	template <typename T>
	static FilterIsGreater<T>& IsGreater(T value)
	{
		return *(new FilterIsGreater<T>(value));
	}

	template <typename T>
	static FilterIsNotEqual<T>& IsNotEqual(T value)
	{
		return *(new FilterIsNotEqual<T>(value));
	}

	template <typename T>
	static FilterIsEqual<T>& IsEqual(T value)
	{
		return *(new FilterIsEqual<T>(value));
	}

	template <typename T>
	static FilterIsNotZero<T>& IsNotZero(T value)
	{
		return *(new FilterIsNotZero<T>(value));
	}

	template <typename T>
	static FilterIsZero<T>& IsZero(T value)
	{
		return *(new FilterIsZero<T>(value));
	}
#pragma endregion


#pragma region Aggregates
	template <typename T>
	static AggregateCount<T>& Count()
	{
		return *(new AggregateCount<T>());
	}

	template <typename T>
	static AggregateSum<T>& Sum()
	{
		return *(new AggregateSum<T>());
	}

	template <typename T>
	static AggregateMin<T>& Min()
	{
		return *(new AggregateMin<T>());
	}

	template <typename T>
	static AggregateMax<T>& Max()
	{
		return *(new AggregateMax<T>());
	}

	template <typename T>
	static AggregateAverage<T>& Average()
	{
		return *(new AggregateAverage<T>());
	}

	template <typename T>
	static AggregateAny<T>& Any(ReactiveCondition<T> condition)
	{
		return *(new AggregateAny<T>(condition));
	}

	template <typename T>
	static AggregateAll<T>& All(ReactiveCondition<T> condition)
	{
		return *(new AggregateAll<T>(condition));
	}

	template <typename T>
	static AggregateNone<T>& None(ReactiveCondition<T> condition)
	{
		return *(new AggregateNone<T>(condition));
	}
#pragma endregion


#pragma region Observables
	template <typename T>
	static ObservableRange<T>& FromRange(T start, T end, T step = 1)
	{
		return *(new ObservableRange<T>(start, end, step));
	}
	template <typename T>
	static ObservableRangeDefer<T>& FromRangeDefer(T start, T end, T step = 1)
	{
		return *(new ObservableRangeDefer<T>(start, end, step));
	}

	template <typename T>
	static ObservableArray<T>& FromArray(T *array, size_t length)
	{
		return *(new ObservableArray<T>(array, length));
	}

	template <typename T>
	static ObservableArrayDefer<T>& FromArrayDefer(T *array, size_t length)
	{
		return *(new ObservableArrayDefer<T>(array, length));
	}

	template <typename T>
	static ObservableProperty<T>& FromProperty()
	{
		return *(new ObservableProperty<T>());
	}

	template <typename T>
	static ObservableTimerMillis<T>& TimerMillis(unsigned long interval)
	{
		return *(new ObservableTimerMillis<T>(interval));
	}

	template <typename T>
	static ObservableTimerMicros<T>& TimerMicros(unsigned long interval)
	{
		return *(new ObservableTimerMicros<T>(interval));
	}

	template <typename T>
	static ObservableIntervalMillis<T>& IntervalMillis(unsigned long interval, unsigned long delay = 0)
	{
		return *(new ObservableIntervalMillis<T>(interval, delay));
	}

	template <typename T>
	static ObservableIntervalMicros<T>& IntervalMicros(unsigned long interval, unsigned long delay = 0)
	{
		return *(new ObservableIntervalMicros<T>(interval, delay));
	}

	
	static ObservableSerialChar<char>& FromSerialChar()
	{
		return *(new ObservableSerialChar<char>());
	}


	static ObservableSerialString<String>& FromSerialString()
	{
		return *(new ObservableSerialString<String>());
	}
	

	static ObservableSerialInteger<int>& FromSerialInteger()
	{
		return *(new ObservableSerialInteger<int>());
	}


	static ObservableSerialFloat<float>& FromSerialFloat()
	{
		return *(new ObservableSerialFloat<float>());
	}

#pragma endregion


#pragma region Observers
	template <typename T>
	static ObserverDo<T>& Do(ReactiveAction<T> action)
	{
		return *(new ObserverDo<T>(action));
	}

	template <typename T>
	static ObserverFinally<T>& Finally(ReactiveCallback action)
	{
		return *(new ObserverFinally<T>(action));
	}

	template <typename T>
	static ObserverDoAndFinally<T>& DoAndFinally(ReactiveAction<T> doAction, ReactiveCallback finallyAction)
	{
		return *(new ObserverDoAndFinally<T>(doAction, finallyAction));
	}

	template <typename T>
	static ObserverProperty<T>& ToProperty(T & property)
	{
		return *(new ObserverProperty<T>(property));
	}

	template <typename T>
	static ObserverArray<T>& ToArray(T *array, size_t length)
	{
		return *(new ObserverArray<T>(array, length));
	}

	template <typename T>
	static ObserverCircularBuffer<T>& ToCircularBuffer(T *array, size_t length)
	{
		return *(new ObserverCircularBuffer<T>(array, length));
	}

	template <typename T>
	static ObserverDigitalOutput<T>& ToDigital(uint8_t pin)
	{
		return *(new ObserverDigitalOutput<T>(pin));
	}

	template <typename T>
	static ObserverAnalogOutput<T>& ToAnalog(uint8_t pin)
	{
		return *(new ObserverAnalogOutput<T>(pin));
	}

	template <typename T>
	static ObserverSerial<T>& ToSerial()
	{
		return *(new ObserverSerial<T>());
	}

#pragma endregion
};

#endif

