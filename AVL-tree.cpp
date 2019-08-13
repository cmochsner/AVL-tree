//Program by Christina Ochsner

#include <iostream>

using namespace std;

struct node
{
	int data;
	node *left=NULL;
	node *right=NULL;
	int factor;
};
class AVLtree
{
	private:
		node* root;
	public:
		AVLtree()
		{
			root = NULL;
		}
		bool isEmpty()
		{
			if (root == NULL)
			{
				return true;
			}
			return false;
		}
		int height(node* curr)
		{
			if (curr == NULL)
			{
				return 0;
			}
			else
			{
				int l = height(curr->left);
				int r = height(curr->right);

				if (l > r)
				{
					return(l + 1);
				}
				else
				{
					return(r + 1);
				}
			}
		}
		int max(int x, int y)
		{
			if (x >= y)
			{
				return x;
			}
			return y;
		}
		int balancef(node *n)
		{
			if (n == NULL)
			{
				return 0;
			}
			return height(n->left) - height(n->right);
		}
		node *rotateRight(node *n)
		{
			node *newroot = n->left;
			node *temp = newroot->right;

			newroot->right = n;
			n->left = temp;

			newroot->factor = balancef(newroot);
			n->factor = balancef(n);

			return newroot;
		}
		node *rotateLeft(node *n)
		{
			node *newroot = n->right;
			node *temp = newroot->left;

			newroot->left = n;
			n->right = temp;

			n->factor = balancef(n);
			newroot->factor = balancef(newroot);

			return newroot;
		}
		node* inserts(node* n, int key)
		{
			if (n == NULL)
			{
				node* newnode = new node;
				newnode->data = key;
				newnode->factor = balancef(n);

				return newnode;
			}
			if (key < n->data)
			{
				n->left = inserts(n->left, key);
			}
			else if (key > n->data)
			{
				n->right = inserts(n->right, key);
			}
			else
			{
				return n;
			}

			n->factor = balancef(n);

			if (n->factor > 1 && key < n->left->data)
			{
				return rotateRight(n);
			}
			if (n->factor < -1 && key > n->right->data)
			{
				return rotateLeft(n);
			}
			if (n->factor > 1 && key > n->left->data)
			{
				n->left = rotateLeft(n->left);
				return rotateRight(n);
			}
			if (n->factor < -1 && key < n->right->data)
			{
				n->right = rotateRight(n->right);
				return rotateLeft(n);
			}

			return n;
		}
		void insert(int key)
		{
			root = inserts(root, key);
		}
		void postorder(node *n)
		{
			if (n != NULL)
			{
				postorder(n->left);
				postorder(n->right);
				cout << n->data << " ";
			}
		}
		void inorder(node *n)
		{
			if (n != NULL)
			{
				inorder(n->left);
				cout << n->data << " ";
				inorder(n->right);
			}
		}
		void preorder(node *n)
		{
			if (n != NULL)
			{
				cout<<n->data<<" ";
				preorder(n->left);
				preorder(n->right);
			}
		}
		void print(int type)
		{
			switch (type)
			{
				case 1:
					preorder(root);
					break;
				case 2:
					inorder(root);
					break;
				case 3:
					postorder(root);
					break;
				default:
					cout << "Invalid entry.";
					break;
			}
			cout << endl;
		}
};


int main()
{
	cout << "Welcome to the AVL tree program!" << endl;
	
	AVLtree t;
	int choice = 0;

	while (choice != 3)
	{
		cout << "\n1: Insert a number into the AVL tree." << endl;
		cout << "2: Print the AVL tree." << endl;
		cout << "3: Exit the program" << endl;

		cin >> choice;

		if (choice == 3)
		{
			continue;
		}

		switch (choice)
		{
			case 1:
			{
				int num;
				cout << "\nEnter the number you'd like to add: ";
				cin >> num;
				t.insert(num);
			}
			break;
			case 2:
			{
				int type;
				cout << "How would like to print your tree? Insert the # for your choice." << endl;
				cout << "1: Preorder Traversal, 2: Inorder Traversal, 3: Postorder Traversal" << endl;
				cin >> type;
				while (type < 1 || type>3)
				{
					cout << "Invalid choice. Try again." << endl;
					cin >> type;
				}
				t.print(type);
			}
			break;
			default:
			{
				cout << "Invalid choice. Try again." << endl;
				cin >> choice;
			}
			break;
		}
	}

	return 0;
}
