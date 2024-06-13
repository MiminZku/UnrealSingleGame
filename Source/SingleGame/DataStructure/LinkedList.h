#pragma once
#include <assert.h>

template <typename T>
class ListNode
{
	// List 클래스에서 ListNode 클래스의 private 멤버에 접근 가능하게 함 
	template <typename T>
	friend class LinkedList;
	template <typename T>
	friend class ListIterator;

	typedef ListNode<T> Node;

private:

	ListNode() {}
	ListNode(T data)
	{
		mData = data;
	}
	~ListNode() {}

	T mData;
	Node* mPrev = nullptr;
	Node* mNext = nullptr;

public:

};

template <typename T>
class ListIterator
{
	template <typename T>
	friend class LinkedList;

	typedef LinkedList<T> List;
	typedef ListIterator<T> Iterator;
	typedef ListNode<T> Node;

public:

	ListIterator() {}
	ListIterator(List* l, Node* n)
		: mList(l)
		, mNode(n)
		, bIsValid(false)
	{
		if (nullptr != mList && nullptr != mNode && mList->Begin() != mNode)
		{
			bIsValid = true;
		}
	}
	~ListIterator() {}

	// 역참조 재정의 ( 인자가 있으면 곱하기 )
	T& operator * ()
	{
		return mNode->mData;
	}

	Iterator& operator ++ ()
	{
		if (mList->End() == mNode || !bIsValid)
		{
			assert(nullptr);
		}
		mNode = mNode->mNext;
		return *this;
	}
	Iterator& operator -- ()
	{
		if (mList->Begin() == mNode->mPrev || !bIsValid)
		{
			assert(nullptr);
		}
		mNode = mNode->mPrev;
		return *this;
	}
	// 후위 연산 (괄호 안에 아무 자료형이나 넣으면 됨)
	Iterator& operator ++ (int)
	{
		if (mList->End() == mNode || !bIsValid)
		{
			assert(nullptr);
		}
		Iterator it = new Iterator(*this);
		this->mNode = this->mNode->mNext;
		return it;
	}
	Iterator& operator -- (int)
	{
		if (mList->Begin() == mNode->mPrev || !bIsValid)
		{
			assert(nullptr);
		}
		Iterator it = new Iterator(*this);
		this->mNode = this->mNode->mPrev;
		return it;
	}

	bool operator == (const Iterator& other) const
	{
		return (mList == other.mList && mNode == other.mNode);
	}
	bool operator != (const Iterator& other) const
	{
		return !(*this == other);
	}

	// 컨버전 (ListNode<int>* node = iter) 이런 식의 자동 형변환 가능
	operator Node* ()
	{
		return mNode;
	}

private:

	List* mList = nullptr;
	Node* mNode = nullptr;
	bool	bIsValid;

};

template <typename T>
class LinkedList
{
	typedef ListNode<T> Node;

public:

	typedef ListIterator<T> Iterator;

	LinkedList()
	{
		mHead = new Node;
		mTail = new Node;

		mHead->mNext = mTail;
		mTail->mPrev = mHead;
	}
	~LinkedList()
	{
		Node* temp = mHead;
		while (temp)
		{
			Node* nextNode = temp->mNext;
			delete temp;
			temp = nextNode;
		}
	}

	void PushFront(const T& data);
	void PushBack(const T& data);

	void PopFront();
	void PopBack();

	void Clear();

	int Size() { return mSize; }
	bool Empty() { return 0 == mSize; }

	Iterator& Begin()
	{
		static Iterator iter;
		iter.mList = this;
		iter.mNode = this->mHead->mNext;
		iter.bIsValid = true;
		return iter;
	}
	Iterator& End()
	{
		static Iterator iter;
		iter.mList = this;
		iter.mNode = this->mTail;
		iter.bIsValid = true;
		return iter;
	}
	Iterator Erase(Iterator& iter)
	{
		if (this != iter.mList || End() == iter)
		{
			assert(nullptr);
		}
		--mSize;

		Node* nextNode = iter.mNode->mNext;

		iter.mNode->mPrev->mNext = iter.mNode->mNext;
		iter.mNode->mNext->mPrev = iter.mNode->mPrev;

		delete iter.mNode;

		return Iterator(this, nextNode);
	}
	Iterator Insert(const Iterator& iter, const T& data)
	{
		if (this != iter.mList || End() == iter)
		{
			assert(nullptr);
		}
		++mSize;

		Node* newNode = new Node(data);

		newNode->mPrev = iter.mNode;
		newNode->mNext = iter.mNode->mNext;
		iter.mNode->mNext->mPrev = newNode;
		iter.mNode->mNext = newNode;

		return Iterator(this, newNode);
	}

private:

	Node* mHead = nullptr;
	Node* mTail = nullptr;
	int mSize = 0;
};

template<typename T>
inline void LinkedList<T>::PushFront(const T& data)
{
	mSize++;

	Node* newNode = new Node(data);
	newNode->mPrev = mHead;
	newNode->mNext = mHead->mNext;
	mHead->mNext->mPrev = newNode;
	mHead->mNext = newNode;
}

template<typename T>
inline void LinkedList<T>::PushBack(const T& data)
{
	mSize++;

	Node* newNode = new Node(data);
	newNode->mPrev = mTail->mPrev;
	newNode->mNext = mTail;
	mTail->mPrev->mNext = newNode;
	mTail->mPrev = newNode;
}

template<typename T>
inline void LinkedList<T>::PopFront()
{
	if (0 == mSize)	return;
	mSize--;

	Node* deleteNode = mHead->mNext;
	mHead->mNext = mHead->mNext->mNext;
	mHead->mNext->mPrev = mHead;
	delete deleteNode;
}

template<typename T>
inline void LinkedList<T>::PopBack()
{
	if (0 == mSize)	return;
	mSize--;

	Node* deleteNode = mTail->mPrev;
	mTail->mPrev = mTail->mPrev->mPrev;
	mTail->mPrev->mNext = mTail;
	delete deleteNode;
}

template<typename T>
inline void LinkedList<T>::Clear()
{
	Node* temp = mHead->mNext;
	while (temp != mTail)
	{
		Node* nextNode = temp->mNext;
		delete temp;
		temp = nextNode;
	}

	mHead->mNext = mTail;
	mTail->mPrev = mHead;
	mSize = 0;
}