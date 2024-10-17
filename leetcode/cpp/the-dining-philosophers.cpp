#include <condition_variable>
#include <functional>
using namespace std;
class Sempahore{
private:
    mutex mtx;
    int count;
    condition_variable cv;
}

class DiningPhilosophers {
private:
    mutex mtx;
    condition_variable cv;
public:
    DiningPhilosophers() {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		
    }
};
