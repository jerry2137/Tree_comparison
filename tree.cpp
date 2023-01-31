#include <iostream>
#include <time.h>
#include "AVLTree.h"
#include "SplayTree.h"
using namespace std;

const int N = 1000000;

inline int randopt() {
	return rand() % 6 + 1;
}

inline int randval() {
	return rand() % 10000;
}

int main()
{
	srand(clock());
	clock_t start, end;
	double time[8];
	int val = randval();

	//--------------------------generator1-----------------------
	//AVLTree
	freopen("AVLTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
		cout << randopt() << " " << randval() << endl;

	fclose(stdout);

	start = clock();

	AVLTree* AVLRoot1 = new AVLTree;
	AVLRoot1->AVLExecute();

	end = clock();

	time[0] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//splayTree
	freopen("splayTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
		cout << randopt() << " " << randval() << endl;

	fclose(stdout);

	start = clock();

	splayTree* splayRoot1 = new splayTree;
	splayRoot1->splayExecute();

	end = clock();

	time[1] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//--------------------------generator2-----------------------
	//AVLTree
	freopen("AVLTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
	{
		int var = randval();
		if (var % 2 == 0)
			val += 1;
		else
			val -= 1;
		cout << randopt() << " " << val << endl;
	}

	fclose(stdout);

	start = clock();

	AVLTree* AVLRoot2 = new AVLTree;
	AVLRoot2->AVLExecute();

	end = clock();

	time[2] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//splayTree
	freopen("splayTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
	{
		int var = randval();
		int opt = randopt();
		if (var % 2 == 0)
			val += 1;
		else
			val -= 1;
		cout << randopt() << " " << val << endl;
	}

	fclose(stdout);

	start = clock();

	splayTree* splayRoot2 = new splayTree;
	splayRoot2->splayExecute();

	end = clock();

	time[3] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//--------------------------generator3-----------------------
	//AVLTree
	freopen("AVLTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
	{
		val += 1;
		cout << randopt() << " " << val << endl;
	}

	fclose(stdout);

	start = clock();

	AVLTree* AVLRoot3 = new AVLTree;
	AVLRoot3->AVLExecute();

	end = clock();

	time[4] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//splayTree
	freopen("splayTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
	{
		val += 1;
		cout << randopt() << " " << val << endl;
	}

	fclose(stdout);

	start = clock();

	splayTree* splayRoot3 = new splayTree;
	splayRoot3->splayExecute();

	end = clock();

	time[5] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//--------------------------generator4-----------------------
	//AVLTree
	freopen("AVLTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
	{
		val += 1;
		int opt = randopt();
		if (opt == 4)
			opt = randopt();
		cout << opt << " " << val << endl;
	}

	fclose(stdout);

	start = clock();

	AVLTree* AVLRoot4 = new AVLTree;
	AVLRoot4->AVLExecute();

	end = clock();

	time[6] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//splayTree
	freopen("splayTree.in", "wb", stdout);

	cout << N << endl;
	for (int i = 1; i <= N; i++)
	{
		val += 1;
		int opt = randopt();
		if (opt == 4)
			opt = randopt();
		cout << opt << " " << val << endl;
	}

	fclose(stdout);

	start = clock();

	splayTree* splayRoot4 = new splayTree;
	splayRoot4->splayExecute();

	end = clock();

	time[7] = ((double)(end - start)) / CLOCKS_PER_SEC;

	//--------------------------result-----------------------
	freopen("tree.out", "wb", stdout);

	cout << "generator1, AVL, time: " << time[0] << endl;
	cout << "generator1, Splay, time: " << time[1] << endl;
	cout << "generator2, AVL, time: " << time[2] << endl;
	cout << "generator2, Splay, time: " << time[3] << endl;
	cout << "generator3, AVL, time: " << time[4] << endl;
	cout << "generator3, Splay, time: " << time[5] << endl;
	cout << "generator4, AVL, time: " << time[6] << endl;
	cout << "generator4, Splay, time: " << time[7] << endl;

	fclose(stdout);

	return 0;
}