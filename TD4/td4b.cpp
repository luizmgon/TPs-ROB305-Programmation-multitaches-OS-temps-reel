#include "Semaphore.h"
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>

// TokenProducer
class TokenProducer {
public:
    TokenProducer(Semaphore& sem, int tokensToProduce)
        : m_semaphore(sem), m_tokensToProduce(tokensToProduce), m_produced(0) {}

    void operator()() {
        for (int i = 0; i < m_tokensToProduce; ++i) {
            m_semaphore.give();
            ++m_produced;
        }
    }

    int getProduced() const { return m_produced; }

private:
    Semaphore& m_semaphore;
    int m_tokensToProduce;
    int m_produced;
};

// TokenConsumer
class TokenConsumer {
public:
    TokenConsumer(Semaphore& sem)
        : m_semaphore(sem), m_consumed(0) {}

    void operator()() {
        while (true) {
            if (m_semaphore.take(500)) {
                ++m_consumed;
            } else {
                break; // timeout -> fim da execução
            }
        }
    }

    int getConsumed() const { return m_consumed; }

private:
    Semaphore& m_semaphore;
    int m_consumed;
};

// main
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <num_consumers> <num_producers> <tokens_per_producer>\n";
        return 1;
    }

    int numConsumers = std::atoi(argv[1]);
    int numProducers = std::atoi(argv[2]);
    int tokensPerProducer = std::atoi(argv[3]);

    Semaphore sem(0);  // começa vazio

    std::vector<TokenProducer> producers;
    std::vector<TokenConsumer> consumers;
    std::vector<std::thread> threads;

    for (int i = 0; i < numProducers; ++i)
        producers.emplace_back(sem, tokensPerProducer);

    for (int i = 0; i < numConsumers; ++i)
        consumers.emplace_back(sem);

    for (auto& producer : producers)
        threads.emplace_back(std::ref(producer));

    for (auto& consumer : consumers)
        threads.emplace_back(std::ref(consumer));

    for (auto& t : threads)
        t.join();

    int totalProduced = 0, totalConsumed = 0;

    for (size_t i = 0; i < producers.size(); ++i) {
        int count = producers[i].getProduced();
        std::cout << "Producer " << i << " produced " << count << " tokens.\n";
        totalProduced += count;
    }

    for (size_t i = 0; i < consumers.size(); ++i) {
        int count = consumers[i].getConsumed();
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

    return 0;
}
