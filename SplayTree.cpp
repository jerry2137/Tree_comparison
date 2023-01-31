#include <iostream>
using namespace std;

class Node
{
public:
	int data;
	Node* left;
	Node* right;
	Node* parent;
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
	Node* newNode(int data, Node* p);
	void rSwitch(Node* n);
	void lSwitch(Node* n);
	void splay(Node* n);
	void insert(const int& val);
	Node* minValueNode(Node* node);
	void erase(const int& val);
	void order(int num);
	int orderRecur(Node* root, int order);
	void small(int num);
	Node* smallRecur(Node* n, int pos);
	Node* find(int num, int ins);
	Node* checkPre(Node* n, Node* pre);
	Node* checkSuc(Node* n, Node* suc);
	void inorder(Node* n);
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

Node* Tree::newNode(int data, Node* p)
{

	Node* node = new Node();
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;
	node->parent = p;
	node->height = 1;
	node->amount = 1;
	return node;
}

void Tree::rSwitch(Node* n)
{
	Node* x = n->left;
	Node* temp = x->right;
	Node* p = n->parent;

	if (temp)
		temp->parent = n;
	x->parent = p;
	if (p)
	{
		if (n == p->right)
			p->right = x;
		else
			p->left = x;
	}

	x->right = n;
	n->left = temp;
	n->parent = x;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

	n->amount = getAmount(n->left) + getAmount(n->right) + 1;
	x->amount = getAmount(x->left) + getAmount(x->right) + 1;

	if (!p)
		treeRoot = x;
}

void Tree::lSwitch(Node* n)
{
	Node* y = n->right;
	Node* temp = y->left;
	Node* p = n->parent;

	if (temp)
		temp->parent = n;
	y->parent = p;
	if (p)
	{
		if (n == p->right)
			p->right = y;
		else
			p->left = y;
	}

	y->left = n;
	n->right = temp;
	n->parent = y;

	n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	n->amount = getAmount(n->left) + getAmount(n->right) + 1;
	y->amount = getAmount(y->left) + getAmount(y->right) + 1;

	if (!p)
		treeRoot = y;
}

void Tree::splay(Node* n)
{
	if (!n)
		return;
	while (n->parent)
	{
		if (!n->parent->parent)
		{
			if (n == n->parent->right)
				lSwitch(n->parent);
			else
				rSwitch(n->parent);
			return;
		}
		if (n == n->parent->right)
		{
			if (n->parent == n->parent->parent->right)
			{
				lSwitch(n->parent->parent);
				lSwitch(n->parent);
			}
			else
			{
				lSwitch(n->parent);
				rSwitch(n->parent);
			}
		}
		else
		{
			if (n->parent == n->parent->parent->right)
			{
				rSwitch(n->parent);
				lSwitch(n->parent);
			}
			else
			{
				rSwitch(n->parent->parent);
				rSwitch(n->parent);
			}
		}

	}
}

void Tree::insert(const int& val)
{
	if (!treeRoot)
	{
		treeRoot = newNode(val, nullptr);
		return;
	}

	Node* n = treeRoot;
	Node* temp = nullptr;

	while (n)
	{
		temp = n;
		if (val < n->data)
			n = n->left;
		else
			n = n->right;
	}
	n = newNode(val, temp);
	if (n->data < temp->data)
		temp->left = n;
	else
		temp->right = n;
	splay(n);
}

Node* Tree::minValueNode(Node* node)
{
	if (!node)
		return nullptr;
	Node* current = node;
	while (current->left)
		current = current->left;
	return current;
}

void Tree::erase(const int& val)
{
	Node* n = find(val, 0);
	if (!n)
		return;
	splay(n);
	if (!n->left || !n->right)
	{
		Node* temp = n->left ? n->left : n->right;

		if (!temp)
			treeRoot = nullptr;
		else
		{
			treeRoot = temp;
			temp->parent = nullptr;
		}
		delete(n);
	}
	else
	{
		Node* temp = minValueNode(n->right);
		Node* r = temp->right;
		Node* p = temp->parent;

		if (temp->parent != n)
		{
			temp->parent->left = r;
			if (r)
				r->parent = temp->parent;
			temp->right = n->right;
			temp->right->parent = temp;
		}
		treeRoot = temp;
		temp->parent = nullptr;
		temp->left = n->left;
		temp->left->parent = temp;
		if (p == n)
			p = temp;
		while (p)
		{
			p->height = 1 + max(getHeight(p->left), getHeight(p->right));
			p->amount = 1 + getAmount(p->left) + getAmount(p->right);
			p = p->parent;
		}
	}
	return;
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
	Node* temp = smallRecur(treeRoot, pos - 1);
	if (!temp)
		return;
	cout << temp->data << endl;
	splay(temp);
	return;
}

Node* Tree::smallRecur(Node* n, int pos)
{
	if (!n)
		return nullptr;
	if (getAmount(n->left) == pos)
		return n;
	if (getAmount(n->left) < pos)
		return smallRecur(n->right, (pos - getAmount(n->left)) - 1);
	if (getAmount(n->left) > pos)
		return smallRecur(n->left, pos);
}

Node* Tree::find(int num, int ins)
{
	if (!treeRoot)
		return nullptr;
	Node* pre = treeRoot;
	Node* suc = treeRoot;
	Node* temp = nullptr;
	while (num != pre->data && num != suc->data)
	{
		if (num < pre->data)
		{
			if (!pre->left)
			{
				if (ins == 1)
				{
					cout << pre->data << endl;
					splay(pre);
				}
				return nullptr;
			}
			suc = pre;
			pre = pre->left;
			continue;
		}
		if (num > suc->data)
		{
			if (!suc->right)
			{
				if (ins == -1)
				{
					cout << suc->data << endl;
					splay(suc);
				}
				return nullptr;
			}
			pre = suc;
			suc = suc->right;
			continue;
		}
		if (pre->height < suc->height)
			temp = pre->right;
		if (pre->height > suc->height)
			temp = suc->left;
		if (!temp)
		{
			if (ins == -1)
			{
				cout << pre->data << endl;
				splay(pre);
			}
			if (ins == 1)
			{
				cout << suc->data << endl;
				splay(suc);
			}
			return nullptr;
		}
		if (num == temp->data)
		{
			if (ins == 0)
				return temp;
			if (ins == -1)
			{
				Node* tag = checkPre(temp, temp);
				if (tag)
				{
					cout << tag->data << endl;
					splay(tag);
				}
				else
				{
					cout << pre->data << endl;
					splay(pre);
				}
			}
			if (ins == 1)
			{
				Node* tag = checkSuc(temp, temp);
				if (tag)
				{
					cout << tag->data << endl;
					splay(tag);
				}
				else
				{
					cout << suc->data << endl;
					splay(suc);
				}
			}
			return nullptr;
		}
		else if (num < temp->data)
			suc = temp;
		else if (num > temp->data)
			pre = temp;
	}
	if (ins == 0)
	{
		if (num == pre->data)
			return pre;
		else
			return suc;
	}
	if (ins == -1)
	{
		if (num == pre->data)
			pre = checkPre(pre, pre);
		else
			pre = checkPre(suc, suc);
		if (!pre)
			pre = suc->parent;
		if (!pre)
			return nullptr;
		cout << pre->data << endl;
		splay(pre);
	}
	if (ins == 1)
	{
		if (num == suc->data)
			suc = checkSuc(suc, suc);
		else
			suc = checkSuc(pre, pre);
		if (!suc)
			suc = pre->parent;
		if (!suc)
			return nullptr;
		cout << suc->data << endl;
		splay(suc);
	}
	return nullptr;
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

void Tree::inorder(Node* n)
{
	if (!n)
		return;
	cout << n->data << endl;
	inorder(n->left);
	inorder(n->right);
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
		//root->inorder(root->treeRoot);
		//cout << endl;
	}
	return 0;
}