#include <vector>
#include <deque>

#include <iostream>


using namespace std;


/*
Full construction of quadtree data type for future particle rendering and collision detection

*/

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

struct Particle
{
        float x, y, r;


        bool operator==(const Particle& other) const
        {
            return (x == other.x && y == other.y);
        }
        bool operator!=(const Particle& other) const
        {
            return (x != other.x | y != other.y);
        }
};

struct Box
{
    float x_u, x_l, y_u, y_l;
    vector<Box*> children;
    vector<Particle> vals;

    bool operator==(const Box& other) const
        {
            return (x_u == other.x_u && y_u == other.y_u &&
                    x_l == other.x_l && y_l == other.y_l);
        }
    bool operator!=(const Box& other) const
        {
            return (x_u != other.x_u || y_u != other.y_u ||
                    x_l != other.x_l || y_l != other.y_l);
        }
};

template <typename T>
struct QuadTree
{
	//LinkedList<T> searchList;
	LinkedList<T> tree;
	deque<Box> quadtree;
	int partCount = 0;

	QuadTree(T node)
	{
		tree.insertAtHead(node);
		quadtree.push_front(node);
	}



	void spawnChildren()
	{

		Box box = tree.head->data;

		Box LB, RB, LT, RT;

		LB.x_u = box.x_u - ((box.x_u - box.x_l) / 2);
		LB.x_l = box.x_l;
		LB.y_u = box.y_u - ((box.y_u - box.y_l)/ 2);
		LB.y_l = box.y_l;

		LT.x_u = box.x_u - ((box.x_u - box.x_l) / 2);
		LT.x_l = box.x_l;
		LT.y_l = box.y_l + ((box.y_u - box.y_l)/ 2);
		LT.y_u = box.y_u;

		RB.x_u = box.x_u;
		RB.x_l = box.x_l + ((box.x_u - box.x_l)/2);
		RB.y_u = box.y_u - ((box.y_u - box.y_l)/2);
		RB.y_l = box.y_l;

		RT.x_u = box.x_u;
		RT.x_l = box.x_l + ((box.x_u - box.x_l)/2);
		RT.y_l = box.y_l + ((box.y_u - box.y_l)/2);
		RT.y_u = box.y_u;


		quadtree.push_front(LB);
		quadtree.push_front(LT);
		quadtree.push_front(RB);
		quadtree.push_front(RT);

		quadtree[4].children.push_back(&quadtree[0]);
		quadtree[4].children.push_back(&quadtree[1]);
		quadtree[4].children.push_back(&quadtree[2]);
		quadtree[4].children.push_back(&quadtree[3]);

		tree.insertAtHead(LB);
		tree.insertAtHead(LT);
		tree.insertAtHead(RB);
		tree.insertAtHead(RT);


	}



	void addParticles(LinkedList<Particle>& particles, int maxParts)
	{

		if (!particles.head->next){cout<<"All particles sorted!" << endl;return;}
		int count = 0;
		partCount+=1;
		Node<Particle>* temp = particles.head;
		Box box = tree.head->data;
		vector<Particle> to_remove;
		while (temp)
		{
			Particle part = temp->data;
			if (part.x < box.x_u && part.x > box.x_l)
			{

				if (part.y < box.y_u && part.y > box.y_l)
				{
					count+=1;
					if (count > maxParts)
					{
						spawnChildren();
						box.vals = vector<Particle>();
						temp = particles.head;
						addParticles(particles,maxParts);

						return;

					}

					box.vals.push_back(part);
					to_remove.push_back(part);


				}
			}
			temp = temp->next;
		}

		for (const Particle& p : to_remove)
		{
        	particles.deleteNode(p);
		 }

		tree.deleteNode(box);
		addParticles(particles, maxParts);

	}


};