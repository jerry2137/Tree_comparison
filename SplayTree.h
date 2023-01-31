#pragma warning(disable:4996)
#include <iostream>
using namespace std;

class splayNode
{
public:
	int data;
	splayNode* left;
	splayNode* right;
	splayNode* parent;
	int height;
	int amount;
};

class splayTree
{
public:
	splayTree();
	void splayExecute();
private:
	splayNode* treeRoot;
	int getHeight(splayNode* N);
	int getAmount(splayNode* N);
	int max(int a, int b);
	splayNode* newNode(int data, splayNode* p);
	void rSwitch(splayNode* n);
	void lSwitch(splayNode* n);
	void splay(splayNode* n);
	void insert(const int& val);
	splayNode* minValueNode(splayNode* n);
	void erase(const int& val);
	void order(int num);
	int orderRecur(splayNode* root, int order);
	void small(int num);
	splayNode* smallRecur(splayNode* n, int pos);
	splayNode* find(int num, int ins);
	splayNode* checkPre(splayNode* n, splayNode* pre);
	splayNode* checkSuc(splayNode* n, splayNode* suc);
};

splayTree::splayTree() { treeRoot = nullptr; }

int splayTree::getHeight(splayNode* N)
{
	if (N == nullptr)
		return 0;
	return N->height;
}

int splayTree::getAmount(splayNode* N)
{
	if (N == nullptr)
		return 0;
	return N->amount;
}

int splayTree::max(int a, int b) { return (a > b) ? a : b; }

splayNode* splayTree::newNode(int data, splayNode* p)
{

	splayNode* Node = new splayNode();
	Node->data = data;
	Node->left = nullptr;
	Node->right = nullptr;
	Node->parent = p;
	Node->height = 1;
	Node->amount = 1;
	return Node;
}

void splayTree::rSwitch(splayNode* n)
{
	splayNode* x = n->left;
	splayNode* temp = x->right;
	splayNode* p = n->parent;

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

void splayTree::lSwitch(splayNode* n)
{
	splayNode* y = n->right;
	splayNode* temp = y->left;
	splayNode* p = n->parent;

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

void splayTree::splay(splayNode* n)
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

void splayTree::insert(const int& val)
{
	if (!treeRoot)
	{
		treeRoot = newNode(val, nullptr);
		return;
	}

	splayNode* n = treeRoot;
	splayNode* temp = nullptr;

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

splayNode* splayTree::minValueNode(splayNode* n)
{
	if (!n)
		return nullptr;
	splayNode* current = n;
	while (current->left)
		current = current->left;
	return current;
}

void splayTree::erase(const int& val)
{
	splayNode* n = find(val, 0);
	if (!n)
		return;
	splay(n);
	if (!n->left || !n->right)
	{
		splayNode* temp = n->left ? n->left : n->right;

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
		splayNode* temp = minValueNode(n->right);
		splayNode* r = temp->right;
		splayNode* p = temp->parent;

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

void splayTree::order(int data)
{
	int o = orderRecur(treeRoot, data) + 1;
	//cout << o << endl;
	return;
}

int splayTree::orderRecur(splayNode* n, int data)
{
	if (!n)
		return 0;
	if (n->data < data)
		return getAmount(n->left) + orderRecur(n->right, data) + 1;
	if (n->data >= data)
		return orderRecur(n->left, data);
}

void splayTree::small(int pos)
{
	splayNode* temp = smallRecur(treeRoot, pos - 1);
	if (!temp)
		return;
	//cout << temp->data << endl;
	splay(temp);
	return;
}

splayNode* splayTree::smallRecur(splayNode* n, int pos)
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

splayNode* splayTree::find(int num, int ins)
{
	if (!treeRoot)
		return nullptr;
	splayNode* pre = treeRoot;
	splayNode* suc = treeRoot;
	splayNode* temp = nullptr;
	while (num != pre->data && num != suc->data)
	{
		if (num < pre->data)
		{
			if (!pre->left)
			{
				if (ins == 1)
				{
					//cout << pre->data << endl;
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
					//cout << suc->data << endl;
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
				//cout << pre->data << endl;
				splay(pre);
			}
			if (ins == 1)
			{
				//cout << suc->data << endl;
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
				splayNode* tag = checkPre(temp, temp);
				if (tag)
				{
					//cout << tag->data << endl;
					splay(tag);
				}
				else
				{
					//cout << pre->data << endl;
					splay(pre);
				}
			}
			if (ins == 1)
			{
				splayNode* tag = checkSuc(temp, temp);
				if (tag)
				{
					//cout << tag->data << endl;
					splay(tag);
				}
				else
				{
					//cout << suc->data << endl;
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
		//cout << pre->data << endl;
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
		//cout << suc->data << endl;
		splay(suc);
	}
	return nullptr;
}

splayNode* splayTree::checkPre(splayNode* n, splayNode* pre)
{
	if (!n)
		return nullptr;
	if (n->data == pre->data)
		return checkPre(n->left, pre);
	splayNode* temp = checkPre(n->right, pre);
	if (temp)
		return temp;
	return n;
}

splayNode* splayTree::checkSuc(splayNode* n, splayNode* suc)
{
	if (!n)
		return nullptr;
	if (n->data == suc->data)
		return checkSuc(n->right, suc);
	splayNode* temp = checkSuc(n->left, suc);
	if (temp)
		return temp;
	return n;
}

void splayTree::splayExecute()
{
	FILE* f=freopen("splayTree.in", "rb", stdin);
	int cases = 0;
	cin >> cases;
	for (int j = 0;j < cases;j++)
	{
		int opt = 0, data = 0;
		cin >> opt >> data;
		switch (opt)
		{
		case 1:
			insert(data);
			break;
		case 2:
			erase(data);
			break;
		case 3:
			order(data);
			break;
		case 4:
			small(data);
			break;
		case 5:
			find(data, -1);
			break;
		case 6:
			find(data, 1);
			break;
		default:
			break;
		}
	}
	fclose(f);
	fclose(stdin);
}
