#include <iostream>


using namespace std;

class Node 
{
     public:	
	int data;
	Node* next;

	Node(int val) 
	{
		data = val;
		next = nullptr;
	}
};


class LinkedList
{
    private:
	Node* head;

    public:
	LinkedList() 
	{
		head = nullptr;
	}

	void insertAtHead(int val)
	{
		Node* newNode = new Node(val);
		newNode->next = head;
		head = newNode;
	}

	
	void insertAtEnd(int val)
	{
		Node* newNode = new Node(val);

		if (!head)
		{
			head = newNode;
			return;
		}

		Node* temp = head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}


	void deleteNode(int val)
	{
		if (!head) return;

		if (head->data == val)
		{
			Node* temp = head;
			head = head->next;
			delete temp;

			return;
		}


		Node* temp = head;

		while (temp->next && temp->next->data != val)
		{
			temp=temp->next;
		}

		if (!temp->next)
		{	
			cout << "Value not in array" << endl;
			return;
		}

		Node* nodeToDelete = temp->next;

		temp->next = temp->next->next;

		delete nodeToDelete;
	}

	void display() {
        	Node* temp = head;
        	while (temp) {
            	std::cout << temp->data << " -> ";
            	temp = temp->next;
        	}
        	std::cout << "NULL" << std::endl;
   	 }

	void reverse()
	{
		Node* prev = nullptr;
		Node* curr = head;
		Node* next = nullptr;

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
		Node* temp;

		while(head)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}


};

int main()
{

	LinkedList list;

	list.insertAtEnd(1);
	list.insertAtEnd(2);
	list.insertAtEnd(4);
	list.insertAtEnd(8);
	list.insertAtEnd(16);
	list.insertAtEnd(32);
	list.insertAtEnd(64);

	list.display();

	list.insertAtHead(0);

	list.display();

	list.deleteNode(16);

	list.display();

	list.reverse();

	list.display();


}	


	void addParticles_noRecursion(LinkedList<Particle>& particles, int maxParts)
	{

		if (!particles.head->next){cout<<"All particles sorted!" << endl;return;}
		int count = 0;
		Node<Particle>* temp = particles.head;
		Box box = tree[0];
		vector<Particle> to_remove;

		while (particles.size() != 1)
		{
		temp = particles.head;
		box = tree[0];
		while (temp)
		{
			Particle part = temp->data;
			if (part.x < box.x_u && part.x > box.x_l && part.y < box.y_u && part.y > box.y_l)
			{

				if (count == maxParts)
				{
					spawnChildren();
					to_remove = vector<Particle>();
					count = 0;
					temp = particles.head;
					box = tree[0];
					cout << box.x_l << endl;
				}

				else
				{
					count+=1;
					to_remove.push_back(part);
					temp = temp->next;
				}

				}
			else
			{
				temp = temp->next;
			}
			
		}

		for (const Particle& p : to_remove)
		{
        	particles.deleteNode(p);
		 }
		tree.pop_front();
		to_remove = vector<Particle>();

		}


	}

