/**
 * @file main.cpp
 * Producer-Consumer implementation using C++ threads and atomics.
 * One producer thread, two consumer threads.
 * No mutexes used — synchronization via atomic indices.
 */
#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

const int MAX_VALUE = 100;
int buffer[MAX_VALUE];

atomic<int> producer_index{0};
atomic<int> consumer_index{0};

/**
 * @brief Producer function:
 * Fills the buffer with values from 0 to MAX_VALUE - 1.
 * Uses memory_order_release to ensure correct memory visibility.
 */
void producer() {
    for(int i = 0; i < MAX_VALUE; i++) {
        buffer[i] = i;
        producer_index.store(i + 1, memory_order_release);
    }
}

/**
 * @brief Consumer function:
 * Each consumer fetches the available index to read.
 * Waits until the producer has written the value at the index.
 * Prints the consumed value and consumer ID.
 * 
 * @param identificationNumber used to identify consumers.
 */
void consumer(int identificationNumber) {
    while (true)
    {
        int index = consumer_index.fetch_add(1, memory_order_acquire);
        if (index >= MAX_VALUE) {
            break;
        }

        while(producer_index.load(memory_order_acquire) <= index) {
            this_thread::yield();
        }

        cout << "Consumer " << identificationNumber << " received value: " << buffer[index] << endl;
    }

    cout << "Consumer " << identificationNumber << " finished" << endl;
}

/**
 * @brief Main function:
 * Launches one producer and two consumer threads.
 * Joins all threads before exiting.
 * Handles exceptions during thread join.
 * 
 * @return int Exit code.
 */
int main() {
    thread prod(producer);
    thread consumer1(consumer, 1);
    thread consumer2(consumer, 2);

    try {
        if(prod.joinable()) prod.join();
        if(consumer1.joinable()) consumer1.join();
        if(consumer2.joinable()) consumer2.join();
    } catch (const exception& e) {
        cerr << "Error. Thread join failed: " << e.what() << endl;
    }
    
    cout << "Done!" << endl;
    return 0;
}