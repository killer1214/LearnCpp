//
// Created by illusory on 2025/6/27.
//

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;

// 前置声明
class Subject;

// 观察者接口
class Observer : public std::enable_shared_from_this<Observer> {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
    virtual void subscribe(const std::shared_ptr<Subject>& subject) = 0;
    virtual void unsubscribe() = 0;
};

//主题接口
class Subject{
public:
    virtual ~Subject() = default;
    virtual void attach(const std::weak_ptr<Observer>& observer) = 0;
    virtual void detach(const std::weak_ptr<Observer>& observer) = 0;
    virtual void notify(const std::string& message) = 0;
};

// 具体主题 - 气象站
class WeatherStation : public Subject {
    std::vector<std::weak_ptr<Observer>> observers;
    float temperature = 0.0f;
    float humidity = 0.0f;
public:
    void setMeasurements(float temp, float hum) {
        temperature = temp;
        humidity = hum;
        notify("Measurements updated");
    }

    void attach(const std::weak_ptr<Observer>& observer) override {
        observers.push_back(observer);
        cout << "[INFO]:Observer attached to WeatherStation\n";
    }

//    void detach(const std::weak_ptr<Observer>& observer) override {
//        auto it = std::remove_if(observers.begin(), observers.end(),
//             [&](const std::weak_ptr<Observer>& w) {
//                    if (auto o1 = w.lock(), o2 = observer.lock()) {
//                        return o1 == o2;
//                    }
//        });
//    }
    void detach(const std::weak_ptr<Observer>& observer) override {
        // 先锁定目标观察者， 避免在lambda中重复锁定
        const auto target = observer.lock();
        if (!target) {
            std::cout << "Detach attempt for expired observer\n";
            return;
        }
        auto it = std::remove_if(observers.begin(), observers.end(),
         [&](const std::weak_ptr<Observer>& w) {
             if (auto o1 = w.lock()) {
                 return o1 == target;  // 比较智能指针是否指向相同对象
             }

             return false;   // 已失效的观察者不匹配
         });
        // 计算实际移除的数量
        const size_t removed = std::distance(it, observers.end());

        observers.erase(it, observers.end());
        std::cout << "Observer detached" << removed << " observer(s) from WeatherStation\n";
    };

    void notify(const std::string& message) override {
        std::cout << "\nWeatherStation notifying " << observers.size() << " observers: " << message << "\n";

        // 使用临时容器存储有效的观察者
        std::vector<std::shared_ptr<Observer>> validObservers;
        for (auto& weak_obs : observers) {
            if(auto obs = weak_obs.lock()) {
                validObservers.push_back(obs);
            }
        }

        // 清理无效的观察者
        auto it = remove_if(observers.begin(), observers.end(), [](const std::weak_ptr<Observer>& w) {
            return w.expired();
        });
        observers.erase(it, observers.end());

        // 通知有效的观察者
        for (auto& obs : validObservers) {
            obs->update(message);
        }
    }

    float getTemperature() const { return temperature; }
    float getHumidity() const { return humidity; }

};

// 具体观察者 - 手机显示
class PhoneDisplay : public Observer {
    std::weak_ptr<Subject> weatherStation;
    std::string name;

public:
    explicit PhoneDisplay(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        if(auto station = weatherStation.lock()) {
            // TODO 查询dynamic_cast使用方法
            auto ws = dynamic_cast<WeatherStation*>(station.get());
            if (ws) {
                std::cout << "[" << name << "] Update received: " << message
                          << "\n  Temperature: " << ws->getTemperature()
                          << "°C, Humidity: " << ws->getHumidity() << "%\n";
            }
        }
    }

    void subscribe(const std::shared_ptr<Subject>& subject) override {
        weatherStation = subject;
        subject->attach(weak_from_this());
        std::cout << name << " subscribe to WeatherStation\n";
    }

    void unsubscribe() override {
        if (auto station = weatherStation.lock()) {
            station->detach(weak_from_this());
            // todo 思考该处reset作用
            weatherStation.reset();
            std::cout << name << " unsubscribe\n";
        }
    }

    ~PhoneDisplay() {
        unsubscribe();
        std::cout << name << " destroyed\n";
    }
};

// 具体观察者 - 电视显示
class TVDisplay : public Observer {
    std::weak_ptr<Subject> weatherStation;
    std::string name;

public:
    explicit TVDisplay(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        if(auto station = weatherStation.lock()) {
            // TODO 查询dynamic_cast使用方法
            auto ws = dynamic_cast<WeatherStation*>(station.get());
            if (ws) {
                std::cout << "[" << name << "] TV Display: Weather update!\n"
                          << "  Current temp: " << ws->getTemperature()
                          << "°C, Humidity: " << ws->getHumidity() << "%\n";
            }
        }
    }

    void subscribe(const std::shared_ptr<Subject>& subject) override {
        weatherStation = subject;
        subject->attach(weak_from_this());
        std::cout << name << " subscribe to WeatherStation\n";
    }

    void unsubscribe() override {
        if (auto station = weatherStation.lock()) {
            station->detach(weak_from_this());
            // todo 思考该处reset作用
            weatherStation.reset();
            std::cout << name << " unsubscribe\n";
        }
    }

    ~TVDisplay() {
        unsubscribe();
        std::cout << name << " destroyed\n";
    }
};

int main() {
    // 创建气象站主题
    auto weatherStation = std::make_shared<WeatherStation>();

    // 创建观察者
    auto phone1 = std::make_shared<PhoneDisplay>("John's Phone");
    auto phone2 = std::make_shared<PhoneDisplay>("Alice's Phone");
    auto tv = std::make_shared<TVDisplay>("Living Room TV");

    // 订阅
    std::cout << "==============订阅===============\n";
    phone1->subscribe(weatherStation);
    phone2->subscribe(weatherStation);
    tv->subscribe(weatherStation);

    std::cout << "=============更新气象数据================\n";
    weatherStation->setMeasurements(23.5f, 45.0f);

    std::cout << "=============取消一个订阅================\n";
    phone1->unsubscribe();

    std::cout << "=============更新气象数据================\n";
    weatherStation->setMeasurements(25.0f, 40.0f);

    // 创建临时观察者
    {
        std::cout << "=============创建临时观察者================\n";
        auto tempPhone = std::make_shared<PhoneDisplay>("Temporary Phone");
        tempPhone->subscribe(weatherStation);
        weatherStation->setMeasurements(26.0f, 38.0f);
    }

    std::cout << "=============再次更新气象数据================\n";
    weatherStation->setMeasurements(22.0f, 50.0f);

    std::cout << "=============取消所有订阅================\n";
    phone2->unsubscribe();
    tv->unsubscribe();

    std::cout << "=============结束================\n";
    return 0;
}







