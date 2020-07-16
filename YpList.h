#pragma once
#define MAX_BASE_SIAE 10
#pragma execution_character_set("utf-8")



template<class T>
class YpList
{
public:
	YpList();
	~YpList();
	T at(int);
	int size();
	void pushBack(T);
	void clear();
	bool push(int, T);
	void replace(int, T);
	void remove(int);
	T last();
	T first();

private:
	typedef struct List{
		T baseList[MAX_BASE_SIAE];
		int len;
		struct List* next;
	} *BaseList;
	int lenght;
	int baseSize;
	BaseList list;

	BaseList newBaseList();


};

