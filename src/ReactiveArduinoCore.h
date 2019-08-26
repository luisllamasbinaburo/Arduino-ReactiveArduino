/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEARDUINOCORE_h
#define _REACTIVEARDUINOCORE_h

#include "ReactiveArduinoBases.h"

#pragma region Forward definitions
template <typename T> class ObservableRange;
template <typename T> class ObservableRangeDefer;
template <typename T> class ObservableArray;
template <typename T> class ObservableArrayDefer;
template <typename T> class ObservableProperty;
template <typename T> class ObservableAnalogInput;
template <typename T> class ObservableDigitalInput;
template <typename T> class ObservableTimerMillis;
template <typename T> class ObservableTimerMicros;
template <typename T> class ObservableIntervalMillis;
template <typename T> class ObservableIntervalMicros;
template <typename T> class ObservableSerialChar;
template <typename T> class ObservableSerialString;
template <typename T> class ObservableSerialInteger;
template <typename T> class ObservableSerialFloat;

template <typename T> class FilterOnRising;
template <typename T> class FilterOnFalling;
template <typename T> class FilterMovingAverage;
template <typename T> class FilterMovingRMS;
template <typename T> class FilterMedian5;
template <typename T> class FilterMedian3;
template <typename T> class FilterPassBand;
template <typename T> class FilterStopBand;
template <typename T> class FilterLowPass;
template <typename T> class FilterHighPass;
template <typename T> class FilterDebounceMillis;
template <typename T> class FilterDebounceMicros;
template <typename T> class FilterWindowMillis;
template <typename T> class FilterWindowMicros;
template <typename T> class FilterIsLessOrEqual;
template <typename T> class FilterIsLess;
template <typename T> class FilterIsGreaterOrEqual;
template <typename T> class FilterIsGreater;
template <typename T> class FilterIsNotEqual;
template <typename T> class FilterIsEqual;
template <typename T> class FilterIsNotZero;
template <typename T> class FilterIsZero;

template <typename T> class OperatorWhere;
template <typename T> class OperatorDistinct;
template <typename T> class OperatorLast;
template <typename T> class OperatorFirst;
template <typename T> class OperatorTake;
template <typename T> class OperatorSkip;
template <typename T> class OperatorBatch;
template <typename T> class OperatorTakeAt;
template <typename T> class OperatorTakeFirst;
template <typename T> class OperatorTakeLast;
template <typename T> class OperatorTakeUntil;
template <typename T> class OperatorTakeWhile;
template <typename T> class OperatorSkipUntil;
template <typename T> class OperatorSkipWhile;
template <typename T> class OperatorForEach;
template <typename T> class OperatorIf;
template <typename T> class OperatorTimeoutMillis;
template <typename T> class OperatorTimeoutMicros;
template <typename T> class OperatorLoop;
template <typename T> class OperatorRepeat;
template <typename T> class OperatorNoReset;
template <typename T> class OperatorReset;

template <typename T> class TransformationSelect;
template <typename T> class TransformationReduce;
template <typename Torig, typename Tdest> class TransformationCast;
template <typename Torig, typename Tdest> class TransformationMap;
template <typename T> class TransformationLimit;
template <typename T> class TransformationUpperLimit;
template <typename T> class TransformationLowerLimit;
template <typename T> class TransformationScale;
template <typename T> class TransformationAbs;
template <typename T> class TransformationAdcToVoltage;
template <typename T> class TransformationToggle;
template <typename T> class TransformationThreshold;
template <typename T> class TransformationTimestampMillis;
template <typename T> class TransformationTimestampMicros;
template <typename T> class TransformationFrequency;
template <typename T> class TransformationElapsedMillis;
template <typename T> class TransformationElapsedMicros;
template <typename T> class TransformationStringBuffer;
template <typename T> class TransformationSplit;
template <typename T> class TransformationJoin;
template <typename T> class TransformationToBool;
template <typename T> class TransformationParseFloat;
template <typename T> class TransformationParseInt;

template <typename T> class AggregateCount;
template <typename T> class AggregateCountdown;
template <typename T> class AggregateSum;
template <typename T> class AggregateMin;
template <typename T> class AggregateMax;
template <typename T> class AggregateAverage;
template <typename T> class AggregateRMS;
template <typename T> class AggregateAny;
template <typename T> class AggregateAll;
template <typename T> class AggregateNone;

template <typename T> class ObserverDo;
template <typename T> class ObserverDoNothing;
template <typename T> class ObserverFinally;
template <typename T> class ObserverDoAndFinally;
template <typename T> class ObserverProperty;
template <typename T> class ObserverArray;
template <typename T> class ObserverCircularBuffer;
template <typename T> class ObserverDigitalOutput;
template <typename T> class ObserverAnalogOutput;
template <typename T> class ObserverSerial;
#pragma endregion


/// Observable base
template <typename T>
class Observable : IObservable<T>, IResetable<T>
{
public:

	void Suscribe(IObserver<T> &observer) override = 0;

	void operator >> (IObserver<T> & obs)
	{
		Suscribe(obs);
	}

	template <typename Torig, typename Tdest>
	Observable<Tdest>& operator >> (Operator<Torig, Tdest>& op)
	{
		return Compound(*this, op);
	}

	template <typename Torig, typename Tdest>
	Observable<Tdest> &Compound(Observable<Torig> &obs, Operator<Torig, Tdest> &op)
	{
		op._parentObservable = this;
		return op;
	}

	void Reset() override
	{
		// do nothing
	}

	// "Fluent" behavior
	OperatorWhere<T>& Where(ReactivePredicate<T> condition);
	OperatorDistinct<T>& Distinct();
	OperatorFirst<T>& First();
	OperatorLast<T>& Last();
	OperatorSkip<T>& Skip(size_t num);
	OperatorSkipUntil<T>& SkipUntil(ReactivePredicate<T> condition);
	OperatorSkipWhile<T>& SkipWhile(ReactivePredicate<T> condition);
	OperatorTake<T>& Take(size_t num);
	OperatorTakeAt<T>& TakeAt(size_t index);
	OperatorTakeFirst<T>& TakeFirst();
	OperatorTakeLast<T>& TakeLast();
	OperatorTakeUntil<T>& TakeUntil(ReactivePredicate<T> condition);
	OperatorTakeWhile<T>& TakeWhile(ReactivePredicate<T> condition);
	OperatorBatch<T>& Batch(size_t num);
	OperatorIf<T>& If(ReactivePredicate<T> condition, ReactiveAction<T> action);
	OperatorForEach<T>& ForEach(ReactiveAction<T> action);
	OperatorTimeoutMillis<T>& TimeoutMillis(ReactiveAction<T> action);
	OperatorTimeoutMicros<T>& TimeoutMicros(ReactiveAction<T> action);
	OperatorReset<T>& DoReset();
	OperatorNoReset<T>& NotReset();
	OperatorLoop<T>& Loop();
	OperatorRepeat<T>& Repeat(size_t N);

	TransformationSelect<T>& Select(ReactiveFunction<T> function);
	template <class Tdest> TransformationCast<T, Tdest>& Cast();
	template <class Tdest> TransformationMap<T, Tdest>& Select(ReactiveMap<T, Tdest> map);
	template <class Tdest> TransformationMap<T, Tdest>& Map(ReactiveMap<T, Tdest> map);
	TransformationReduce<T>& Reduce(ReactiveCompound<T> function);
	TransformationUpperLimit<T>& LimitUpper(T upperLimit);
	TransformationLowerLimit<T>& LimitLower(T lowerLimit);
	TransformationLimit<T>& Limit(T lowerLimit, T upperLimit);
	TransformationScale<T>& Scale(T factor);
	TransformationScale<T>& Scale(T input_min, T input_max, T output_min, T output_max);
	TransformationTimestampMillis<T>& Millis();
	TransformationTimestampMicros<T>& Micros();
	TransformationElapsedMillis<T>& ElapsedMillis();
	TransformationElapsedMicros<T>& ElapsedMicros();
	TransformationFrequency<T>& Frequency();
	TransformationThreshold<T>& Threshold(T threshold, int state = LOW);
	TransformationThreshold<T>& DoubleThreshold(T lowThreshold, T highThreshold, int state = LOW);
	TransformationToggle<T>& Toggle(int state = LOW);
	TransformationAdcToVoltage<T>& AdcToVoltage(T input_max = 1023, T output_max = 5.0);
	TransformationSplit<T>& Split(char separator = ',');
	TransformationJoin<T>& Join(char separator = ',');
	TransformationStringBuffer <T>& StringBuffer();
	TransformationToBool<T>& ToBool();
	TransformationCast<T, int>& ToInt();
	TransformationCast<T, float>& ToFloat();
	TransformationParseInt<T>& ParseInt();
	TransformationParseFloat<T>& ParseFloat();

	FilterOnRising<T>& OnRising();
	FilterOnFalling<T>& OnFalling();
	FilterMedian3<T>& Median3();
	FilterMedian5<T>& Median5();
	FilterMovingAverage<T>& MovingAverage(size_t N);
	FilterMovingRMS<T>& MovingRMS(size_t N);
	FilterLowPass<T>& LowPass(double alpha);
	FilterHighPass<T>& HighPass(double alpha);
	FilterStopBand<T>& StopBand(double alpha1, double alpha2);
	FilterPassBand<T>& PassBand(double alpha1, double alpha2);
	FilterDebounceMillis<T>& DebounceMillis(unsigned long interval);
	FilterDebounceMicros<T>& DebounceMicros(unsigned long interval);
	FilterWindowMillis<T>& WindowMillis(unsigned long interval);
	FilterWindowMicros<T>& WindowMicros(unsigned long interval);
	FilterIsLessOrEqual<T>& IsLessOrEqual(T value);
	FilterIsLess<T>& IsLess(T value);
	FilterIsGreaterOrEqual<T>& IsGreaterOrEqual(T value);
	FilterIsGreater<T>& IsGreater(T value);
	FilterIsNotEqual<T>& IsNotEqual(T value);
	FilterIsEqual<T>& IsEqual(T value);
	FilterIsNotZero<T>& IsNotZero();
	FilterIsZero<T>& IsZero();

	AggregateCount<T>& Count();
	AggregateCountdown<T>& CountDown(size_t N);
	AggregateSum<T>& Sum();
	AggregateMin<T>& Min();
	AggregateMax<T>& Max();
	AggregateAverage<T>& Average();
	AggregateRMS<T>& RMS();
	AggregateAny<T>& Any(ReactivePredicate<T> condition);
	AggregateAll<T>& All(ReactivePredicate<T> condition);
	AggregateNone<T>& None(ReactivePredicate<T> condition);

	ObserverSerial<T> ToSerial();
	ObserverDo<T>& Do(ReactiveAction<T> action);
	ObserverFinally<T>& Finally(ReactiveCallback action);
	ObserverDoAndFinally<T>& DoAndFinally(ReactiveAction<T> doAction, ReactiveCallback finallyAction);
	ObserverDoNothing<T>& DoNothing();
	ObserverProperty<T>& ToProperty(T& property);
	ObserverArray<T>& ToArray(T *array, size_t length);
	ObserverCircularBuffer<T>& ToCircularBuffer(T *array, size_t length);
	ObserverDigitalOutput<T>& ToDigitalOutput(uint8_t pin);
	ObserverAnalogOutput<T>& ToAnalogOutput(uint8_t pin);
};

#pragma region Implementation
template <typename T>
auto Observable<T>::Where(ReactivePredicate<T> condition) -> OperatorWhere<T>&
{
	auto newOp = new OperatorWhere<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Distinct() -> OperatorDistinct<T>&
{
	auto newOp = new OperatorDistinct<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::First() -> OperatorFirst<T>&
{
	auto newOp = new OperatorFirst<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Last() -> OperatorLast<T>&
{
	auto newOp = new OperatorLast<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Skip(size_t num) -> OperatorSkip<T>&
{
	auto newOp = new OperatorSkip<T>(num);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::SkipUntil(ReactivePredicate<T> condition) -> OperatorSkipUntil<T>&
{
	auto newOp = new OperatorSkipUntil<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::SkipWhile(ReactivePredicate<T> condition) -> OperatorSkipWhile<T>&
{
	auto newOp = new OperatorSkipWhile<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::Take(size_t num) -> OperatorTake<T>&
{
	auto newOp = new OperatorTake<T>(num);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::TakeAt(size_t index) -> OperatorTakeAt<T>&
{
	auto newOp = new OperatorTakeAt<T>(index);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::TakeFirst() -> OperatorTakeFirst<T>&
{
	auto newOp = new OperatorTakeFirst<T>();
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::TakeLast() -> OperatorTakeLast<T>&
{
	auto newOp = new OperatorTakeLast<T>();
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::TakeUntil(ReactivePredicate<T> condition) -> OperatorTakeUntil<T>&
{
	auto newOp = new OperatorTakeUntil<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::TakeWhile(ReactivePredicate<T> condition) -> OperatorTakeWhile<T>&
{
	auto newOp = new OperatorTakeWhile<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Batch(size_t num) -> OperatorBatch<T>&
{
	auto newOp = new OperatorBatch<T>(num);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::If(ReactivePredicate<T> condition, ReactiveAction<T> action) -> OperatorIf<T>&
{
	auto newOp = new OperatorIf<T>(condition, action);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ForEach(ReactiveAction<T> action) -> OperatorForEach<T>&
{
	auto newOp = new OperatorForEach<T>(action);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::TimeoutMillis(ReactiveAction<T> action) -> OperatorTimeoutMillis<T>&
{
	auto newOp = new OperatorTimeoutMillis<T>(action);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::TimeoutMicros(ReactiveAction<T> action) -> OperatorTimeoutMicros<T>&
{
	auto newOp = new OperatorTimeoutMicros<T>(action);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::DoReset() -> OperatorReset<T>&
{
	auto newOp = new OperatorReset<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::NotReset() -> OperatorNoReset<T>&
{
	auto newOp = new OperatorNoReset<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Loop() -> OperatorLoop<T>&
{
	auto newOp = new OperatorLoop<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Repeat(size_t N) -> OperatorRepeat<T>&
{
	auto newOp = new OperatorRepeat<T>(N);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Select(ReactiveFunction<T> function) -> TransformationSelect<T>&
{
	auto newOp = new TransformationSelect<T>(function);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
template <typename Tdest>
auto Observable<T>::Cast() -> TransformationCast<T, Tdest>&
{
	auto newOp = new TransformationCast<T, Tdest>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
template <typename Tdest>
auto Observable<T>::Map(ReactiveMap<T, Tdest> map) -> TransformationMap<T, Tdest>&
{
	auto newOp = new TransformationMap<T, Tdest>(map);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
template <typename Tdest>
auto Observable<T>::Select(ReactiveMap<T, Tdest> map) -> TransformationMap<T, Tdest>&
{
	auto newOp = new TransformationMap<T, Tdest>(map);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::Reduce(ReactiveCompound<T> function) -> TransformationReduce<T>&
{
	auto newOp = new TransformationReduce<T>(function);
	Compound(*this, *newOp);
	return *newOp;
}


template <typename T>
auto Observable<T>::LimitUpper(T upperLimit) -> TransformationUpperLimit<T>&
{
	auto newOp = new TransformationUpperLimit<T>(upperLimit);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::LimitLower(T lowerLimit) -> TransformationLowerLimit<T>&
{
	auto newOp = new TransformationLowerLimit<T>(lowerLimit);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Limit(T lowerLimit, T upperLimit) -> TransformationLimit<T>&
{
	auto newOp = new TransformationLimit<T>(lowerLimit, upperLimit);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Scale(T factor) -> TransformationScale<T>&
{
	auto newOp = new TransformationScale<T>(0, 1, 0, factor);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Scale(T input_min, T input_max, T output_min, T output_max) -> TransformationScale<T>&
{
	auto newOp = new TransformationScale<T>(input_min, input_max, output_min, output_max);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Millis() -> TransformationTimestampMillis<T>&
{
	auto newOp = new TransformationTimestampMillis<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Micros() -> TransformationTimestampMicros<T>&
{
	auto newOp = new TransformationTimestampMicros<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ElapsedMillis() -> TransformationElapsedMillis<T>&
{
	auto newOp = new TransformationElapsedMillis<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ElapsedMicros() -> TransformationElapsedMicros<T>&
{
	auto newOp = new TransformationElapsedMicros<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Frequency() -> TransformationFrequency<T>&
{
	auto newOp = new TransformationFrequency<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Threshold(T threshold, int state) -> TransformationThreshold<T>&
{
	auto newOp = new TransformationThreshold<T>(threshold, state);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::DoubleThreshold(T lowThreshold, T highThreshold, int state) -> TransformationThreshold<T>&
{
	auto newOp = new TransformationThreshold<T>(lowThreshold, highThreshold, state);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Toggle(int state) -> TransformationToggle<T>&
{
	auto newOp = new TransformationToggle<T>(state);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::AdcToVoltage(T input_max, T output_max) -> TransformationAdcToVoltage<T>&
{
	auto newOp = new TransformationAdcToVoltage<T>(input_max, output_max);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Split(char separator) -> TransformationSplit<T>&
{
	auto newOp = new TransformationSplit<T>(separator);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Join(char separator) -> TransformationJoin<T>&
{
	auto newOp = new TransformationJoin<T>(separator);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::StringBuffer() -> TransformationStringBuffer<T>&
{
	auto newOp = new TransformationStringBuffer <T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToBool() -> TransformationToBool<T>&
{
	auto newOp = new TransformationToBool<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToInt() -> TransformationCast<T, int>&
{
	auto newOp = new TransformationCast<T, int>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToFloat() -> TransformationCast<T, float>&
{
	auto newOp = new TransformationCast<T, float>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ParseInt() -> TransformationParseInt<T>&
{
	auto newOp = new TransformationParseInt<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ParseFloat() -> TransformationParseFloat<T>&
{
	auto newOp = new TransformationParseFloat<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::OnRising() -> FilterOnRising<T>&
{
	auto newOp = new FilterOnRising<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::OnFalling() -> FilterOnFalling<T>&
{
	auto newOp = new FilterOnFalling<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Median3() -> FilterMedian3<T>&
{
	auto newOp = new FilterMedian3<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Median5() -> FilterMedian5<T>&
{
	auto newOp = new FilterMedian5<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::MovingAverage(size_t N) -> FilterMovingAverage<T>&
{
	auto newOp = new FilterMovingAverage<T>(N);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::MovingRMS(size_t N) -> FilterMovingRMS<T>&
{
	auto newOp = new FilterMovingRMS<T>(N);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::LowPass(const double alpha) -> FilterLowPass<T>&
{
	auto newOp = new FilterLowPass<T>(alpha);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::HighPass(const double alpha) -> FilterHighPass<T>&
{
	auto newOp = new FilterHighPass<T>(alpha);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::StopBand(const double alpha1, const double alpha2) -> FilterStopBand<T>&
{
	auto newOp = new FilterStopBand<T>(alpha1, alpha2);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::PassBand(const double alpha1, const double alpha2) -> FilterPassBand<T>&
{
	auto newOp = new FilterPassBand<T>(alpha1, alpha2);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::DebounceMillis(const unsigned long interval) -> FilterDebounceMillis<T>&
{
	auto newOp = new FilterDebounceMillis<T>(interval);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::DebounceMicros(const unsigned long interval) -> FilterDebounceMicros<T>&
{
	auto newOp = new FilterDebounceMicros<T>(interval);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::WindowMillis(const unsigned long interval) -> FilterWindowMillis<T>&
{
	auto newOp = new FilterWindowMillis<T>(interval);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::WindowMicros(const unsigned long interval) -> FilterWindowMicros<T>&
{
	auto newOp = new FilterWindowMicros<T>(interval);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsLessOrEqual(T value) -> FilterIsLessOrEqual<T>&
{
	auto newOp = new FilterIsLessOrEqual<T>(value);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsLess(T value) -> FilterIsLess<T>&
{
	auto newOp = new FilterIsLess<T>(value);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsGreaterOrEqual(T value) -> FilterIsGreaterOrEqual<T>&
{
	auto newOp = new FilterIsGreaterOrEqual<T>(value);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsGreater(T value) -> FilterIsGreater<T>&
{
	auto newOp = new FilterIsGreater<T>(value);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsNotEqual(T value) -> FilterIsNotEqual<T>&
{
	auto newOp = new FilterIsNotEqual<T>(value);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsEqual(T value) -> FilterIsEqual<T>&
{
	auto newOp = new FilterIsEqual<T>(value);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsNotZero() -> FilterIsNotZero<T>&
{
	auto newOp = new FilterIsNotZero<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::IsZero() -> FilterIsZero<T>&
{
	auto newOp = new FilterIsZero<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Count() -> AggregateCount<T>&
{
	auto newOp = new AggregateCount<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::CountDown(size_t N) -> AggregateCountdown<T>&
{
	auto newOp = new AggregateCountdown<T>(N);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Sum() -> AggregateSum<T>&
{
	auto newOp = new AggregateSum<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Min() -> AggregateMin<T>&
{
	auto newOp = new AggregateMin<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Max() -> AggregateMax<T>&
{
	auto newOp = new AggregateMax<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Average() -> AggregateAverage<T>&
{
	auto newOp = new AggregateAverage<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::RMS() -> AggregateRMS<T>&
{
	auto newOp = new AggregateRMS<T>();
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Any(ReactivePredicate<T> condition) -> AggregateAny<T>&
{
	auto newOp = new AggregateAny<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::All(ReactivePredicate<T> condition) -> AggregateAll<T>&
{
	auto newOp = new AggregateAll<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::None(ReactivePredicate<T> condition) -> AggregateNone<T>&
{
	auto newOp = new AggregateNone<T>(condition);
	Compound(*this, *newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToSerial() -> ObserverSerial<T>
{
	auto newOp = new ObserverSerial<T>();
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Do(ReactiveAction<T> action) -> ObserverDo<T>&
{
	auto newOp = new ObserverDo<T>(action);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::Finally(ReactiveCallback action) -> ObserverFinally<T>&
{
	auto newOp = new ObserverFinally<T>(action);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::DoAndFinally(ReactiveAction<T> doAction, ReactiveCallback finallyAction) -> ObserverDoAndFinally<T>&
{
	auto newOp = new ObserverDoAndFinally<T>(doAction, finallyAction);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::DoNothing() -> ObserverDoNothing<T>&
{
	auto newOp = new ObserverDoNothing<T>();
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToProperty(T& property) -> ObserverProperty<T>&
{
	auto newOp = new ObserverProperty<T>(property);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToArray(T* array, size_t length) -> ObserverArray<T>&
{
	auto newOp = new ObserverArray<T>(array, length);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToCircularBuffer(T* array, size_t length) -> ObserverCircularBuffer<T>&
{
	auto newOp = new ObserverCircularBuffer<T>(array, length);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToDigitalOutput(uint8_t pin) -> ObserverDigitalOutput<T>&
{
	auto newOp = new ObserverDigitalOutput<T>(pin);
	Suscribe(*newOp);
	return *newOp;
}

template <typename T>
auto Observable<T>::ToAnalogOutput(uint8_t pin) -> ObserverAnalogOutput<T>&
{
	auto newOp = new ObserverAnalogOutput<T>(pin);
	Suscribe(*newOp);
	return *newOp;
}
#pragma endregion


/// Operator Base
template <typename Torig, typename Tdest>
class Operator : public  IObserver<Torig>, public  Observable<Tdest>
{
public:
	Observable<Torig>* _parentObservable;
	IObserver<Tdest>* _childObserver;

	void Suscribe(IObserver<Tdest> & observer) override;
	void Reset() override;

protected:
	void OnNext(Torig value) override;
	void OnComplete() override;
};

template <typename Torig, typename Tdest>
void Operator<Torig, Tdest>::Suscribe(IObserver<Tdest> &observer)
{
	this->_childObserver = &observer;
	_parentObservable->Suscribe(*this);
}

template <typename Torig, typename Tdest>
void Operator<Torig, Tdest>::OnNext(Torig value)
{
}

template <typename Torig, typename Tdest>
void Operator<Torig, Tdest>::OnComplete()
{
	if (this->_childObserver != nullptr) this->_childObserver->OnComplete();
}

template<typename Torig, typename Tdest>
void Operator<Torig, Tdest>::Reset()
{
	if(_parentObservable != nullptr) _parentObservable->Reset();
}
#endif