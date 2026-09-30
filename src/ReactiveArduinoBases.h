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
class ObserverList
{
public:
  ObserverList();
  ~ObserverList();

  void Add(IObserver<T>*);
  void Remove(IObserver<T>*);
  void RemoveAll();
  bool IsEmpty() const;

  void OnNext(T) const;
  void OnComplete() const;
  
private:
  struct Node
  {
    IObserver<T>* _obj;
    Node *_next;

    Node(IObserver<T>*);
  };

  Node *_head;
  Node *_tail;
};

template <typename T>
ObserverList<T>::Node::Node(IObserver<T>* obj)
{
  _obj = obj;
  _next = nullptr;
}

template <typename T>
ObserverList<T>::ObserverList()
{
  _head = _tail = nullptr;
}

template <typename T>
ObserverList<T>::~ObserverList()
{
	RemoveAll();
}

template <typename T>
void ObserverList<T>::RemoveAll()
{
  Node *node;
  while (_head != nullptr)
  {
    node = _head;
    _head = _head->_next;
    delete node;
  }
}

template <typename T>
void ObserverList<T>::Add(IObserver<T>* obj)
{
  Node *node = new Node(obj);
  if (_head)
  {
    _tail->_next = node;
    _tail = node;
  }
  else
    _head = _tail = node;
}

template <typename T>
void ObserverList<T>::Remove(IObserver<T>* obj)
{
  Node *last = nullptr;
  Node *node = _head;
  while (node != nullptr)
  {
    if (node->_obj == obj)
    {
      if (last)
        last->_next = node->_next;
      else
        _head = node->_next;

      if (_tail == node)
        _tail = last;

      delete node;
    }
    last = node;
    node = node->_next;
  }
}

template <typename T>
bool ObserverList<T>::IsEmpty() const
{
  return _head == nullptr;
}

template <typename T>
void ObserverList<T>::OnNext(T value) const
{
  Node *node = _head;
  while (node != nullptr)
  {
    node->_obj->OnNext(value);
    node = node->_next;
  }
}

template <typename T>
void ObserverList<T>::OnComplete() const
{
  Node *node = _head;
  while (node != nullptr)
  {
    node->_obj->OnComplete();
    node = node->_next;
  }
}

#endif