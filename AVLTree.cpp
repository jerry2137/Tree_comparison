#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
	int data;
	Node* left;
	Node* right;
	int height;
	int amount;
};

class Tree
{
public:
	Node* treeRoot;
	Tree();
	int getHeight(Node* N);
	int getAmount(Node* N);
	int max(int a, int b);
	Node* newNode(int data);
	Node* rSwitch(Node* y);
	Node* lSwitch(Node* x);
	int getBalance(Node* N);
	void insert(const int& val);
	Node* insertRecur(Node* node, int data);
	Node* minValueNode(Node* node);
	Node* maxValueNode(Node* node);
	void erase(const int& val);
	Node* eraseRecur(Node* root, int data);
	void order(int num);
	int orderRecur(Node* root, int order);
	void small(int num);
	int smallRecur(Node* n, int pos);
	void find(int num, int ins);
	Node* checkPre(Node* n, Node* pre);
	Node* checkSuc(Node* n, Node* suc);
	Node* nextNode(Node* temp, stack<Node*>& s);
};

Tree::Tree() { treeRoot = nullptr; }

int Tree::getHeight(Node* N)
{
	if (N == nullptr)
		return 0;
	return N->height;
}

int Tree::getAmount(Node* N)
{
	if (N == nullptr)
		return 0;
	return N->amount;
}

int Tree::max(int a, int b) { return (a > b) ? a : b; }

Node* Tree::newNode(int data)
{

	Node* node = new Node();
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;
	node->amount = 1;
	return node;
}

Node* Tree::rSwitch(Node* n)
{
	Node* x = n->left;
	if (!x)
		return nullptr;

	n->left = x->right;
	x->right = n;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	n->amount = getAmount(n->left) + getAmount(n->right) + 1;
	x->amount = getAmount(x->left) + getAmount(x->right) + 1;

	return x;
}

Node* Tree::lSwitch(Node* n)
{
	Node* y = n->right;
	if (!y)
		return nullptr;

	n->right = y->left;
	y->left = n;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	n->amount = getAmount(n->left) + getAmount(n->right) + 1;
	y->amount = getAmount(y->left) + getAmount(y->right) + 1;

	return y;
}

int Tree::getBalance(Node* N)
{
	if (N == nullptr)
		return 0;
	return getHeight(N->left) - getHeight(N->right);
}

void Tree::insert(const int& val)
{
	Node* root = treeRoot;
	treeRoot = insertRecur(root, val);
}

Node* Tree::insertRecur(Node* node, int data)
{
	if (!node)
		return(newNode(data));

	if (data < node->data)
		node->left = insertRecur(node->left, data);
	else if (data >= node->data)
		node->right = insertRecur(node->right, data);

	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	node->amount = 1 + getAmount(node->left) + getAmount(node->right);

	int balance = getBalance(node);

	if (balance > 1 && data < node->left->data)
		return rSwitch(node);

	if (balance < -1 && data > node->right->data)
		return lSwitch(node);

	if (balance > 1 && data > node->left->data)
	{
		node->left = lSwitch(node->left);
		return rSwitch(node);
	}

	if (balance < -1 && data < node->right->data)
	{
		node->right = rSwitch(node->right);
		return lSwitch(node);
	}

	return node;
}

Node* Tree::minValueNode(Node* node)
{
	Node* current = node;
	while (current->left)
		current = current->left;
	return current;
}

Node* Tree::maxValueNode(Node* node)
{
	Node* current = node;
	while (current->right)
		current = current->right;
	return current;
}

void Tree::erase(const int& val)
{
	Node* root = treeRoot;
	treeRoot = eraseRecur(root, val);
	return;
}

Node* Tree::eraseRecur(Node* root, int data)
{
	if (!root)
		return root;

	if (data < root->data)
		root->left = eraseRecur(root->left, data);

	else if (data > root->data)
		root->right = eraseRecur(root->right, data);

	else
	{
		if (!root->left || !root->right)
		{
			Node* temp = root->left ? root->left : root->right;

			if (!temp)
			{
				temp = root;
				root = nullptr;
			}
			else
				*root = *temp;
			delete(temp);
		}
		else
		{
			Node* temp = minValueNode(root->right);

			root->data = temp->data;

			root->right = eraseRecur(root->right,
				temp->data);
		}
	}

	if (!root)
		return root;

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	root->amount = 1 + getAmount(root->left) + getAmount(root->right);

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
		return rSwitch(root);

	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = lSwitch(root->left);
		return rSwitch(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return lSwitch(root);

	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rSwitch(root->right);
		return lSwitch(root);
	}
	return root;
}

void Tree::order(int data)
{
	cout << orderRecur(treeRoot, data) + 1 << endl;
	return;
}

int Tree::orderRecur(Node* n, int data)
{
	if (!n)
		return 0;
	if (n->data < data)
		return getAmount(n->left) + orderRecur(n->right, data) + 1;
	if (n->data >= data)
		return orderRecur(n->left, data);
}

void Tree::small(int pos)
{
	if (treeRoot)
		cout << smallRecur(treeRoot, pos - 1) << endl;
	return;
}

int Tree::smallRecur(Node* n, int pos)
{
	if (!n)
		return NULL;
	if (getAmount(n->left) == pos)
		return n->data;
	if (getAmount(n->left) < pos)
		return smallRecur(n->right, (pos - getAmount(n->left)) - 1);
	if (getAmount(n->left) > pos)
		return smallRecur(n->left, pos);
}

void Tree::find(int num, int ins)
{
	if (!treeRoot)
		return;
	Node* pre = treeRoot;
	Node* suc = treeRoot;
	Node* temp = nullptr;
	while (num != pre->data && num != suc->data)
	{
		if (num < pre->data)
		{
			if (!pre->left)
			{
				cout << pre->data << endl;
				return;
			}
			suc = pre;
			pre = pre->left;
			continue;
		}
		if (num > suc->data)
		{
			if (!suc->right)
			{
				cout << suc->data << endl;
				return;
			}
			pre = suc;
			suc = suc->right;
			continue;
		}
		if (pre->height < suc->height)
		{
			temp = pre->right;
			if (!temp)
			{
				if (ins == -1)
					cout << pre->data << endl;
				if (ins == 1)
					cout << suc->data << endl;
				return;
			}

		}
		if (pre->height > suc->height)
		{
			temp = suc->left;
			if (!temp)
			{
				if (ins == -1)
					cout << pre->data << endl;
				if (ins == 1)
					cout << suc->data << endl;
				return;
			}
		}
		if (num == temp->data)
		{
			if (ins == -1)
			{
				Node* tag = checkPre(temp, temp);
				if (tag)
					cout << tag->data << endl;
				else
					cout << pre->data << endl;
			}
			if (ins == 1)
			{
				Node* tag = checkSuc(temp, temp);
				if (tag)
					cout << tag->data << endl;
				else
					cout << suc->data << endl;
			}
			return;
		}
		else if (num < temp->data)
			suc = temp;
		else if (num > temp->data)
			pre = temp;
	}
	if (ins == -1)
	{
		if (num == pre->data)
			pre = checkPre(pre, pre);
		cout << pre->data << endl;
		return;
	}
	if (ins == 1)
	{
		if (num == suc->data)
			suc = checkSuc(suc, suc);
		cout << suc->data << endl;
		return;
	}
}

Node* Tree::checkPre(Node* n, Node* pre)
{
	if (!n)
		return nullptr;
	if (n->data == pre->data)
		return checkPre(n->left, pre);
	Node* temp = checkPre(n->right, pre);
	if (temp)
		return temp;
	return n;
}

Node* Tree::checkSuc(Node* n, Node* suc)
{
	if (!n)
		return nullptr;
	if (n->data == suc->data)
		return checkSuc(n->right, suc);
	Node* temp = checkSuc(n->left, suc);
	if (temp)
		return temp;
	return n;
}

Node* Tree::nextNode(Node* temp, stack<Node*>& s)
{
	if (temp->right)
	{
		s.push(temp);
		temp = temp->right;
		while (temp->left)
		{
			s.push(temp);
			temp = temp->left;
		}
		return temp;
	}
	else
	{
		while (temp == s.top()->right)
		{
			temp = s.top();
			s.pop();
		}
		temp = s.top();
		s.pop();
		return temp;
	}
}

int main()
{
	Tree* root = new Tree;
	int cases = 0;
	cin >> cases;
	for (int j = 0;j < cases;j++)
	{
		int opt = 0, data = 0;
		cin >> opt >> data;
		switch (opt)
		{
		case 1:
			root->insert(data);
			break;
		case 2:
			root->erase(data);
			break;
		case 3:
			root->order(data);
			break;
		case 4:
			root->small(data);
			break;
		case 5:
			root->find(data, -1);
			break;
		case 6:
			root->find(data, 1);
			break;
		default:
			break;
		}
	}
	return 0;
}