#include <future>
#include <iostream>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <Windows.h>
using namespace std;

queue<int> que;
mutex mut;
int i = 60;
bool bÑreate = true;
bool stop = false;

void create() {
	while (!stop) {
		mut.lock();
		if (bÑreate) {
			que.push(rand()% 10000);
			if (que.size() >= 100) bÑreate = FALSE;
		}
		mut.unlock();
		this_thread::sleep_for(chrono::milliseconds(300));
	}
}

void sell() {
	while (!stop) {
		mut.lock();
		if (que.size() > 0) { 
			que.pop();
			if (que.size() <= 80) bÑreate = TRUE;
		}
		mut.unlock();
		this_thread::sleep_for(chrono::milliseconds(300));
	}
}


int main() {
	future<void> f1 = async(launch::async, create);
	future<void> f2 = async(launch::async, create);
	future<void> f3 = async(launch::async, create);
	future<void> f4 = async(launch::async, sell);
	future<void> f5 = async(launch::async, sell);

	while (!GetAsyncKeyState(VK_INSERT)) {
		mut.lock();
		cout << que.size() << '\n';
		mut.unlock();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	stop = true;

	f1.get();
	f2.get();
	f3.get();
	f4.get();
	f5.get();

	return 0;
}