#include "./Utils/Semaphore.h"
#include "../TD3/Utils/Thread.h"
#include <iostream>
#include <vector>
#include <cstdlib>

class TokenProducer : public Thread {
private:
    Semaphore& m_semaphore;
    int m_tokensToProduce;
    int m_produced;

public:
    TokenProducer(int id, Semaphore& sem, int tokensToProduce)
        : Thread(id), m_semaphore(sem), m_tokensToProduce(tokensToProduce), m_produced(0) {}

    void run() override {
        for (int i = 0; i < m_tokensToProduce; ++i) {
            m_semaphore.give();
            ++m_produced;
        }
    }

    int getProduced() const { return m_produced; }
};

class TokenConsumer : public Thread {
private:
    Semaphore& m_semaphore;
    int m_consumed;

public:
    TokenConsumer(int id, Semaphore& sem)
        : Thread(id), m_semaphore(sem), m_consumed(0) {}

    void run() override {
        while (true) {
            if (m_semaphore.take(500)) {
                ++m_consumed;
            } else {
                break; // timeout
            }
        }
    }

    int getConsumed() const { return m_consumed; }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <num_consumers> <num_producers> <tokens_per_producer>\n";
        return 1;
    }

    int numConsumers = std::atoi(argv[1]);
    int numProducers = std::atoi(argv[2]);
    int tokensPerProducer = std::atoi(argv[3]);

    Semaphore sem(0);

    std::vector<TokenProducer*> producers;
    std::vector<TokenConsumer*> consumers;

    for (int i = 0; i < numProducers; ++i) {
        auto* p = new TokenProducer(i, sem, tokensPerProducer);
        producers.push_back(p);
        p->start(10); 
    }

    for (int i = 0; i < numConsumers; ++i) {
        auto* c = new TokenConsumer(i + numProducers, sem);
        consumers.push_back(c);
        c->start(10); 
    }

    for (auto* p : producers) p->join();
    for (auto* c : consumers) c->join();

    int totalProduced = 0;
    for (size_t i = 0; i < producers.size(); ++i) {
        int count = producers[i]->getProduced();
        std::cout << "Producer " << i << " produced " << count << " tokens.\n";
        totalProduced += count;
    }

    int totalConsumed = 0;
    for (size_t i = 0; i < consumers.size(); ++i) {
        int count = consumers[i]->getConsumed();
        std::cout << "Consumer " << i << " consumed " << count << " tokens.\n";
        totalConsumed += count;
    }

    std::cout << "Total tokens produced: " << totalProduced << "\n";
    std::cout << "Total tokens consumed: " << totalConsumed << "\n";

    if (totalProduced == totalConsumed) {
        std::cout << "SUCCESS: No token lost.\n";
    } else {
        std::cout << "ERROR: Token mismatch!\n";
    }

    for (auto* p : producers) delete p;
    for (auto* c : consumers) delete c;

    return 0;
}
