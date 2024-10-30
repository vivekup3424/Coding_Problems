#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

class TokenBucket{
private:
  double tokens;
  double maxTokens;
  double refillRate;
  std::chrono::steady_clock
};
