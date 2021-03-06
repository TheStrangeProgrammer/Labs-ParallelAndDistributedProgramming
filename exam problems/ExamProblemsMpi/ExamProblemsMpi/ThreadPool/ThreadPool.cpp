// ThreadPool.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <thread>
#include<condition_variable>
#include<list>
#include<vector>
#include<atomic>
#include<iostream>

using namespace std;

class ThreadPool {
	condition_variable cv;
	mutex mtx;
	list<function<void()>> work;
	vector<thread> threads;

	void run() {
		unique_lock<mutex> lck(mtx);
		while (true) {
			if (work.empty()) {
				cv.wait(lck);
			}
			else {
				function<void()> wf = work.front();
				work.pop_front();
				wf();
			}
		}
	}

public:
	explicit ThreadPool(int n) {
		threads.resize(n);
		for (int i = 0; i < n; ++i) {
			threads.emplace_back([this]() {run(); });
		}
	}

	void enqueue(function<void()>f) {
		unique_lock<mutex> lck(mtx);
		work.push_back(f);
		cv.notify_one();
	}
};

void funct(int start, int end) {
	for (int i = start; i < end; i++)
		cout << "i: " << i;
	cout << endl;
}
int main()
{
	ThreadPool pool(10);
	for (int i = 0; i < 5; ++i) {
		pool.enqueue([i]() {funct(i, i + 3); });
	}
	return 0;
}

