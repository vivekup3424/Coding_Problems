#include <string>
#include <set>
class IObserver{
public:
	virtual ~IObserver(){}
	virtual void Update(const std::string messageFromSubject);
};
class IPublisher{
public:
	virtual ~IPublisher(){}
	virtual void Attach(IObserver *obs);
	virtual void Detach(IObserver *obs);
	virtual void Notify();
};
class Publisher: public IPublisher{
private:
	std::set<IObserver*> observers;
	public:
	void Attach(IObserver *obs) override {
		observers.insert(obs);
	}
	void Detach(IObserver *obs) override {
		observers.erase(obs);
	}
	void Notify() override{
		for(auto obs : observers){
			obs->Update("Hello");
		}
	}
};
