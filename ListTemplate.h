#pragma once
#include <iostream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;
namespace election {
	template<class T>
	class ListT
	{

	private:
		class ListNode
		{
			friend class ListT<T>;
		private:
			ListNode* next;
			ListNode* prev;
			T* _data;
		public:
			ListNode(T* data) :next(nullptr), prev(nullptr), _data(data) {}
			ListNode* getNext() { return next; }
			T* getData() { return _data; }
			~ListNode() = default;
			friend class ListT<T>::Iterator;
		};
		ListNode* head;
		ListNode* tail;
		int _size;


	public:

		ListT() :head(nullptr), tail(nullptr), _size(0)
		{

		}//ctor
		//ListT(const ListT& other);//copy ctor
		~ListT() = default;//dtor

		void setSize() { _size++; }//set
		int& GetSizeOfList() { return _size; }//get

		/***************************Iterator*******************************/
	public:
		class Iterator
		{
			friend class ListT<T>;
		private:
			ListNode* _pNode;
		public:
			friend class ListNode;
			friend class const_iterator;

			using iterator_category = std::bidirectional_iterator_tag;
			// other options exist, e.g., std::forward_iterator_tag
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;
			Iterator(ListNode* pNode) :_pNode(pNode) {}
			Iterator(const Iterator& other) : _pNode(other._pNode) {}
			

			void iterPrint(const T& ds)
			{
				for (auto itr = ds.begin(); itr != ds.end(); ++itr) {
					cout << *itr << " ";
				}
				cout << endl;
			}
			//operators
			Iterator operator++() {
				_pNode = _pNode->next;
				return *this;
			}
			Iterator operator++(int) {
				Iterator temp = *this;
				_pNode = _pNode->next;
				return temp;
			}
			Iterator& operator--() {
				_pNode = _pNode->prev;
				return *this;
			}
			Iterator operator--(int) {
				Iterator temp(*this);
				_pNode = _pNode->prev;
				return temp;
			}

			bool operator==(const Iterator& other) const {
				return _pNode == other._pNode;
			}

			Iterator& operator=(Iterator& other) {
				_pNode = other._pNode;
				return *this;
			}

			bool operator!=(const Iterator& other) const {
				return !(*this == other);
			}
			T* operator*() {
				return _pNode->_data;
			}
			T* operator->() {
				return &(this->_data);
			}


		};
		/***************************Const Iterator*******************************/
		class const_Iterator
		{
		private:
			const ListNode* _pNode;
		public:
			using iterator_category = std::bidirectional_iterator_tag;
			// other options exist, e.g., std::forward_iterator_tag
			using different_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			const_Iterator(const ListNode* _pNode) :_pNode(_pNode) {}

			//operators

			const Iterator& operator=(const Iterator& other) {
				_pNode = other._pNode;
				return *this;
			}
			const T* operator*() {
				return this->_data;
			}
			const T* operator->() {
				return &(this->_data);
			}

		};

		/****************reverse_iterator**********************/
		class reverse_iterator : public Iterator
		{
		public:
			reverse_iterator() {}
			T& operator* ()
			{
				return Iterator::operator*();
			}

			const T& operator* () const
			{
				return Iterator::operator*();
			}

			reverse_iterator& operator++ ()
			{
				this->_pNode = this->_pNode->prev;
				return *this;
			}

			reverse_iterator operator++ (int)
			{
				reverse_iterator old = *this;
				++(*this);
				return old;
			}

			reverse_iterator operator-- ()
			{
				this->_pNode = this->_pNode->next;
				return *this;
			}

			reverse_iterator operator-- (int)
			{
				reverse_iterator old = *this;
				--(*this);
				return old;
			}

		protected:
			reverse_iterator(ListNode* p) : Iterator{ p } {}

			friend class ListT<T>;
		};

		class const_reverse_iterator : public const_Iterator
		{
		public:
			const_reverse_iterator() {}

			const_reverse_iterator operator++ ()
			{
				this->_pNode = this->_pNode->prev;
				return *this;
			}
			const_reverse_iterator operator++ (int)
			{
				const_reverse_iterator old = *this;
				++(*this);
				return old;
			}
			const_reverse_iterator& operator-- ()
			{
				this->_pNode = this->_pNode->next;
				return *this;
			}

			const_reverse_iterator operator-- (int)
			{
				const_reverse_iterator old = *this;
				--(*this);
				return old;
			}

		protected:
			const_reverse_iterator(ListNode* p) : const_Iterator{ p } {}

			friend class ListT<T>;
		};



		Iterator insert(const Iterator& iter, T* data) {
			ListNode* pNewNode = new ListNode(data);

			if (iter == this->end())
			{
				throw "EROR!!!!";
				delete pNewNode;
			}
			pNewNode->next = iter._pNode->next;
			iter._pNode->next->prev = pNewNode;
			pNewNode->prev = iter._pNode;
			iter._pNode->next = pNewNode;

			return Iterator(pNewNode);
		}
		Iterator push_back(T* data)
		{
			ListNode* pNewNode = new ListNode(data);
			if (!head)
				head = tail = pNewNode;
			else
			{
				tail->next = pNewNode;
				pNewNode->prev = tail;
				tail = pNewNode;
			}
			return pNewNode;
		}
		Iterator Tail() { return tail; }
		Iterator begin() { return head; }
		Iterator end() { return nullptr; }
		const_Iterator begin()const { return head; }
		const_Iterator end()const{ return nullptr; }
		Iterator cbegin() { return head; }
		Iterator cend() { return nullptr; }
		const_Iterator cbegin() const noexcept { return head; }
		const_Iterator cend() const noexcept { return nullptr; }


		reverse_iterator rbegin()
		{
			return reverse_iterator{ tail->prev };
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator{ tail->prev };
		}

		reverse_iterator rend()
		{
			return reverse_iterator{ head };
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator{ head };
		}



		Iterator At(const int& index) {
			int i = 0;
			Iterator itr = this->begin();
			while (i < _size)
			{
				if (i == index)
					return itr;
				++i;
				++itr;
			}
		}
		Iterator erase(Iterator& iter)
		{
			ListNode* temp = iter._pNode;
			iter._pNode->prev->next = iter._pNode->next;
			delete temp;
			return ++iter;
		}

		Iterator erase(const Iterator& first, const Iterator& last)
		{
			ListNode* temp = first._pNode;
			while (temp != last._pNode)
			{
				temp = temp->next;
				delete temp->prev;
			}
			return last;

		}

	};
}