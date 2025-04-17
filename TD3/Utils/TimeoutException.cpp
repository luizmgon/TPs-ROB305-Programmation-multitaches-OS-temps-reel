#include <exception>
#include <string>

class TimeoutException : public std::exception
{
private:
    long timeout;

public:
    TimeoutException(long timeout) : timeout(timeout) {}
    const char *what() const noexcept
    {
        std::string message = "TimeoutException after waiting for " + std::to_string(timeout) + " ms";
        return message.c_str();
    }
};