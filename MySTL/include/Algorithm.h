#pragma
#include "Vector.h"
#include "List.h"
#include "Forward_list.h"


namespace myStd
{
	// find()

	template <typename T>
	typename myStd::Vector<T>::iterator find(typename myStd::Vector<T>::iterator beginIt, typename myStd::Vector<T>::iterator endIt, T value)
	{
		for (typename myStd::Vector<T>::iterator it = beginIt; it != endIt; it++) {
			if (*it == value) {
				return it;
			}
		}
		return nullptr;
	}

	template <typename T>
	typename myStd::List<T>::iterator find(typename myStd::List<T>::iterator beginIt, typename myStd::List<T>::iterator endIt, T value)
	{
		for (typename myStd::List<T>::iterator it = beginIt; it != endIt; it++) {
			if (*it == value) {
				return it;
			}
		}
		return nullptr;
	}

	template <typename T>
	typename myStd::Forward_list<T>::iterator find(typename myStd::Forward_list<T>::iterator beginIt, typename myStd::Forward_list<T>::iterator endIt, T value)
	{
		for (typename myStd::Forward_list<T>::iterator it = beginIt; it != endIt; it++) {
			if (*it == value) {
				return it;
			}
		}
		return nullptr;
	}

	// sort<>()

	template <typename T>
	void sort(typename myStd::Vector<T>::iterator beginIt, typename myStd::Vector<T>::iterator endIt)
	{
		for (typename myStd::Vector<T>::iterator it = beginIt; it != endIt - 1; it++) {
			for (typename myStd::Vector<T>::iterator it2 = it + 1; it2 != endIt; it2++) {
				if (*it > *it2) {
					T temp = *it;
					*it = *it2;
					*it2 = temp;
				}
			}
		}
	}

	template <typename T>
	void sort(typename myStd::List<T>::iterator beginIt, typename myStd::List<T>::iterator endIt)
	{
		for (typename myStd::List<T>::iterator it = beginIt; it != endIt - 1; it++) {
			for (typename myStd::List<T>::iterator it2 = it + 1; it2 != endIt; it2++) {
				if (*it > *it2) {
					T temp = *it;
					*it = *it2;
					*it2 = temp;
				}
			}
		}
	}

	template <typename T>
	void sort(typename myStd::Forward_list<T>::iterator beginIt, typename myStd::Forward_list<T>::iterator endIt)
	{
		for (typename myStd::Forward_list<T>::iterator it = beginIt; it != endIt - 1; it++) {
			for (typename myStd::Forward_list<T>::iterator it2 = it + 1; it2 != endIt; it2++) {
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
	void rotate(typename myStd::Vector<T>::iterator beginIt, typename myStd::Vector<T>::iterator beginItSecond, typename myStd::Vector<T>::iterator endIt)
	{
		typename myStd::Vector<T> arr;

		for (typename myStd::Vector<T>::iterator it = beginIt; it != beginItSecond; it++) {
			arr.push_back(*it);
		}

		int i = 0;
		for (typename myStd::Vector<T>::iterator it = beginIt; it != endIt; it++) {
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
	void rotate(typename myStd::List<T>::iterator beginIt, typename myStd::List<T>::iterator beginItSecond, typename myStd::List<T>::iterator endIt)
	{
		typename myStd::Vector<T> arr;

		for (typename myStd::List<T>::iterator it = beginIt; it != beginItSecond; it++) {
			arr.push_back(*it);
		}

		int i = 0;
		typename myStd::List<T>::iterator it = beginIt;
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
	void rotate(typename myStd::Forward_list<T>::iterator beginIt, typename myStd::Forward_list<T>::iterator beginItSecond, typename myStd::Forward_list<T>::iterator endIt)
	{
		typename myStd::Vector<T> arr;

		for (typename myStd::Forward_list<T>::iterator it = beginIt; it != beginItSecond; it++) {
			arr.push_back(*it);
		}

		int i = 0;
		typename myStd::Forward_list<T>::iterator it = beginIt;
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
	void copy(typename myStd::Vector<T>::iterator beginIt, typename myStd::Vector<T>::iterator endIt, typename myStd::Vector<T>::iterator beginItSecond)
	{
		for (typename myStd::Vector<T>::iterator it = beginIt, it2 = beginItSecond; it != endIt; it++, it2++) {
			*it2 = *it;
		}
	}

	template <typename T>
	void copy(typename myStd::List<T>::iterator beginIt, typename myStd::List<T>::iterator endIt, typename myStd::List<T>::iterator beginItSecond)
	{
		for (typename myStd::List<T>::iterator it = beginIt, it2 = beginItSecond; it != endIt; it++, it2++) {
			*it2 = *it;
		}
	}

	template <typename T>
	void copy(typename myStd::Forward_list<T>::iterator beginIt, typename myStd::Forward_list<T>::iterator endIt, typename myStd::Forward_list<T>::iterator beginItSecond)
	{
		for (typename myStd::Forward_list<T>::iterator it = beginIt, it2 = beginItSecond; it != endIt; it++, it2++) {
			*it2 = *it;
		}
	}
}