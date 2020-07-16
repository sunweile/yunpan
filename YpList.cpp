#include "YpList.h"
#pragma execution_character_set("utf-8")
template<class T>
YpList<T>::YpList() {
	this->lenght = 0;
	this->baseSize = 0;
	this->list = newBaseList();
	this->list->len = 0;
}
template<class T>
YpList<T>::~YpList() {
	for (int i = 0; i < lenght; ++i) {
		T t = this->at(i);
		if (t != NULL) {
			delete t;
		}
	}
	YpList<T>::BaseList nextList[baseSize];
	YpList<T>::BaseList next = this->list;
	int i = baseSize;
	while (next != NULL){
		nextList[--i] = next
		next = next->next;
	}
	for (; i < baseSize; ++i) {
		delete nextList[i];
	}
}

template<class T>
T YpList<T>::at(int i) {
	if (i < 0 || i >= lenght) {
		return NULL;
	}
	int t = i / MAX_BASE_SIAE;
	int j = i % MAX_BASE_SIAE;
	YpList<T>::BaseList next = this->list;
	while (t > 0) {
		next = next->next;
		t--;
	}
	return next[j - 1];
}

template<class T>
int YpList<T>::size() {
	return lenght;
}

template<class T>
void YpList<T>::pushBack(T t) {
	int l = lenght / MAX_BASE_SIAE;
	int j = lenght % MAX_BASE_SIAE;
	YpList<T>::BaseList next = this->list;
	while (l > 0) {
		next = next->next;
		if (next == NULL) {
			this->newBaseList();
			next = next->next;
		}
		l--;
	}
	next[j] = t;
	next->len++;
}

template<class T>
typename YpList<T>::BaseList YpList<T>::newBaseList() {
	this->baseSize++;
	YpList<T>::BaseList next = this->list;
	while (next != NULL && next->next != NULL) {
		next = next->next;
	}
	YpList<T>::BaseList n = new YpList<T>::List();
	n->len = 0;
	n->next = NULL;
	if (next != NULL) {
		next->next = n;
	}
	return n;
}

template<class T>
bool YpList<T>::push(int i, T t) {
	if (i < 0 || i > lenght) {
		return false;
	}
	if (i == lenght) {
		pushBack(t);
		return true;
	}
	int l = i / MAX_BASE_SIAE;
	int j = i % MAX_BASE_SIAE;
	YpList<T>::BaseList next = this->list;
	while (l > 0) {
		next = next->next;
		if (next == NULL) {
			this->newBaseList();
			next = next->next;
		}
		l--;
	}
	if (next->len < MAX_BASE_SIAE) {
		int len = next->len;
		while (--len != j) {
			next[len + 1] = next[len]
		}
		next[j] = t;
		next->len++;
	}else {
		T t1 = next[MAX_BASE_SIAE-1];
		int len = next->len-1;
		while (--len != j) {
			next[len + 1] = next[len]
		}
		next[j] = t;
		return push((l + 1) * MAX_BASE_SIAE, t1);
	}

}
template<class T>
void YpList<T>::clear() {
	for (int i = 0; i < lenght; ++i) {
		T t = this->at(i);
		if (t != NULL) {
			delete t;
		}
	}
	YpList<T>::BaseList nextList[baseSize];
	YpList<T>::BaseList next = this->list;
	int i = baseSize;
	while (next != NULL) {
		nextList[--i] = next
			next = next->next;
	}
	for (; i < baseSize; ++i) {
		delete nextList[i];
	}
	this->lenght = 0;
	this->baseSize = 0;
	this->list = newBaseList();
	this->list->len = 0;
}

template<class T>
void YpList<T>::replace(int i, T t) {
	if (i < 0 || i >= lenght) {
		return;
	}
	int l = i / MAX_BASE_SIAE;
	int j = i % MAX_BASE_SIAE;
	YpList<T>::BaseList next = this->list;
	while (l > 0) {
		next = next->next;
		l--;
	}
	delete next[j];
	next[j] = t;
}

template<class T>
void YpList<T>::remove(int i) {
	replace(i,NULL);
}

template<class T>
T YpList<T>::last() {
	return at(lenght-1)
}

template<class T>
T YpList<T>::first() {
	return at(0);
}
