#include <iostream> 
#include <string> 
#include <cassert> 

using namespace std;
class Guest {
	string fullname;
	string connected_date;
public:
	Guest(string fullname, string date)
	{
		this->setFullname(fullname);
		this->setDate(date);
	}


	Guest(const Guest& guest)
	{
		this->setFullname(guest.getFullname());
		this->setDate(guest.getDate());
	}


	void setFullname(string fullname) {
		if (!fullname.empty()) {
			this->fullname = fullname;
		}
		else {
			cout << "Error." << endl;
		}
	}

	void setDate(string date) {
		if (!date.empty()) {
			this->connected_date = date;
		}
		else {
			cout << "Error." << endl;
		}
	}

	string getFullname() const {
		return this->fullname;
	}

	string getDate() const {
		return this->connected_date;
	}
};

class Admin {
	string username;
	string password;
public:

	Admin(string username, string password) {
		this->SetUsername(username);
		this->SetPassword(password);
	}


	Admin(const Admin& admin) {
		this->SetUsername(admin.GetUsername());
		this->SetPassword(admin.GetPassword());
	}

	void SetUsername(string username) {
		if (!username.empty()) {
			this->username = username;
		}
		else {
			cout << "Error." << endl;
		}
	}

	void SetPassword(string password) {
		if (!password.empty()) {
			this->password = password;
		}
		else {
			cout << "Error." << endl;
		}
	}

	string GetUsername() const {
		return this->username;
	}

	string GetPassword()const {
		return this->password;
	}

};

class Product {
	static int _id;
	int id;
	string name;
	string description;
	double price;
	double discount;
	int quantity;
	double tax;
public:

	Product()
	{
		id = ++_id;
	}

	Product(string name, double price, int quantity = 1)
		:Product()
	{
		this->setName(name);
		this->setPrice(price);
		this->setQuantity(quantity);
	}


	Product(string name, string description, double price, double discount, double tax, int quantity = 1)
		:Product(name, price, quantity)
	{
		this->setDescription(description);
		this->setDiscount(discount);
		this->setTax(tax);
	}

	Product(const Product& product)
		:Product(product.getName(), product.getDescription(), product.getPrice(), product.getDiscount(), product.getTax(), product.getQuantity())
	{
		this->id = product.id;
	}

	void setName(const string& name) {
		if (!name.empty()) {
			this->name = name;
		}
		else {
			cout << "Error." << endl;
		}
	}

	void setDescription(const string& description) {
		if (!description.empty()) {
			this->description = description;
		}
		else {
			cout << "Error." << endl;
		}
	}

	void setPrice(double price) {
		if (price >= 0) {
			this->price = price;
		}
		else {
			cout << "Error: Price cannot be negative." << endl;
		}
	}

	void setDiscount(double discount) {
		if (discount >= 0 && discount <= 1) {
			this->discount = discount;
		}
		else {
			cout << "Error: Discount should be between 0 and 1." << endl;
		}
	}

	void setTax(double tax) {

		if (tax >= 0) {
			this->tax = tax;
		}
		else {
			cout << "Error: Tax cannot be negative." << endl;
		}
	}

	void setQuantity(int quantity) {
		if (quantity >= 0) {
			this->quantity = quantity;
		}
		else {
			cout << "Error: Quantity cannot be negative." << endl;
		}
	}

	string getName()const {
		return this->name;
	}

	string getDescription()const {
		return this->description;
	}

	double getPrice()const {
		return this->price;
	}

	double getDiscount()const {
		return this->discount;
	}

	double getTax()const {
		return this->tax;
	}

	int getId()const {
		return this->id;
	}

	int getQuantity()const {
		return this->quantity;
	}
};

int Product::_id = 0;


template<typename T>
class DbSet {
	T** items = nullptr;
	int count = 0;
public:
	void add(const T* item)
	{
		if (items == nullptr)
		{
			items = new T * [++count];
			items[0] = new T(*item);
		}
		else
		{
			T** nItems = new T * [count + 1];
			for (size_t i = 0; i < count; i++)
				nItems[i] = items[i];


			nItems[count] = new T(*item);
			delete[] items;
			items = nItems;
			count++;
		}
	}

	bool checkId(const int& id)
	{
		for (size_t i = 0; i < count; i++)
			if (items[i]->getId() == id)
				return true;
		return false;

	}

	void deleteByid(const int& id)
	{
		if (checkId(id))
		{
			T** nItems = new T * [count - 1];
			int index = 0;

			for (size_t i = 0; i < count; i++)
			{
				if (items[i]->getId() != id)
					nItems[index++] = items[i];
				else
					delete items[i];
			}
			delete[] items;
			items = nItems;
			count--;
		}
	}

	T* getItem(const int& id)
	{
		if (checkId(id))
			for (size_t i = 0; i < count; i++)
				if (items[i]->getid() == id)
					return items[i];
		return nullptr;
	}

	int getCount() const
	{
		return count;
	}

	T** getItems() const
	{
		return items;
	}

	~DbSet()
	{
		if (items != nullptr)
		{
			for (size_t i = 0; i < count; i++)
				if (items[i] != nullptr)
					delete items[i];
			delete[] items;
		}
	}

	void deleteAllProducts() {
		for (size_t i = 0; i < count; i++) {
			delete items[i];
		}
		delete[] items;
		items = nullptr;
		count = 0;
	}

	void deleteAllGuests() {
		for (size_t i = 0; i < count; i++) {
			delete items[i];
		}
		delete[] items;
		items = nullptr;
		count = 0;
	};

};

class Database {
public:
	DbSet<Product>products;
	DbSet<Admin>admins;
	DbSet<Guest>guest;


	bool checkAdmin(string username)
	{
		for (size_t i = 0; i < admins.getCount(); i++)

			if (admins.getItems()[i]->GetUsername() == username)
				return true;
		return false;
	}

	bool adminLogin(string username, string password)
	{
		for (size_t i = 0; i < admins.getCount(); i++)
			if (admins.getItems()[i]->GetUsername() == username && admins.getItems()[i]->GetPassword() == password)
				return true;
		return false;
	}
	void deleteProduct(int productId) {
		if (products.checkId(productId)) {
			products.deleteByid(productId);
			cout << "mehsul ugurla silindi." << endl;
		}
		else {
			cout << "mehsul tapilmadi" << endl;
		}
	}

	void showAllProducts() {
		if (products.getCount() > 0) {
			cout << "butun mehsullar:" << endl;
			Product** productList = products.getItems();
			for (int i = 0; i < products.getCount(); i++) {
				cout << "ID: " << productList[i]->getId() << ", Name: " << productList[i]->getName() << ", Price: $" << productList[i]->getPrice() << ", Quantity: " << productList[i]->getQuantity() << endl;
			}
		}
		else {
			cout << "mehsul tapilmadi." << endl;
		}
	}

	void showAllGuests() {
		if (guest.getCount() > 0) {
			cout << "butun guestler:" << endl;
			Guest** guestList = guest.getItems();
			for (int i = 0; i < guest.getCount(); i++) {
				cout << "Fullname: " << guestList[i]->getFullname() << ", Connected Date: " << guestList[i]->getDate() << endl;
			}
		}
		else {
			cout << "tapilmadi." << endl;
		}
	}


	void updateProduct(int productId) {
		Product* productToUpdate = products.getItem(productId);
		if (productToUpdate != nullptr) {
			cout << "mehsul update edildi" << endl;
		}
		else {
			cout << "mehsul tapilmadi" << endl;
		}
	}

	void deleteAllProducts() {
		products.deleteAllProducts();
		cout << "butun mehsullar silindi." << endl;
	}

	void deleteAllGuests() {
		guest.deleteAllGuests();
		cout << "butun guestler silindiler." << endl;
	}

	void showTotalPriceById(int productId) {
		Product* product = products.getItem(productId);
		if (product != nullptr) {
			double totalPrice = product->getPrice() * product->getQuantity();
			cout << "umumi deyer " << product->getName() << ": $" << totalPrice << endl;
		}
		else {
			cout << "mehsul tapilmadi" << endl;
		}
	}

};


void printMenu() {
	cout << " 1 => Delete Product" << endl;
	cout << " 2 => Show All Products" << endl;
	cout << " 3 => Show All Guests" << endl;
	cout << " 4 => Update Product" << endl;
	cout << " 5 => Delete All Products" << endl;
	cout << " 6 => Delete All Guests" << endl;
	cout << " 7 => Show Total price by Id" << endl;
	cout << " 8 => Exit" << endl;
}

int main() {
	Database db;



	while (true) {
		printMenu();

		int choice;
		cout << "secim edin: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			int productId;
			cout << "ID daxil edin: ";
			cin >> productId;
			db.deleteProduct(productId);
			break;
		}
		case 2:
			db.showAllProducts();
			break;
		case 3:
			db.showAllGuests();
			break;
		case 4: {
			int productId;
			cout << "ID daxil edin: ";
			cin >> productId;
			db.updateProduct(productId);
			break;
		}
		case 5:
			db.deleteAllProducts();
			break;
		case 6:
			db.deleteAllGuests();
			break;
		case 7: {
			int productId;
			cout << "ID daxil edin: ";
			cin >> productId;
			db.showTotalPriceById(productId);
			break;
		}
		case 8:
			cout << "Exiting..." << endl;
			return 0;
		default:
			cout << "yanlis secim." << endl;
		}
	}
}







