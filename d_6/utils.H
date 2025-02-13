#include <vector>
#include <deque>

#include <iostream>


using namespace std;

template <typename T>
class Node 
{
    public:	
	T data;
	Node* next;

	Node(T val) 
	{
		data = val;
		next = nullptr;
	}
};

template <typename T>
class LinkedList
{
    private:

    public:
	Node<T>* head;
	LinkedList() 
	{
		head = nullptr;
	}

	void insertAtHead(T val)
	{
		Node<T>* newNode = new Node<T>(val);
		newNode->next = head;
		head = newNode;
	}

	
	void insertAtEnd(T val)
	{
		Node<T>* newNode = new Node<T>(val);

		if (!head)
		{
			head = newNode;
			return;
		}

		Node<T>* temp = head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}


	void deleteNode(T val)
	{
		if (!head) return;

		if (head->data == val)
		{
			Node<T>* temp = head;
			head = head->next;
			delete temp;

			return;
		}


		Node<T>* temp = head;

		while (temp->next && temp->next->data != val)
		{
			temp=temp->next;
		}

		if (!temp->next)
		{	
			cout << "Value not in array" << endl;
			return;
		}

		Node<T>* nodeToDelete = temp->next;

		temp->next = temp->next->next;

		delete nodeToDelete;
	}

	void display() {
			int count = 0;
        	Node<T>* temp = head;
        	while (temp) {
            	//std::cout << temp->data << " -> ";
            	temp = temp->next;
				count += 1;
        	}
			cout << count << endl;
        	//std::cout << "NULL" << std::endl;
   	 }

	void reverse()
	{
		Node<T>* prev = nullptr;
		Node<T>* curr = head;
		Node<T>* next = nullptr;

		while(curr)
		{
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}
		head = prev;
	}



	~LinkedList()
	{
		Node<T>* temp;

		while(head)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}


};


template <typename T>
struct Particle
{
        T x, y, r;


        bool operator==(const Particle& other) const
        {
            return (x == other.x && y == other.y);
        }
        bool operator!=(const Particle& other) const
        {
            return (x != other.x | y != other.y);
        }
};

template <typename T>
struct Box
{
    T x, y, w, h;

	Box(){};
    
	Box(T _x, T _y, T _w, T _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	bool contains(Particle<T> p)
	{
		return (p.x >= x && p.x <= x+w && p.y >= y && p.y <= y+h);
	}
	bool contains(T px, T py)
	{
		return (px >= x && px <= x+w && py >= y && py <= y+h);
	}

	bool intersects(Box<T> range)
	{
		T q1x = range.x+w;
		T q1y = range.y+h;
		T q2x = range.x;
		T q2y = range.y+h;
		T q3x = range.x;
		T q3y = range.y;
		T q4x = range.x+w;
		T q4y = range.y;

		return (contains(q1x, q1y) || contains(q2x, q2y)
		 || contains(q3x, q3y) || contains(q4x, q4y));
	}


};


template <typename T>
class QuadTree
{
	private:
		static const int CAPACITY = 10;
		Box<T> boundary;
		vector<Particle<T>> particles;
		bool divided = false;
		QuadTree *TL, *TR, *BL, *BR;

	public:
		QuadTree(Box<T> _boundary)
		{
			boundary = _boundary;
			TL = nullptr;
			TR = nullptr;
			BL = nullptr;
			BR = nullptr;
		}

		~QuadTree()
		{
			delete TL;
			delete TR;
			delete BL;
			delete BR;
		}

		void subdivide()
		{
			T x = boundary.x;
			T y = boundary.y;
			T w = boundary.w / 2;
			T h = boundary.h / 2;


			TL = new QuadTree<T>(Box(x, y+h, w, h));
			TR = new QuadTree<T>(Box(x+w, y+h, w, h));
			BL = new QuadTree<T>(Box(x, y, w, h));
			BR = new QuadTree<T>(Box(x+w, y, w, h));

			divided = true;
		}

		bool insert(Particle<T> p)
		{
			if (!boundary.contains(p)) {return false;}

			if (particles.size() < CAPACITY)
			{
				particles.push_back(p);
				return true;
			}
			if (!divided)
			{
				subdivide();
			}
			if (BL->insert(p)) return true;
			if (BR->insert(p)) return true;
			if (TL->insert(p)) return true;
			if (TR->insert(p)) return true;

			return false;
		}

		void query(Box<T> range, vector<Particle<T>> &found)
		{
			if (!boundary.intersects(range)) {return;}

			for (Particle<T> p : particles)
			{
				if (range.contains(p))
				{
					found.push_back(p);
				}
			}

			if (divided)
			{
				BL->query(range, found);
				BR->query(range, found);
				TL->query(range, found);
				TR->query(range, found);
			}
		}


		void print() {
			for (Particle<T> p : particles) {
				cout << "(" << p.x << ", " << p.y << ") " << endl;
			}
			if (divided) {
				BL->print();
				BR->print();
				TL->print();
				TR->print();
			}
		}



};


