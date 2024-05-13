#include <iostream>
#include <thread>

volatile int shared_value = 0;

void thread_function(int N) {
  for (int i = 0; i < N; i++) {
    shared_value ++;
  }
}

int main() {
  const int threads_num = 4;
  const int increments_num = 1'000'000;

  std::thread* threads[threads_num];

  for (int i = 0; i < threads_num; i++)
    threads[i] = new std::thread(thread_function, increments_num);

  for (int i = 0; i < threads_num; i++)
    threads[i]->join();

  std::cout << "We got " << shared_value << " increments this time around!" << std::endl;
}