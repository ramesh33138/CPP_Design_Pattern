#include<iostream>
//In this pattern we can create more than one Instance/obeject of the class
//All methods and variables should be in static
//constructor and destructor should be in private 
//It doesn't use more RAM memory because we have created only one instance
//Usually we can't create object for constructor from outside the class if we make it as a private
//As I mentioned all methods are static so it doesn't use heap area. it always created in stack area only
class Singleton{
	public:
		static Singleton* create_instance() {
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


};
Singleton* Singleton::m_pInstance = nullptr; //since m_pInstance as a static so we have to initialize outside the class
int main () {
	//you can try with these things it will create only one instance but here we are creationg so many instances
	Singleton::create_instance();
	Singleton::create_instance();
	Singleton::create_instance();
	Singleton::create_instance();
	Singleton::create_instance();
	Singleton::create_instance();
	Singleton::destroy();
	Singleton::destroy();
	Singleton::destroy();
	Singleton::destroy();
	Singleton::destroy();
	Singleton::destroy();
	return 0;
}
