#include <iostream>
#include "Message.h"
#include <thread>
#include <chrono>

int main()
{
    Message obj1(1000, 10000, 10, "hello!");
    Message obj2(2000, 10000, 8, "how do you do?");
    Message obj3(3000, 10000, 5, "Good bye!");

    std::thread t1(obj1);
    std::thread t2(obj2);
    std::thread t3(obj3);
  
    t1.join();
    t2.join();
    t3.join();
    
    std::cout << "\ntotal message :" << Message::totalCount() << "\n";

}
