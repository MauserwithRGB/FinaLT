#include <iostream>
#include <string>
#include <vector>
#include <cctype>

class Category; // forward decalaration, because 'Category' is used before it is defined in 'Transactions', line 14
//FUNCTIONS
std::string tolowerString(std::string str)
{
	for (auto& x : str)
	{
		x = tolower(x);
	}
	
	return str;
}

// CLASSES
class Transactions
{
	private:
		double amount;
		// date and time
		std::string name;
		std::string details;
		Category* category;
		
	public:
		Transactions(std::string name, double amount, std::string details/*, date and time*/) : amount(amount), name(name), details(details)/*, category(category)*/ {}
		
		double getAmount()  // in order to updating/editing
		{
			return amount;
		}
};

class Category
{
	private:
		std::string name;
		std::vector <Transactions*> transactionVctr;  // a vector to store pointers to 'Transactions' objects
	
	public:
		Category(std::string name) : name(name){}
		
		std::string getName()
		{
			return name;
		}
		
//		void listTransactions()
		
		void addTransaction()
		{
			std::string name, details, catName;
			double amount;
			
			std::cout << "\nEnter the name";
			std::cin >> name; 
			
			std::cout << "\nEnter amount: ";
			std::cin >> amount;
			
			std::cout << "\nEnter details: ";
			std::cin >> details;
			
			Transactions* t = new Transactions(name, amount, details);
			
			transactionVctr.push_back(t); // DO NOT FORGET TO USE DELETE
		}
		
//		void deleteTransaction() 
};

class Budget // for multiple budgets
{
	private:
		std::string name;
		double limit;
//		double daily;  // a daily spending limit calculated using limit and budget duration, exceeding this will cause it  to be recalculated
//		int duration;  // to-do
		std::vector <Category*> categoryVctr; // a vector to store pointers to 'Category' objects
		
	public:
		Budget(std::string name, double limit) : name(name), limit(limit) {}
		
		std::string getName()
		{
			return name;
		}
		
		Category* findCategory(std::string catName)  // to search if a category already exists
		{
			for (Category* c : categoryVctr)
			{
				if (tolowerString(catName) == tolowerString(c->getName()))
					return c;
			}
			
			return nullptr; // not found, i.e; create new category
		}
		
		void addCategory(std::string catName)
		{	
			if (findCategory(catName) == nullptr)	
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
		
		Budget* findBudget(std::string budName)
		{
			for (Budget* b : budgetVctr)
			{
				if (tolowerString(budName) == tolowerString(b->getName()))
					return b;
			}
			
			return nullptr;
		}
		
		void addBudget(std::string name)
		{
			if (findBudget(name) == nullptr)
			{
				double limit;
				std::cout << "\nEnter budget limit: ";
				std::cin >> limit;
				
				budgetVctr.push_back(new Budget(name, limit));
			}
			
			else
				std::cout << "\nBudget already exists!";  // i may need to remove this if else checking because its not this methods job
		}
};

int main()
{
	std::cout << "\n-------- FinaLT --------\n";
	
	BudgetManager& manager = BudgetManager::getInstance();  // used a reference because it points to the same instance. Without it, the copy constructor will be invoked, which has been deleted for this class
	
	// main menu
	char choice;
	bool menuFlag = true; // used a flag so that the prgram can be terminated from inside a switch case
	
	while (menuFlag)
	{
		// editing might or  might not be edited. lets see what time says...
		std::cout << "\n1. Create a new transaction \t 2. Create a new category \t 3.  Create a new budget \t 4. Edit a transaction \t 5. Edit a category \t 6. Edit a budget \t 0. Exit the application\n";
		std::cin >> choice;
		
		switch (choice)
		{
			case '0': // inverted commas beacause choice is char
				menuFlag = false;
				break;
				
			case '1':
			{
				std::string budName;
				std::cout << "\nEnter budget: ";
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				if (b != nullptr)
				{
					std::string catName;
			
					std::cout << "\nEnter category: ";
					std::cin >> catName;
				
					Category* c = b->findCategory(catName);
					
					if (c != nullptr)
					{
						c->addTransaction();
					}						
				
					else
						std::cout << "\nCategory not found!";
				}
					
				else
					std::cout << "\nBudget not found!";
				}
				
			case '2':
			{
				std::string budName;
				std::cout << "\nEnter budget: ";
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				if (b != nullptr)
				{
					std::string catName;
			
					std::cout << "\nEnter category: ";
					std::cin >> catName;
				
					Category* c = b->findCategory(catName);
					
					if (c == nullptr)
						b->addCategory(catName);
					
					else
						std::cout << "\nCategory already exists!";						
				}
					
				else
					std::cout << "\nBudget not found!";
			}
			
			case '3':
			{
				std::string budName;
				std::cout << "\nEnter budget: ";
				std::cin >> budName;
				
				Budget* b = manager.findBudget(budName);
				
				if (b == nullptr)
					manager.addBudget(budName);
					
				else if (b != nullptr)
					std::cout << "\nBudget already exists!";
			}
		}
	}
	
}
