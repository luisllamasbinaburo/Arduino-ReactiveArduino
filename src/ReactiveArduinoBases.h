/***************************************************
Copyright (c) 2019 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

#ifndef _REACTIVEARDUINOBASES_h
#define _REACTIVEARDUINOBASES_h

using ReactiveCallback = void(*)();

template <typename T>
using ReactiveAction = void(*)(T);

template <typename T>
using ReactiveFunction = T(*)(T);

template <typename T>
using ReactiveCompound = T(*)(T, T);

template <typename Torig, typename Tdest>
using ReactiveMap = Tdest(*)(Torig);

template <typename Torig, typename Tdest>
using ReactiveReduce = Tdest(*)(Tdest, Torig);

template <typename T>
using ReactivePredicate = bool(*)(T);

template <typename T> class IObserver;
template <typename T> class Observable;
template <typename T1, typename T2> class Operator;

template <typename T>
class IObserver
{
public:
	virtual void OnNext(T value) = 0;
	virtual void OnComplete() = 0;

protected:
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual void Subscribe(IObserver<T> &observer) = 0;
	virtual void UnSubscribe(IObserver<T> &observer) = 0;

protected:
	virtual ~IObservable() = default;
};

template <typename T>
class IResetable
{
public:
	virtual void Reset() = 0;
	virtual ~IResetable() = default;

protected:
	bool _isComplete = false;
};

template <typename T>
class ObserverList {
public:
  ObserverList();
  ~ObserverList();

  void Add(IObserver<T>*);
  void Remove(IObserver<T>*);
  void RemoveAll();
  bool IsEmpty() const;

  void Fire(T) const;
  void Complete() const;
  
private:
  struct Node
  {
    IObserver<T>* obj_;
    Node *next_;
  };

  Node *head_;
  Node *tail_;
};

template <typename T>
ObserverList<T>::ObserverList() {
  head_ = tail_ = nullptr;
}

template <typename T>
ObserverList<T>::~ObserverList() {
	RemoveAll();
}

template <typename T>
void ObserverList<T>::RemoveAll() {
  Node *node;
  while (head_ != nullptr) {
    node = head_;
    head_ = head_->next_;
    delete node;
  }
}

template <typename T>
void ObserverList<T>::Add(IObserver<T>* obj) {
  Node *node = new Node();
  node->obj_ = obj;
  node ->next_ = nullptr;
  if (head_)
    tail_ = tail_->next_ = node;
  else
    head_ = tail_ = node;
}

template <typename T>
void ObserverList<T>::Remove(IObserver<T>* obj) {
  Node *last = nullptr;
  Node *node = head_;
  while (node != nullptr) {
    if (node->obj_ == obj) {
      if (last)
        last->next_ = node->next_;
      else
        head_ = node->next_;

      if (tail_ == node)
        tail_ = last;

      delete node;
    }
    last = node;
    node = node->next_;
  }
}

template <typename T>
bool ObserverList<T>::IsEmpty() const {
  return head_ == nullptr;
  }

template <typename T>
void ObserverList<T>::Fire(T value) const {
  Node *node = head_;
  while (node != nullptr) {
    node->obj_->OnNext(value);
    node = node->next_;
  }
}

template <typename T>
void ObserverList<T>::Complete() const {
  Node *node = head_;
  while (node != nullptr) {
    node->obj_->OnComplete();
    node = node->next_;
  }
}

#endif