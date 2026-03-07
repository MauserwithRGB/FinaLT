#include <iostream>
#include <string>
#include <vector>

class Category; // forward decalaration, because 'Category' is used before it is defined in 'Transactions', line 14

class Transactions
{
	private:
		double amount;
		// date and time
		std::string name;
		std::string details;
		Category* category;
		
	public:
		Transactions(std::string name, double amount, std::string details/*, Category *category/* , date and time*/) : amount(amount), name(name), details(details)/*, category(category)*/ {}
		
		double getAmount()  // in order to updating/editing
		{
			return amount;
		}
};

class Category
{
	private:
		std::string name;
	
	public:
		Category(std::string name) : name(name){}
		
		std::string getName()
		{
			return name;
		}
		
		void addTransaction()
		{
			std::string name, details, catName;
		//	Category* category;
			double amount;
			std::cout << "\nEnter the name, amount, details, category";
			std::cin >> name >> amount >> details/* >> category*/; 
			
			std::cout << "\nEnter amount: ";
			std::cin >> amount;
			
			std::cout << "\nEnter details: ";
			std::cin >> details;
			
			std::cout << "\nEnter category: ";
			std::cin >> catName;
//			Transactions* t(name, amount, details, *category);
		}
		
};

class Budget // for multiple budgets
{
	private:
		std::string name;
		double limit;
//		double daily;  // a daily spending limit calculated using limit and budget duration, exceeding this will cause it  to be recalculated
//		int duration  // to-do
		std::vector <Transactions*> transactionVctr;  // a vector to store pointers to 'Transactions' objects
		std::vector <Category*> categoryVctr; // a vector to store pointers to 'Category' objects
		
	public:
		Budget(std::string name, double limit) : name(name), limit(limit) {}
		
		Category* findCategory(std::string catName)  // to search if a category already exists
		{
			for (Category* c : categoryVctr)
			{
				if (catName == c->getName())
				{
					return c;
				}
			}
			
			return nullptr; // not found, i.e; create new category
		}
		
		void addCategory(std::string catName)
		{
			Category* catPtr = findCategory(catName);
			
			if (catPtr == nullptr)
				categoryVctr.push_back(new Category(catName));
				
			else
				std::cout << "\nCategory already exists!";
		}
};

/* the singleton
excerpt from Refactoring Guru:
All implementations of the Singleton have these two steps in common:

    1. Make the default constructor private, to prevent other objects from using the new operator with the Singleton class.
    2. Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static field. All following calls to this method return the cached object.

If your code has access to the Singleton class, then it’s able to call the Singleton’s static method. So whenever that method is called, the same object is always returned. */

class BudgetManager
{
	private:
		BudgetManager() { std::cout << "Called\n";};
		std::vector <Budget*> budgetVctr;  // vector to store pointers to 'Budget' objects
		
		BudgetManager(const BudgetManager&) = delete;  // deleting copy constructor
		BudgetManager& operator=(const BudgetManager&) = delete; // deleting assignment operator
		
	public:
		static BudgetManager& getInstance()  // a static mathod to call for
		{
			static BudgetManager instance;  // static ensures that its created only once along with the private constructor
			return instance;
		}
};

int main()
{
	std::cout << "\n-------- FinaLT --------\n";
	
	BudgetManager& manager = BudgetManager::getInstance();  // used a reference because it points to the same instance. Without it, the copy constructor will be invoked, which has been deleted for this class
	
	// main menu
	int choice;
	std::cout << "1. Add Transaction \t 2. Create a new budget\n";
	std::cin >> choice;
	
//	switch (choice)
//	{
//		case 1:
//			
//	}
	
}
