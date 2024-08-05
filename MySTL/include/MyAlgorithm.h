#ifndef ALGORITM_H
#define ALGORITM_H
#include "MyVector.h"
#include "MyList.h"
#include "MyForward_list.h"


namespace myStd
{
	// find()

	template <typename T>
	typename myStd::MyVector<T>::iterator find(typename myStd::MyVector<T>::iterator beginIt, typename myStd::MyVector<T>::iterator endIt, T value)
	{
		for (typename myStd::MyVector<T>::iterator it = beginIt; it != endIt; it++) {
			if (*it == value) {
				return it;
			}
		}
		return nullptr;
	}

	template <typename T>
	typename myStd::MyList<T>::iterator find(typename myStd::MyList<T>::iterator beginIt, typename myStd::MyList<T>::iterator endIt, T value)
	{
		for (typename myStd::MyList<T>::iterator it = beginIt; it != endIt; it++) {
			if (*it == value) {
				return it;
			}
		}
		return nullptr;
	}

	template <typename T>
	typename myStd::MyForward_list<T>::iterator find(typename myStd::MyForward_list<T>::iterator beginIt, typename myStd::MyForward_list<T>::iterator endIt, T value)
	{
		for (typename myStd::MyForward_list<T>::iterator it = beginIt; it != endIt; it++) {
			if (*it == value) {
				return it;
			}
		}
		return nullptr;
	}

	// sort<>()

	template <typename T>
	void sort(typename myStd::MyVector<T>::iterator beginIt, typename myStd::MyVector<T>::iterator endIt)
	{
		for (typename myStd::MyVector<T>::iterator it = beginIt; it != endIt - 1; it++) {
			for (typename myStd::MyVector<T>::iterator it2 = it + 1; it2 != endIt; it2++) {
				if (*it > *it2) {
					T temp = *it;
					*it = *it2;
					*it2 = temp;
				}
			}
		}
	}

	template <typename T>
	void sort(typename myStd::MyList<T>::iterator beginIt, typename myStd::MyList<T>::iterator endIt)
	{
		for (typename myStd::MyList<T>::iterator it = beginIt; it != endIt - 1; it++) {
			for (typename myStd::MyList<T>::iterator it2 = it + 1; it2 != endIt; it2++) {
				if (*it > *it2) {
					T temp = *it;
					*it = *it2;
					*it2 = temp;
				}
			}
		}
	}

	template <typename T>
	void sort(typename myStd::MyForward_list<T>::iterator beginIt, typename myStd::MyForward_list<T>::iterator endIt)
	{
		for (typename myStd::MyForward_list<T>::iterator it = beginIt; it != endIt - 1; it++) {
			for (typename myStd::MyForward_list<T>::iterator it2 = it + 1; it2 != endIt; it2++) {
				if (*it > *it2) {
					T temp = *it;
					*it = *it2;
					*it2 = temp;
				}
			}
		}
	}

	// rotate<>()

	template <typename T>
	void rotate(typename myStd::MyVector<T>::iterator beginIt, typename myStd::MyVector<T>::iterator beginItSecond, typename myStd::MyVector<T>::iterator endIt)
	{
		typename myStd::MyVector<T> arr;

		for (typename myStd::MyVector<T>::iterator it = beginIt; it != beginItSecond; it++) {
			arr.push_back(*it);
		}

		int i = 0;
		for (typename myStd::MyVector<T>::iterator it = beginIt; it != endIt; it++) {
			if (beginItSecond == endIt) {
				*it = arr.at(i);
				i++;
			}
			else {
				*it = *beginItSecond;
				beginItSecond++;
			}
		}
	}

	template <typename T>
	void rotate(typename myStd::MyList<T>::iterator beginIt, typename myStd::MyList<T>::iterator beginItSecond, typename myStd::MyList<T>::iterator endIt)
	{
		typename myStd::MyVector<T> arr;

		for (typename myStd::MyList<T>::iterator it = beginIt; it != beginItSecond; it++) {
			arr.push_back(*it);
		}

		int i = 0;
		typename myStd::MyList<T>::iterator it = beginIt;
		bool f = true;
		for (it = beginIt; it != endIt; it++) {
			if (beginItSecond == endIt) {
				if (f) {
					*it = *beginItSecond;
					f = false;
					continue;
				}
				*it = arr.at(i);
				i++;
			}
			else {
				*it = *beginItSecond;
				beginItSecond++;
			}
		}
		*it = arr.at(i);
	}

	template <typename T>
	void rotate(typename myStd::MyForward_list<T>::iterator beginIt, typename myStd::MyForward_list<T>::iterator beginItSecond, typename myStd::MyForward_list<T>::iterator endIt)
	{
		typename myStd::MyVector<T> arr;

		for (typename myStd::MyForward_list<T>::iterator it = beginIt; it != beginItSecond; it++) {
			arr.push_back(*it);
		}

		int i = 0;
		typename myStd::MyForward_list<T>::iterator it = beginIt;
		bool f = true;
		for (it = beginIt; it != endIt; it++) {
			if (beginItSecond == endIt) {
				if (f) {
					*it = *beginItSecond;
					f = false;
					continue;
				}
				*it = arr.at(i);
				i++;
			}
			else {
				*it = *beginItSecond;
				beginItSecond++;
			}
		}
		*it = arr.at(i);
	}

	// copy<>()

	template <typename T>
	void copy(typename myStd::MyVector<T>::iterator beginIt, typename myStd::MyVector<T>::iterator endIt, typename myStd::MyVector<T>::iterator beginItSecond)
	{
		for (typename myStd::MyVector<T>::iterator it = beginIt, it2 = beginItSecond; it != endIt; it++, it2++) {
			*it2 = *it;
		}
	}

	template <typename T>
	void copy(typename myStd::MyList<T>::iterator beginIt, typename myStd::MyList<T>::iterator endIt, typename myStd::MyList<T>::iterator beginItSecond)
	{
		for (typename myStd::MyList<T>::iterator it = beginIt, it2 = beginItSecond; it != endIt; it++, it2++) {
			*it2 = *it;
		}
	}

	template <typename T>
	void copy(typename myStd::MyForward_list<T>::iterator beginIt, typename myStd::MyForward_list<T>::iterator endIt, typename myStd::MyForward_list<T>::iterator beginItSecond)
	{
		for (typename myStd::MyForward_list<T>::iterator it = beginIt, it2 = beginItSecond; it != endIt; it++, it2++) {
			*it2 = *it;
		}
	}


	// remove<>()
}

#endif