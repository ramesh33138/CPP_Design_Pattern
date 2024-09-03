#include<iostream>
#include<bits/stdc++.h>
//In this pattern we can create more than one Instance/obeject of the class
//All methods and variables should be in static
//constructor and destructor should be in private 
//It doesn't use more RAM memory because we have created only one instance
//Usually we can't create object for constructor from outside the class if we make it as a private
//As I mentioned all methods are static so it doesn't use heap area. it always created in stack area only
//NOTE: If we use multiple threads without mutex/lock it will keep on creating instance so be aware of it
//In order to avoid that one mutex was introduced
class Singleton{
	public:
		static Singleton* create_instance() {
			std::lock_guard<std::mutex>lock(mtx);//it will automatically unlock the function when one thread completes its call
			if(m_pInstance == nullptr) {
				m_pInstance = new Singleton();
			}
			return m_pInstance;
		}
		static void destroy () {
			if(m_pInstance != nullptr) {
				delete m_pInstance;
				m_pInstance = nullptr;
			}
		}
	private:
	        Singleton(){
			std::cout<<"constructor created\n";
		}
		 ~Singleton () {
			std::cout<<"destructor destroys the object"<<std::endl;
		}
		static Singleton* m_pInstance;
		static std::mutex mtx;
};
Singleton* Singleton::m_pInstance = nullptr; //since m_pInstance as a static so we have to initialize outside the class
std::mutex Singleton::mtx;
int main () {
	std::vector<std::thread> threads;
	for(int i = 0; i < 10; i++) {
		auto callback = [] () {
			Singleton::create_instance();
		};
		//threads.emplace_back(std::thread([] () {Singleton::create_instance()}));
		threads.emplace_back(std::thread(callback));
	}
	for (auto& it : threads) {
		if(it.joinable())
		{
			it.join();
		}
	}
	//Singleton::destroy();
	return 0;
}
