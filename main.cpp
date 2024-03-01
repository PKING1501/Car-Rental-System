#include<iostream>
#include<fstream>
#include <sstream>
#include<vector>
#include<ctime>
#include<regex>
#include<string>
using namespace std;

int customer_id, employee_id, car_id;

bool isValidDate(const std::string& dateStr) {
    int day, month, year;
    char delimiter;
    std::istringstream iss(dateStr);
    iss >> day >> delimiter >> month >> delimiter >> year;
    if (month < 1 || month > 12) {
        return false;
    }
    int maxDays;
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDays = 29;
        } else {
            maxDays = 28; 
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDays = 30; 
    } else {
        maxDays = 31; 
    }
    if (day < 1 || day > maxDays) {
        return false;
    }
    return true;
}

bool isValidDateFormat(const string& date) {
    if(!isValidDate(date)){
        return false;
    }
    regex dateRegex("\\b(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}\\b");
    return regex_match(date, dateRegex);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int getDaysInMonth(int month, int year) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return -1;
    }
}

void parseDate(const string& date, int& day, int& month, int& year) {
    istringstream ss(date);
    char delimiter;
    ss >> day >> delimiter >> month >> delimiter >> year;
}

int daysBetweenDates(const string& date1, const string& date2) {
    int day1, month1, year1;
    int day2, month2, year2;
    parseDate(date1, day1, month1, year1);
    parseDate(date2, day2, month2, year2);
    if (year2 < year1 || (year2 == year1 && month2 < month1) || (year2 == year1 && month2 == month1 && day2 < day1)) {
        std::swap(day1, day2);
        std::swap(month1, month2);
        std::swap(year1, year2);
    }
    int totalDays1 = day1;
    for (int i = 1; i < month1; ++i) {
        totalDays1 += getDaysInMonth(i, year1);
    }
    for (int i = 1; i < year1; ++i) {
        totalDays1 += isLeapYear(i) ? 366 : 365;
    }

    int totalDays2 = day2;
    for (int i = 1; i < month2; ++i) {
        totalDays2 += getDaysInMonth(i, year2);
    }
    for (int i = 1; i < year2; ++i) {
        totalDays2 += isLeapYear(i) ? 366 : 365;
    }
    return totalDays2 - totalDays1;
}

string getTodaysDate() {
    time_t now = std::time(nullptr);
    tm* timeinfo = std::localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", timeinfo);
    return std::string(buffer);
}

string swapDayYear(const string& date){
    std::string swapped = date.substr(6, 4); 
    swapped += "/";
    swapped += date.substr(3, 2); 
    swapped += "/";
    swapped += date.substr(0, 2); 
    return swapped;
}

int compareDates(const string& date1, const string& date2) {
    string swapped_date1 = swapDayYear(date1);
    string swapped_date2 = swapDayYear(date2);
    return swapped_date1 > swapped_date2;
}

class Request{
    public:
        int isEmployee;
        int id;
        int car_id;
        string startTime;
        string endTime;
};

class Car{
    public:
        int id;
        string model;
        string condition;
        int price;
        bool isAvl;
};

class User{
    public:
        string name;
        string email;
        string password;
        int fine;
};

class Customer: public User{
        friend class Start;
    private:
        Customer getCustomerWithID(int id);
    public:
        int id;
        int customer_record;
        void customerDashboard(const Customer &c);
        void addRentRequestCustomer(Customer customer);
        void viewCustomerDetails(Customer customer);
        void removeRentRequestCustomer(Customer customer);

};

class Employee: public User{
        friend class Start;
    private:
        Employee getEmployeeWithID(int id);
    public:
        int employee_record;
        int id;
        void employeeDashboard(const Employee &e);
        void removeRentRequestEmployee(Employee employee);
        void viewEmployeeDetails(Employee employee);
        void addRentRequestEmployee(Employee employee);

};

class Manager: public User{
        friend class Start;
    public:
        void managerDashboard();
        void addCar();
        void updateCar();
        void deleteCar();
        void deleteCustomer();
        void deleteEmployee();
};

class Start{
    private:
        int averageRecord();
        Customer customer;
        Employee employee;
        Manager manager;
    public:
        Start();
        void customerLogin();
        void customerRegister();
        void employeeLogin();
        void employeeRegister();
        void managerLogin();
};

void write_data_Employees(string str, Employee &employee){
    ofstream write;
    if(str=="id.txt"){
        write.open("temp.txt");
            write << customer_id << endl;
            write << employee_id << endl;
            write << car_id <<endl;
        write.close();
        remove("id.txt");
        rename("temp.txt","id.txt");
    }
    else{
        write.open(str,ios::app);
            write << employee.id << "\n";
            write << employee.name << "\n";
            write << employee.email << "\n";
            write << employee.password << "\n";
            write << employee.fine << "\n";
            write << employee.employee_record << "\n";
        write.close();
    }
}

void write_data_Customers(string str, Customer &cust){
    ofstream write;
    if(str=="id.txt"){
        write.open("temp.txt");
            write << customer_id << endl;
            write << employee_id << endl;
            write << car_id << endl;
        write.close();
        remove("id.txt");
        rename("temp.txt","id.txt");
    }
    else{
        write.open(str,ios::app);
            write << cust.id << "\n";
            write << cust.name << "\n";
            write << cust.email << "\n";
            write << cust.password << "\n";
            write << cust.fine << "\n";
            write << cust.customer_record << "\n";
        write.close();
    }
}

void write_data_request(string str,Request &req){
    ofstream write;
    write.open(str,ios::app);
        write<<req.isEmployee<<" ";
        write<<req.id<<" ";
        write<<req.car_id<<endl;
        write<<req.startTime<<endl;
        write<<req.endTime<< endl;
    write.close();
}

void write_data_cars(string str, Car car){
    ofstream write;
    write.open(str,ios::app);
        write<<car.id<<endl;
        write<<car.model<<endl;
        write<<car.condition<<endl;
        write<<car.price<<endl;
        write<<car.isAvl<<endl;
    write.close();
}

void viewCarList(){
    if(car_id==0){
        cout<<"\n--> No car available at the Moment, EMPTY List\n\n";
        return;
    }
    int count = 0;
    cout<<"--> LIST: ";
    ifstream read;
    Car temp_car;
    read.open("cars.txt",ios::app);
        while(!read.eof() && count<(car_id)){
            read >> temp_car.id;
            read.ignore(); getline(read, temp_car.model);
            getline(read, temp_car.condition);
            read >> temp_car.price;
            read >> temp_car.isAvl;
            if(temp_car.isAvl==true){
                cout<<"\n\n"<<temp_car.id<<". "<<temp_car.model<<" | "<<temp_car.condition<<" | [ "<<temp_car.price<<" ]\n";
            }
            count++;
        }
    read.close();
    cout<<"\n";
}

void viewRequests(int isEmployee, int id){
    ifstream read;
    read.open("requests.txt",ios::app);
        Request req; int count = 1;
        while(read>>req.isEmployee){
            read >> req.id; read>> req.car_id; read.ignore();
            getline(read, req.startTime);
            getline(read, req.endTime);
            if(isEmployee==req.isEmployee && req.id==id){
                cout<<"\n--> "<<count++<<". Rented Car ID: "<<req.car_id<<" | Start Date: "<<req.startTime<<" | End Date: "<<req.endTime<<endl;
            }
        }
    read.close();
}

void deleteRequest(int isEmployee, int id, int cid){
    ifstream read;
    int fine = 0;
    string returnDate;
    read.open("requests.txt",ios::app);
        Request req;
        int req_found=0;
        while(read >> req.isEmployee){
            read >> req.id; read>> req.car_id; read.ignore();
            getline(read, req.startTime);
            getline(read, req.endTime);
            if(isEmployee==req.isEmployee && req.id==id && req.car_id==cid){
                req_found=1;
                returnDate = req.endTime;
            }
            else{
                write_data_request("temp.txt",req);
            }
        }
    read.close();
    if(!req_found){
        cout<<"\n--> Invalid details, Please try again\n";
        remove("temp.txt");
        return;
    }
    else{
        cout<<"\n--> Enter Today's Date (DD/MM/YYYY): ";
        string todaysDate;
        cin.ignore(); getline(cin,todaysDate);
        if(compareDates(returnDate,todaysDate)==1){
            cout<<"\n--> Sorry, but returns can't be made earlier than due dates\n\n";
            return;
        }
        else{
            fine = 2*daysBetweenDates(todaysDate,returnDate);
        }
        cout<<"\n--> Enter the condition of returned Car ( Perfect / Not Bad / Critical ): \n--> ";
        string returningCondition;
        getline(cin, returningCondition);
        if(isEmployee==0){
            Customer cust;
            ifstream read;
            read.open("customers.txt",ios::app);
                while(read>>cust.id){
                    read.ignore();getline(read, cust.name);
                    read>>cust.email;
                    read>>cust.password;
                    read>>cust.fine;
                    read>>cust.customer_record;
                    if(cust.id==id){
                        cust.fine += fine;
                        // cout<<endl<<returningCondition<<endl;
                        if(returningCondition=="Not Bad"){
                            cust.customer_record = (cust.customer_record-1)<0?0:cust.customer_record-1;
                        }
                        else if(returningCondition=="Critical"){
                            cust.customer_record = (cust.customer_record-2)<0?0:cust.customer_record-2;
                        }
                        else if(returningCondition=="Perfect"){
                            ;
                        }
                        else{
                            cout<<"\n--> Enter VALID Car Condition\n\n";
                            return;
                        }
                    }
                    write_data_Customers("temp1.txt",cust);
                }
            read.close();
            remove("customers.txt");
            rename("temp1.txt","customers.txt");
        }
        else{
            Employee emp;
            ifstream read;
            read.open("employees.txt",ios::app);
                while(read>>emp.id){
                    read.ignore();getline(read, emp.name);
                    read>>emp.email;
                    read>>emp.password;
                    read>>emp.fine;
                    read>>emp.employee_record;
                    if(emp.id==id){
                        emp.fine += fine;
                        // cout<<endl<<returningCondition<<endl;
                        if(returningCondition=="Not Bad"){
                            emp.employee_record = (emp.employee_record-1)<0?0:emp.employee_record-1;
                        }
                        else if(returningCondition=="Critical"){
                            emp.employee_record = (emp.employee_record-2)<0?0:emp.employee_record-2;
                        }
                        else if(returningCondition=="Perfect"){
                            ;
                        }
                        else{
                            cout<<"\n--> Enter VALID Car Condition\n\n";
                            return;
                        }
                    }
                    write_data_Employees("temp1.txt",emp);
                }
            read.close();
            remove("employees.txt");
            rename("temp1.txt","employees.txt");
        }
        remove("requests.txt");
        rename("temp.txt","requests.txt");
        cout<<"\n--> Car return request Approved\n";
        return;
    }
}

void updateCustomer(Customer &customer){
    ifstream read;
    Customer cust; int count =0;
    read.open("customers.txt",ios::app);
        while(!read.eof() && count < customer_id){
            read >> cust.id;
            read.ignore(); getline(read,cust.name);
            read >> cust.email;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if(cust.id==customer.id){
                write_data_Customers("temp.txt",customer);
            }
            else{
                write_data_Customers("temp.txt", cust);
            }
            count++;
        }
    read.close();
    remove("customers.txt");
    rename("temp.txt","customers.txt");
}

void updateEmployee(Employee &employee){
    ifstream read;
    Employee emp; int count =0;
    read.open("employees.txt",ios::app);
        while(read>>emp.id){
            read.ignore(); getline(read,emp.name);
            read >> emp.email;
            read >> emp.password;
            read >> emp.fine;
            read >> emp.employee_record;
            if(emp.id==employee.id){
                write_data_Employees("temp.txt",employee);
            }
            else{
                write_data_Employees("temp.txt", emp);
            }
            count++;
        }
    read.close();
    remove("employees.txt");
    rename("temp.txt","employees.txt");
}

int Start::averageRecord(){
    long long sum = 0; int count = 0;
    ifstream read;
    Customer temp_cust;
    read.open("customers.txt",ios::app);
        while(!read.eof() && count < customer_id){
            read >> temp_cust.id;
            read.ignore(); getline(read, temp_cust.name);
            read >> temp_cust.email;
            read >> temp_cust.password;
            read >> temp_cust.fine;
            read >> temp_cust.customer_record;
            sum += temp_cust.customer_record;
            count++;
        }
    read.close();
    count = 0;
    Employee temp_employee;
    read.open("employees.txt",ios::app);
        while(!read.eof() && count < employee_id){
            read >> temp_employee.id;
            read.ignore(); getline(read, temp_employee.name);
            read >> temp_employee.email;
            read >> temp_employee.password;
            read >> temp_employee.fine;
            read >> temp_employee.employee_record;
            sum += temp_employee.employee_record;
            count++;
        }
    read.close();
    int ans = (int)(sum)/(customer_id+employee_id);
    return ans;
}

void Customer::viewCustomerDetails(Customer customer){
    ifstream read;
    Customer cust;
    read.open("customers.txt",ios::app);
        while(!read.eof()){
            read >> cust.id;
            read.ignore(); getline(read, cust.name);
            read >> cust.email;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if(customer.id==cust.id){
                cout<<"\n\n-----"<<cust.name<<"-----\n";
                cout<<"--> Email: "<<cust.email<<endl;
                cout<<"--> Password: "<<cust.password<<endl;
                cout<<"--> Fine: "<<cust.fine<<endl;
                cout<<"--> Customer Record: "<<cust.customer_record<<endl;
                cout<<"--> Cars On Rent: "<<endl;
                viewRequests(0,cust.id);
                break;
            }
        }
    read.close();
    return;
}

void Employee::viewEmployeeDetails(Employee employee){
    ifstream read;
    Employee emp;
    read.open("employees.txt",ios::app);
        while(!read.eof()){
            read >> emp.id;
            read.ignore(); getline(read, emp.name);
            read >> emp.email;
            read >> emp.password;
            read >> emp.fine;
            read >> emp.employee_record;
            if(employee.id==emp.id){
                cout<<"\n\n-----"<<emp.name<<"-----\n";
                cout<<"--> Email: "<<emp.email<<endl;
                cout<<"--> Password: "<<emp.password<<endl;
                cout<<"--> Fine: "<<emp.fine<<endl;
                cout<<"--> Employee Record: "<<emp.employee_record<<endl;
                cout<<"--> Cars On Rent: "<<endl;
                viewRequests(1,emp.id);
                break;
            }
        }
    read.close();
    return;
}

void Customer::addRentRequestCustomer(Customer customer){
    if(customer.fine!=0){
        cout<<"\n--> Please Clear Your Fines First\n\n";
        customerDashboard(customer);
        return;
    }
    cout<<"\n--> Choose one of the following cars by entering corresponding Index to proceed: \n";
    viewCarList();
    cout<<"--> ";
    int index, priceOfCar;
    cin>>index;
    ifstream read;
    Car temp_car; int count = 0; int car_found = 0;
    read.open("cars.txt",ios::app);
        while(!read.eof() && count<car_id){
            read >> temp_car.id;
            read.ignore(); getline(read, temp_car.model);
            getline(read, temp_car.condition);
            read >> temp_car.price;
            read >> temp_car.isAvl;
            if(temp_car.id==index && temp_car.isAvl==true){
                if(customer.customer_record<=0){
                    cout<<"\nPOOR CUSTOMER RECORD, Please talk to the manager\n\n";
                    customerDashboard(customer);
                    return;
                }
                car_found = 1;
                priceOfCar = temp_car.price;
                cout<<"\n--> Are you sure you want to proceed with the rent request (y/n) ?\n";
                cout<<"\n---Details For The Rental---\n";
                cout<<"Model Name: "<<temp_car.model<<endl<<"Car Condition: "<<temp_car.condition<<"\nCar Rent Price (weekly): "<<temp_car.price<<"\n\n";
                break;
            }
            else if(temp_car.id==index){
                cout<<"--> This particular car isn't available at the moment. Sorry for the Inconvenience\n\n";
                read.close();
                customerDashboard(customer);
                return;
            }
            count++;
        }
    read.close();
    if(!car_found){
        cout<<"\nPlease Enter a valid Car Index As per the List\n";
        customerDashboard(customer);
    }
    else{
        char choice;
        cout<<"--> ";
        cin>>choice;
        if(choice=='y'){
            string date_time = getTodaysDate();
            cout<<"--> Rental Approval Date: "<< date_time<<endl<<"--> Enter Return Date (DD/MM/YYYY): ";
            string rentalInvalidationTime;
            cin.ignore(); getline(cin,rentalInvalidationTime);
            int isDateEnteredValid = isValidDateFormat(rentalInvalidationTime);
            isDateEnteredValid = isDateEnteredValid & compareDates(rentalInvalidationTime,date_time);
            if(!isDateEnteredValid){
                cout<<"\n--> Invalid Date Format\n\n";
                customerDashboard(customer);
                return;
            }
            cout<<"\n--> Charge Amount per Week: "<< priceOfCar <<endl;
            ofstream write;
            write.open("requests.txt",ios::app);
                write << "0 " << customer.id << " " << index << endl << date_time <<endl<< rentalInvalidationTime<<endl;
            write.close();
            cout<<"\n RENT REQUEST SENT\n\n";
            customer.customer_record = (customer.customer_record-1)<0?0:(customer.customer_record-1);
            updateCustomer(customer);
            customerDashboard(customer);
        }
        else{
            cout<<"Request Cancelled, Redirecting\n\n";
            customerDashboard(customer);
        }
    }
}

void Customer::removeRentRequestCustomer(Customer customer){
    cout<<"\n--> Choose one of the following cars by entering corresponding Index to proceed: \n";
    viewRequests(0,customer.id);
    cout<<"\n--> Enter the returned car ID: ";
    int CID; cin>>CID;
    deleteRequest(0,customer.id,CID);
    customerDashboard(customer);
}

void Employee::removeRentRequestEmployee(Employee employee){
    cout<<"\n--> Choose one of the following cars by entering corresponding Index to proceed: \n";
    viewRequests(1, employee.id);
    cout<<"\n--> Enter the returned car ID: ";
    int CID; cin>>CID;
    deleteRequest(1,employee.id,CID);
    employeeDashboard(employee);
}

void Employee::addRentRequestEmployee(Employee employee){
    if(employee.fine!=0){
        cout<<"\n--> Please Clear Your Fines First\n\n";
        employeeDashboard(employee);
        return;
    }
    cout<<"\n--> Choose one of the following cars by entering corresponding Index to proceed: \n";
    viewCarList();
    cout<<"--> ";
    int index, priceOfCar;
    cin>>index;
    ifstream read;
    Car temp_car; int count = 0; int car_found = 0;
    read.open("cars.txt",ios::app);
        while(!read.eof() && count<car_id){
            read >> temp_car.id;
            read.ignore(); getline(read, temp_car.model);
            getline(read, temp_car.condition);
            read >> temp_car.price;
            read >> temp_car.isAvl;
            if(temp_car.id==index && temp_car.isAvl==true){
                if(employee.employee_record<=0){
                    cout<<"\nPOOR EMPLOYEE RECORD, Please talk to the manager\n\n";
                    employeeDashboard(employee);
                    return;
                }
                car_found = 1;
                priceOfCar = 0.85*temp_car.price;
                cout<<"\n--> Are you sure you want to proceed with the rent request (y/n) ?\n";
                cout<<"\n---Details For The Rental---\n";
                cout<<"Model Name: "<<temp_car.model<<endl<<"Car Condition: "<<temp_car.condition<<"\nCar Rent Price (weekly): ";
                cout<<0.85*temp_car.price<<"\n\n";
                break;
            }
            else if(temp_car.id==index){
                cout<<"--> This particular car isn't available at the moment. Sorry for the Inconvenience\n\n";
                read.close();
                employeeDashboard(employee);
                return;
            }
            count++;
        }
    read.close();
    if(!car_found){
        cout<<"\nPlease Enter a valid Car Index As per the List\n";
        employeeDashboard(employee);
    }
    else{
        char choice;
        cout<<"--> ";
        cin>>choice;
        if(choice=='y'){
            string date_time = getTodaysDate();
            cout<<"--> Rental Approval Date: "<< date_time<<endl<<"--> Enter Return Date (DD/MM/YYYY): ";
            string rentalInvalidationTime;
            cin.ignore(); getline(cin,rentalInvalidationTime);
            int isDateEnteredValid = isValidDateFormat(rentalInvalidationTime);
            isDateEnteredValid = isDateEnteredValid & compareDates(rentalInvalidationTime,date_time);
            if(!isDateEnteredValid){
                cout<<"\n--> Invalid Date Format\n\n";
                employeeDashboard(employee);
                return;
            }
            cout<<"\n--> Charge Amount per Week: "<< priceOfCar <<endl;
            ofstream write;
            write.open("requests.txt",ios::app);
                write << "1 " << employee.id << " " << index << endl << date_time <<endl<< rentalInvalidationTime<<endl;
            write.close();
            cout<<"\n RENT REQUEST SENT\n\n";
            employee.employee_record = (employee.employee_record-1)<0?0:(employee.employee_record-1);
            updateEmployee(employee);
            employeeDashboard(employee);
        }
        else{
            cout<<"Request Cancelled, Redirecting\n\n";
            employeeDashboard(employee);
        }
    }
}

Customer Customer::getCustomerWithID(int id){
    Customer cust;
    ifstream read;
    read.open("customers.txt",ios::app);
        while(!read.eof()){
            read >> cust.id;
            read.ignore(); getline(read, cust.name);
            read >> cust.email;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if(id==cust.id){
                return cust;
            }
        }
    read.close();
    cout<<"\n Customer Search Error\n\n";
    Start();
    return Customer();
}

Employee Employee::getEmployeeWithID(int id){
    ifstream read;
    Employee emp;
    read.open("employees.txt",ios::app);
        while(read >> emp.id){
            read.ignore(); getline(read, emp.name);
            read >> emp.email;
            read >> emp.password;
            read >> emp.fine;
            read >> emp.employee_record;
            if(id==emp.id){
                return emp;
            }
        }
    read.close();
    cout<<"\n Employee search Error\n\n";
    Start();
    return Employee();
}

void Employee::employeeDashboard(const Employee &e){
    Employee employee = getEmployeeWithID(e.id);
    int choice;
    cout<<"\n--------DASHBOARD--------\n";
    cout<<"--> 1. View Available CAR List\n";
    cout<<"--> 2. Make A Rent Request\n";
    cout<<"--> 3. Make A Return Request\n";
    cout<<"--> 4. View Profile\n";
    cout<<"--> 5. Clear Your Dues\n";
    cout<<"--> 6. Update Profile\n";
    cout<<"--> 7. Back To Start Page\n";
    cout<<"--> Anything Else To QUIT\n--> ";
    cin>>choice; 
    Employee emp;
    switch (choice){
        case 1:{
            viewCarList();
            employeeDashboard(employee);
            break;
        }
        case 2:
            addRentRequestEmployee(employee);
            break;
        case 3:
            removeRentRequestEmployee(employee);
            break;
        case 4:
            viewEmployeeDetails(employee);
            employeeDashboard(employee);
            break;
        case 5:
            emp = employee;
            if(emp.employee_record>=emp.fine){
                emp.employee_record-=emp.fine;
                emp.fine = 0;
                updateEmployee(emp);
                cout<<"\nAll Dues Cleared\n\n";
            }
            else{
                cout<<"\n--> Not Enough Record To Clear Dues\n\n";
            }
            employeeDashboard(emp);
            break;
        case 6:{
            int choice1;
            cout<<"--> What field will you like to update ?\n";
            cout<<"\n--> 1. Name\n--> 2. Email\n--> 3. Password\n-->";
            cin>>choice1;
            char c;
            string temp;
            switch (choice1)
            {
            case 1:
                cout<<"\n--> Current Name: "<<employee.name<<endl;
                cout<<"\n--> Enter New Name: ";
                cin.ignore(); getline(cin,temp);
                cout<<"Are you sure you want the following update ? (y/n):\n > "<<employee.name<<" --> "<< temp<<"\n--> ";
                cin>> c;
                if(c=='y'){
                    employee.name = temp;
                    updateEmployee(employee);
                    cout<<"\n--> Updated Successfully\n\n";
                }
                else{
                    cout<<"\nUpdate Cancelled\n\n";
                    employeeDashboard(employee);
                    return;
                }
                break;
            case 2:
                cout<<"\n--> Current Email: "<<employee.email<<endl;
                cout<<"\n--> Enter New Email: ";
                cin.ignore(); getline(cin,temp);
                cout<<"Are you sure you want the following update ? (y/n):\n > "<<employee.email<<" --> "<< temp<<"\n--> ";
                cin>> c;
                if(c=='y'){
                    employee.email = temp;
                    updateEmployee(employee);
                    cout<<"\n--> Updated Successfully\n\n";
                }
                else{
                    cout<<"\nUpdate Cancelled\n\n";
                    employeeDashboard(employee);
                    return;
                }
                break;
            case 3:
                cout<<"\n--> Current Password: "<<employee.password<<endl;
                cout<<"\n--> Enter New Password: ";
                cin.ignore(); getline(cin,temp);
                cout<<"Are you sure you want the following update ? (y/n):\n > "<<employee.password<<" --> "<< temp<<"\n--> ";
                cin>> c;
                if(c=='y'){
                    employee.password = temp;
                    updateEmployee(employee);
                    cout<<"\n--> Updated Successfully\n\n";
                }
                else{
                    cout<<"\nUpdate Cancelled\n\n";
                    employeeDashboard(employee);
                    return;
                }
                break;
            default:
                cout<<"Please choose one of the above choices\n";
                employeeDashboard(employee);
                return;
            }
        }
            break;
        case 7:
            Start();
            break;
        default:{
            exit(0);
            break;
        }
    }
    employeeDashboard(employee);
}

void Customer::customerDashboard(const Customer &c){
    Customer customer = getCustomerWithID(c.id);
    int choice;
    cout<<"\n--------DASHBOARD--------\n";
    cout<<"--> 1. View Available CAR List\n";
    cout<<"--> 2. Make A Rent Request\n";
    cout<<"--> 3. Make A Return Request\n";
    cout<<"--> 4. View Profile\n";
    cout<<"--> 5. Clear Your Dues\n";
    cout<<"--> 6. Update Profile\n";
    cout<<"--> 7. Back To Start Page\n";
    cout<<"--> Anything Else To QUIT\n--> ";
    cin>>choice; 
    Customer cust;
    switch (choice){
        case 1:{
            viewCarList();
            customerDashboard(customer);
            break;
        }
        case 2:
            addRentRequestCustomer(customer);
            break;
        case 3:
            removeRentRequestCustomer(customer);
            break;
        case 4:
            viewCustomerDetails(customer);
            customerDashboard(customer);
            break;
        case 5:
            cust = customer;
            if(cust.customer_record>=cust.fine){
                cust.customer_record -= cust.fine;
                cust.fine = 0;
                updateCustomer(cust);
                cout<<"\nAll Dues Cleared\n\n";
            }
            else{
                cout<<"\n--> Not Enough Record To Clear Dues\n\n";
            }
            customerDashboard(cust);
            break;
        case 6:{
            int choice1;
            cout<<"--> What field will you like to update ?\n";
            cout<<"\n--> 1. Name\n--> 2. Email\n--> 3. Password\n--> ";
            cin>>choice1;
            char c;
            string temp;
            switch (choice1)
            {
            case 1:
                cout<<"\n--> Current Name: "<<customer.name<<endl;
                cout<<"\n--> Enter New Name: ";
                cin.ignore(); getline(cin,temp);
                cout<<"Are you sure you want the following update ? (y/n):\n > "<<customer.name<<" --> "<< temp<<"\n--> ";
                cin>> c;
                if(c=='y'){
                    customer.name = temp;
                    updateCustomer(customer);
                    cout<<"\n--> Updated Successfully\n\n";
                }
                else{
                    cout<<"\nUpdate Cancelled\n\n";
                    customerDashboard(customer);
                    return;
                }
                break;
            case 2:
                cout<<"\n--> Current Email: "<<customer.email<<endl;
                cout<<"\n--> Enter New Email: ";
                cin.ignore(); getline(cin,temp);
                cout<<"Are you sure you want the following update ? (y/n):\n > "<<customer.email<<" --> "<< temp<<"\n--> ";
                cin>> c;
                if(c=='y'){
                    customer.email = temp;
                    updateCustomer(customer);
                    cout<<"\n--> Updated Successfully\n\n";
                }
                else{
                    cout<<"\nUpdate Cancelled\n\n";
                    customerDashboard(customer);
                    return;
                }
                break;
            case 3:
                cout<<"\n--> Current Password: "<<customer.password<<endl;
                cout<<"\n--> Enter New Password: ";
                cin.ignore(); getline(cin,temp);
                cout<<"Are you sure you want the following update ? (y/n):\n > "<<customer.password<<" --> "<< temp<<"\n--> ";
                cin>> c;
                if(c=='y'){
                    customer.password = temp;
                    updateCustomer(customer);
                    cout<<"\n--> Updated Successfully\n\n";
                }
                else{
                    cout<<"\nUpdate Cancelled\n\n";
                    customerDashboard(customer);
                    return;
                }
                break;
            default:
                cout<<"Please choose one of the above choices\n";
                customerDashboard(customer);
                return;
            }
        }
            break;
        case 7:
            Start();
            break;
        default:{
            exit(0);
            break;
        }
    } 
    customerDashboard(customer);
}

Start::Start(){
    ifstream read;
    read.open("id.txt"); 
    if(!read.fail()){
        read >> customer_id;
        read >> employee_id;
        read >> car_id;
    }
    else{
        customer_id = 0;
        employee_id = 0;
        car_id = 0;
    }
    read.close();
    int Choice;
    cout<<"\n--WELCOME TO PK RENTALS-- \t\n";
    cout<<"--> Please choose one of the following options (Eg: 1/2/...): \t\n";
    cout<<"--> 1. New around here, Register ?\n";
    cout<<"--> 2. Already familiar, Login ?\n";
    cout<<"--> 3. An Employee ?\n";
    cout<<"--> 4. Employee Registration ?\n";
    cout<<"--> 5. The Manager ?\n";
    cout<<"--> Anything Else To QUIT\n--> ";
    cin>>Choice;
    switch (Choice){
        case 1:
            customerRegister();
            break;
        case 2:
            customerLogin();
            break;
        case 3:
            employeeLogin();
            break;
        case 4:
            employeeRegister();
            break;
        case 5:
            managerLogin();
            break;
        default:
            exit(0);
            break;
    }
}

void Start::customerRegister(){
    cout<<"\n--Welcome!--"<<endl;
    Customer new_cust;  
    cout<<"Enter your name: "<<endl;
    string temporary;
    cin.ignore(); getline(cin,temporary); new_cust.name = temporary;
    cout<<"Enter your email id: "<<endl;
    cin >> new_cust.email;
    string email = new_cust.email;
    ifstream read;
    read.open("customers.txt",ios::app);
        while(!read.eof()){
            Customer cust;
            read >> cust.id;
            read.ignore(); getline(read,cust.name);
            read >> cust.email;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if(cust.email==email){
                cout<<"\n--> User with same EMAIL ID already Exists, Please Login \n";
                customerLogin();
                break;
            }
        }
    read.close();
    cout<<"Enter your password: "<<endl;
    cin>>new_cust.password;
    new_cust.fine = 0;
    new_cust.customer_record = (averageRecord()>3)?averageRecord():3;
    customer_id++;
    new_cust.id = customer_id;
    write_data_Customers("customers.txt", new_cust);
    write_data_Customers("id.txt", new_cust);
    cout<<"\nCustomer Registeration Successful"<<endl;
    customerLogin();
}

void Start::customerLogin(){
    cout<<"\nGreat to see you back !"<<endl<<"Please enter your credentials: "<<endl<<endl;
    cout<<"--> Email: ";
    string email;
    cin>>email;
    cout<<"--> Password: ";
    string password, name;
    cin>>password;
    int found_customer = 0;
    Customer cust_found;
    ifstream read;
    read.open("customers.txt",ios::app);
        while(!read.eof()){
            Customer cust;
            read >> cust.id;
            read.ignore(); getline(read, cust.name);
            read >> cust.email;
            read >> cust.password;
            read >> cust.fine;
            read >> cust.customer_record;
            if(cust.email==email && cust.password==password){
                cout<<"\n--> Welcome "<< cust.name << ", Your LOGIN Attempt Was SUCCESSFUL \n\n";
                found_customer = 1;
                cust_found = cust;
                break;
            }
            else if(cust.email==email){
                cout<<"\n--> Wrong Email Or Password\n";
                found_customer = 2;
                break;
            }
        }
    read.close();
    if(found_customer==1){
        customer.customerDashboard(cust_found);
    }
    else if(found_customer==2){
        customerLogin();
    }
    else if(found_customer==0){
        cout<<"\n--> Email ID not found, Please Register\n";
        Start();
    }
    else{
        Start();
    }
}

void Start::employeeRegister(){
    cout<<"\n--Welcome!--"<<endl;
    Employee new_employee;  
    cout<<"Enter your name: "<<endl;
    string temporary;
    cin.ignore(); getline(cin,temporary); new_employee.name = temporary;
    cout<<"Enter your email id: "<<endl;
    cin>>new_employee.email;
    string email = new_employee.email;
    ifstream read;
    read.open("employees.txt",ios::app);
        while(!read.eof()){
            Employee employee;
            read >> employee.id;
            read.ignore(); getline(read, employee.name);
            read >> employee.email;
            read >> employee.password;
            read >> employee.fine;
            read >> employee.employee_record;
            if(employee.email==email){
                cout<<"\n--> User with same EMAIL ID already Exists, Please Login \n";
                employeeLogin();
                break;
            }
        }
    read.close();
    cout<<"Enter your password: "<<endl;
    cin>>new_employee.password;
    new_employee.fine = 0;
    new_employee.employee_record = (averageRecord()>3)?averageRecord():3;;
    employee_id++;
    new_employee.id = employee_id;
    write_data_Employees("employees.txt", new_employee);
    write_data_Employees("id.txt", new_employee);
    cout<<"\nEmployee Registeration Successful"<<endl;
    employeeLogin();
}

void Start::employeeLogin(){
    cout<<"\nGreat to see you back !"<<endl<<"Please enter your credentials: "<<endl<<endl;
    cout<<"--> Email: ";
    string email;
    cin>>email;
    cout<<"--> Password: ";
    string password, name;
    cin>>password;
    int found_employee = 0;
    Employee employee_found;
    ifstream read;
    read.open("employees.txt",ios::app);
        while(!read.eof()){
            Employee employee;
            read >> employee.id;
            read.ignore(); getline(read, employee.name);
            read >> employee.email;
            read >> employee.password;
            read >> employee.fine;
            read >> employee.employee_record;
            if(employee.email==email && employee.password==password){
                cout<<"\n--> Welcome "<< employee.name << ", Your LOGIN Attempt Was SUCCESSFUL \n\n";
                found_employee = 1;
                employee_found = employee;
                break;
            }
            else if(employee.email==email){
                cout<<"\n--> Wrong Email Or Password\n";
                found_employee = 2;
                break;
            }
        }
    read.close();
    if(found_employee==1){
        employee.employeeDashboard(employee_found);
    }
    else if(found_employee==2){
        employeeLogin();
    }
    else if(found_employee==0){
        cout<<"\n--> Email ID not found, Please Register\n";
        Start();
    }
    else{
        Start();
    }
}

void Start::managerLogin(){
    Manager manager;
    ifstream read;
    read.open("manager.txt"); 
    if(!read.fail()){
        getline(read,manager.name);
        read >> manager.email;
        read >> manager.password;
    }
    else{
        cout<<"\n--> Hey Manager, What Should I Call You ?\n--> Name: ";
        cin.ignore(); getline(cin,manager.name);
        cout<<"\n\n--> Manager Please Set Your Email & Password\n--> Email: ";
        cin>>manager.email;
        cout<<"\n--> Password: ";
        cin>>manager.password;
        manager.fine=0;
        ofstream write;
        write.open("manager.txt",ios::app);
            write<<manager.name<<endl;
            write<<manager.email<<endl;
            write<<manager.password<<endl;
            write<<manager.fine<<endl;
        write.close();
    }
    cout<<"\nWelcome, Manager!\n\n";
    cout<<"Your Email ID please: ";
    string email, password;
    cin>>email;
    cout<<"Password please: ";
    cin>>password;
    read.open("manager.txt",ios::app);
        read.ignore(); getline(read, manager.name);
        read >> manager.email;
        read >> manager.password;
        read >> manager.fine;
    read.close();
    if(manager.email==email && manager.password==password){
        cout<<"\nLogin Successful\n";
        manager.managerDashboard();
    }
    else{
        cout<<"\nWrong Email/Password, Please try again\n\n";
        managerLogin();
    }
}

void Manager::managerDashboard(){
    int choice;
    cout<<"\n--------DASHBOARD--------\n";
    cout<<"--> 1. Create a Car Option\n";
    cout<<"--> 2. Update a Car Option\n";
    cout<<"--> 3. Delete a Car Option\n";
    cout<<"--> 4. View Available CAR List\n";
    cout<<"--> 5. View Customer Details\n";
    cout<<"--> 6. View Employee Details\n";
    cout<<"--> 7. View All Requests\n";
    cout<<"--> 8. Update Request\n";
    cout<<"--> 9. Delete Request\n";
    cout<<"--> 10. Delete Customer\n";
    cout<<"--> 11. Delete Employee\n";
    cout<<"--> 12. Update Customer Details\n";
    cout<<"--> 13. Update Employee Details\n";
    cout<<"--> 14. Back To Start Page\n";
    cout<<"--> Anything Else To QUIT\n--> ";
    cin>>choice;
    string name;
    ifstream read; Customer cust; int found = 0; Employee emp;
    switch (choice){
    case 1:
        addCar();
        break;
    case 2:
        updateCar();
        break;
    case 3:
        deleteCar();
        break;
    case 4:
        viewCarList();
        managerDashboard();
        break;
    case 5:
        cout<<"Enter the customer Name you would want details of:\n--> ";
        cin.ignore(); getline(cin,name);
        read.open("customers.txt",ios::app);
            while(read>>cust.id){
                read.ignore();getline(read,cust.name);
                read>>cust.email;
                read>>cust.password;
                read>>cust.fine;
                read>>cust.customer_record;
                if(name==cust.name){
                    found = 1;
                    cust.viewCustomerDetails(cust);
                    break;
                }
            }
        read.close();
        if(!found){
            cout<<"\n--> No customer with this Name exists\n\n";
        }
        managerDashboard();
        break;
    case 6:
        cout<<"Enter the employee Name you would want details of:\n--> ";
        cin.ignore(); getline(cin,name);
        read.open("employees.txt",ios::app);
            while(read>>emp.id){
                read.ignore();getline(read,emp.name);
                read>>emp.email;
                read>>emp.password;
                read>>emp.fine;
                read>>emp.employee_record;
                if(name==emp.name){
                    found = 1;
                    emp.viewEmployeeDetails(emp);
                    break;
                }
            }
        read.close();
        if(!found){
            cout<<"\n--> No employee with this Name exists\n\n";
        }
        managerDashboard();
        break;
    case 7:
        cout<<"\n";
        for(int i=1;i<=customer_id;i++){
            viewRequests(0,i);
        }
        for(int i=1;i<=employee_id;i++){
            viewRequests(1,i);
        }
        cout<<"\n";
        managerDashboard();
        break;
    case 8:{
        int isEmployee,id,cid;
            cout<<"\n--> Is the request a Customer's Request (y/n) ?\n--> ";
            char c;
            cin>>c;
            if(c=='y'){
                isEmployee = 0;
                cout<<"\n--> Enter the customer's ID: ";
            }
            else if(c=='n'){
                isEmployee = 1;
                cout<<"\n--> Enter the Employee's ID: ";
            }
            else{
                cout<<"\n--> INVALID CHOICE\n\n";
                managerDashboard();
                return;
            }
            cin>>id;
            cout<<"\n--> Enter the corresponding car ID: ";
            cin>>cid;
            ifstream read;
            read.open("requests.txt",ios::app);
                Request req;
                int req_found=0;
                while(read >> req.isEmployee){
                    read >> req.id; read>> req.car_id; read.ignore();
                    getline(read, req.startTime);
                    getline(read, req.endTime);
                    if(isEmployee==req.isEmployee && req.id==id && req.car_id==cid){
                        req_found=1;
                        cout<<"\n--> What would you like to update ?\n\n\t-----Details Of The Request-----\n";
                        cout<<"--> User ID: "<<req.id<<" | Car ID: "<<req.car_id<<" | Rent Approved On: "<<req.startTime<<" | Returning Date: "<<req.endTime<<"\n\n";
                        cout<<"--> 1. Ownership Status ( 0 --> customer/ 1 --> employee )\n";
                        cout<<"--> 2. User ID \n";
                        cout<<"--> 3. Car ID ( 1 - "<<car_id<<" )\n";
                        cout<<"--> 4. Rent Approval Date\n";
                        cout<<"--> 5. Returning Date\n--> ";
                        int ch;
                        cin>>ch;
                        if(ch==1){
                            cout<<"\n--> Update Status as: "<<req.isEmployee<<" --> "<<!req.isEmployee<<" (y/n)\n--> ";
                            char c; cin>>c;
                            if(c=='y') req.isEmployee = !req.isEmployee;
                            else if(c=='n'){;}
                            else{
                                cout<<"\n INVALID INPUT\n\n";
                                managerDashboard();
                            }
                        }
                        else if(ch==2){
                            if(req.isEmployee==0){
                                cout<<"\n--> Enter the New Customer ID: "; cin>>ch;
                                if(ch>customer_id || ch<=0){
                                    cout<<"\n--> INVALID INPUT\n";
                                    managerDashboard();
                                }
                                else req.id = ch;
                            }
                            if(req.isEmployee==1){
                                cout<<"\n--> Enter the New Employee ID: "; cin>>ch;
                                if(ch>employee_id || ch<=0){
                                    cout<<"\n--> INVALID INPUT\n";
                                    managerDashboard();
                                }
                                else req.id = ch;
                            }
                        }
                        else if(ch==3){
                            cout<<"\n--> Enter the New Car ID: "; cin>>ch;
                            if(ch>car_id || ch<=0){
                                cout<<"\n--> INVALID INPUT\n";
                                managerDashboard();
                            }
                            else req.car_id = ch;
                        }
                        else if(ch==4){
                            string a;
                            cout<<"\n--> Enter the New Date: ";
                            cin.ignore(); getline(cin,a);
                            int isDateEnteredValid = isValidDateFormat(a);
                            isDateEnteredValid = isDateEnteredValid & compareDates(req.endTime,a);
                            if(!isDateEnteredValid){
                                cout<<"\n--> Invalid Date Format\n\n";
                                managerDashboard();
                            }
                            req.startTime = a;
                        }
                        else if(ch==5){
                            string a;
                            cout<<"\n--> Enter the New Date: ";
                            cin.ignore(); getline(cin,a);
                            int isDateEnteredValid = isValidDateFormat(a);
                            isDateEnteredValid = isDateEnteredValid & compareDates(a, req.startTime);
                            if(!isDateEnteredValid){
                                cout<<"\n--> Invalid Date Format\n\n";
                                managerDashboard();
                            }
                            req.endTime = a;
                        }
                        else{
                            cout<<"\n--> INVALID INPUT\n";
                            managerDashboard();
                        }
                        write_data_request("temp.txt",req);
                    }
                    else{
                        write_data_request("temp.txt",req);
                    }
                }
            read.close();
            if(!req_found){
                cout<<"\n--> Invalid details, Please try again\n";
                remove("temp.txt");
                managerDashboard();
            }
            else{
                remove("requests.txt");
                rename("temp.txt","requests.txt");
                cout<<"\n--> Corresponding request has been Updated\n\n";
                managerDashboard();
            }
            break;
    }
    case 9:{
            int isEmployee,id,cid;
            cout<<"\n--> Is the request a Customer's Request (y/n) ?\n--> ";
            char c;
            cin>>c;
            if(c=='y'){
                isEmployee = 0;
                cout<<"\n-->Enter the customer's ID: ";
            }
            else if(c=='n'){
                isEmployee = 1;
                cout<<"\n-->Enter the Employee's ID: ";
            }
            else{
                cout<<"INVALID CHOICE\n\n";
                managerDashboard();
            }
            cin>>id;
            cout<<"\n--> Enter the corresponding car ID: ";
            cin>>cid;
            ifstream read;
            read.open("requests.txt",ios::app);
                Request req;
                int req_found=0;
                while(read >> req.isEmployee){
                    read >> req.id; read>> req.car_id; read.ignore();
                    getline(read, req.startTime);
                    getline(read, req.endTime);
                    if(isEmployee==req.isEmployee && req.id==id && req.car_id==cid){
                        req_found=1;
                    }
                    else{
                        write_data_request("temp.txt",req);
                    }
                }
            read.close();
            if(!req_found){
                cout<<"\n--> Invalid details, Please try again\n";
                remove("temp.txt");
                managerDashboard();
            }
            else{
                remove("requests.txt");
                rename("temp.txt","requests.txt");
                cout<<"\n--> Corresponding request has been Deleted\n\n";
                managerDashboard();
            }
            break;
        }
    case 10:
        deleteCustomer();
        break;
    case 11:
        deleteEmployee();
        break;
    case 12:{
        cout<<"\nHow would you like to update a Customer ?\n";
        cout<<"\n--> 1. By ID ?\n";
        cout<<"--> 2. By Name ?\n";
        cout<<"--> Anything Else To QUIT\n--> ";
        cin>>choice;
        switch (choice){
            case 1:{
                    int id, id_found = 0, count = 0;
                    cout<<"\n--> Enter the ID you want updated:\n";
                    cout<<"--> ID: "; cin>>id;
                    Customer temp_cust;
                    read.open("customers.txt",ios::app);
                        while(!read.eof() && count<customer_id){
                            read >> temp_cust.id;
                            read.ignore(); getline(read, temp_cust.name);
                            read >> temp_cust.email;
                            read >> temp_cust.password;
                            read >> temp_cust.fine;
                            read >> temp_cust.customer_record;
                            if(temp_cust.id!=id){
                                write_data_Customers("temp.txt",temp_cust);
                            }
                            else{
                                id_found=1;
                                int choice1;
                                cout<<"--> What field will you like to update ?\n";
                                cout<<"\n--> 1. Name\n--> 2. Email\n--> 3. Password\n--> 4. Fine\n--> 5. Customer Record\n--> ";
                                cin>>choice1;
                                char c;
                                string temp;
                                switch (choice1)
                                {
                                case 1:
                                    cout<<"\n--> Current Name: "<<temp_cust.name<<endl;
                                    cout<<"\n--> Enter New Name: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.name<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.name = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 2:
                                    cout<<"\n--> Current Email: "<<temp_cust.email<<endl;
                                    cout<<"\n--> Enter New Email: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.email<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.email = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 3:
                                    cout<<"\n--> Current Password: "<<temp_cust.password<<endl;
                                    cout<<"\n--> Enter New Password: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.password<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.password = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 4:
                                    cout<<"\n--> Current Fine: "<<temp_cust.fine<<endl;
                                    cout<<"\n--> Enter New Fine: ";
                                    int newFine;
                                    cin>>newFine;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.fine<<" --> "<<newFine<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.fine = newFine;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 5:
                                    cout<<"\n--> Current Customer Record: "<<temp_cust.customer_record<<endl;
                                    cout<<"\n--> Enter New Customer Record: ";
                                    int newCR;
                                    cin>>newCR;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.customer_record<<" --> "<<newCR<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.customer_record = newCR;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                default:
                                    cout<<"Please choose one of the above choices\n";
                                    managerDashboard();
                                }
                                write_data_Customers("temp.txt",temp_cust);
                            }
                            count++;
                        }
                    read.close();
                    if(!id_found){
                        cout<<"Please enter a valid ID for updating\n";
                        managerDashboard();
                        remove("temp.txt");
                    }
                    else{
                        remove("customers.txt");
                        rename("temp.txt","customers.txt");
                        cout<<"\nUpdate Successful\n";
                        managerDashboard();
                    }
                    break;
                }
            case 2:{
                    cout<<"\n--> Enter Customer Name for the Update: \n";
                    cout<<"--> Name: ";
                    cin.ignore(); getline(cin, name);
                    int name_found = 0, count = 0;
                    Customer temp_cust;
                    read.open("customers.txt",ios::app);
                        while(!read.eof() && count<(car_id)){
                            read >> temp_cust.id;
                            read.ignore(); getline(read, temp_cust.name);
                            read >> temp_cust.email;
                            read >> temp_cust.password;
                            read >> temp_cust.fine;
                            read >> temp_cust.customer_record;
                            if(temp_cust.name!=name){
                                write_data_Customers("temp.txt",temp_cust);
                            }
                            else{
                                name_found=1;
                                int choice1;
                                cout<<"--> What field will you like to update ?\n";
                                cout<<"\n--> 1. Name\n--> 2. Email\n--> 3. Password\n--> 4. Fine\n--> 5. Customer Record\n--> ";
                                cin>>choice1;
                                char c;
                                string temp;
                                switch (choice1)
                                {
                                case 1:
                                    cout<<"\n--> Current Name: "<<temp_cust.name<<endl;
                                    cout<<"\n--> Enter New Name: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.name<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.name = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 2:
                                    cout<<"\n--> Current Email: "<<temp_cust.email<<endl;
                                    cout<<"\n--> Enter New Email: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.email<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.email = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 3:
                                    cout<<"\n--> Current Password: "<<temp_cust.password<<endl;
                                    cout<<"\n--> Enter New Password: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.password<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.password = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 4:
                                    cout<<"\n--> Current Fine: "<<temp_cust.fine<<endl;
                                    cout<<"\n--> Enter New Fine: ";
                                    int newFine;
                                    cin>>newFine;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.fine<<" --> "<<newFine<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.fine = newFine;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 5:
                                    cout<<"\n--> Current Customer Record: "<<temp_cust.customer_record<<endl;
                                    cout<<"\n--> Enter New Customer Record: ";
                                    int newCR;
                                    cin>>newCR;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_cust.customer_record<<" --> "<<newCR<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_cust.customer_record = newCR;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                default:
                                    cout<<"Please choose one of the above choices\n";
                                    managerDashboard();
                                }
                                write_data_Customers("temp.txt",temp_cust);
                            }
                            count++;
                        }
                    read.close();
                    if(!name_found){
                        cout<<"\n--> Customer with Name doesn't exist.\n";
                        remove("temp.txt");
                        managerDashboard();
                    }
                    else{
                        remove("customers.txt");
                        rename("temp.txt","customers.txt");
                        cout<<"\nThe Update Was Successful\n";
                        managerDashboard();
                    }
                    break;
                }
            default:{
                    managerDashboard();
                    break;
                }
        }
        break;
    }
    case 13:{
        cout<<"\nHow would you like to update an Employee ?\n";
        cout<<"\n--> 1. By ID ?\n";
        cout<<"--> 2. By Name ?\n";
        cout<<"--> Anything Else To QUIT\n--> ";
        cin>>choice;
        switch (choice){
            case 1:{
                    int id, id_found = 0, count = 0;
                    cout<<"\n--> Enter the ID you want updated:\n";
                    cout<<"--> ID: "; cin>>id;
                    Employee temp_emp;
                    read.open("employees.txt",ios::app);
                        while(!read.eof() && count<(employee_id)){
                            read >> temp_emp.id;
                            read.ignore(); getline(read, temp_emp.name);
                            read >> temp_emp.email;
                            read >> temp_emp.password;
                            read >> temp_emp.fine;
                            read >> temp_emp.employee_record;
                            if(temp_emp.id!=id){
                                write_data_Employees("temp.txt",temp_emp);
                            }
                            else{
                                id_found=1;
                                int choice1;
                                cout<<"--> What field will you like to update ?\n";
                                cout<<"\n--> 1. Name\n--> 2. Email\n--> 3. Password\n--> 4. Fine\n--> 5.Employee Record\n--> ";
                                cin>>choice1;
                                char c;
                                string temp;
                                switch (choice1)
                                {
                                case 1:
                                    cout<<"\n--> Current Name: "<<temp_emp.name<<endl;
                                    cout<<"\n--> Enter New Name: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.name<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.name = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 2:
                                    cout<<"\n--> Current Email: "<<temp_emp.email<<endl;
                                    cout<<"\n--> Enter New Email: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.email<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.email = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 3:
                                    cout<<"\n--> Current Password: "<<temp_emp.password<<endl;
                                    cout<<"\n--> Enter New Password: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.password<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.password = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 4:
                                    cout<<"\n--> Current Fine: "<<temp_emp.fine<<endl;
                                    cout<<"\n--> Enter New Fine: ";
                                    int newFine;
                                    cin>>newFine;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.fine<<" --> "<<newFine<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.fine = newFine;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 5:
                                    cout<<"\n--> Current Employee Record: "<<temp_emp.employee_record<<endl;
                                    cout<<"\n--> Enter New Employee Record: ";
                                    int newCR;
                                    cin>>newCR;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.employee_record<<" --> "<<newCR<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.employee_record = newCR;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                default:
                                    cout<<"Please choose one of the above choices\n";
                                    managerDashboard();
                                }
                                write_data_Employees("temp.txt",temp_emp);
                            }
                            count++;
                        }
                    read.close();
                    if(!id_found){
                        cout<<"Please enter a valid ID for updating\n";
                        managerDashboard();
                        remove("temp.txt");
                    }
                    else{
                        remove("employees.txt");
                        rename("temp.txt","employees.txt");
                        cout<<"\nUpdate Successful\n";
                        managerDashboard();
                    }
                    break;
                }
            case 2:{
                    cout<<"\n--> Enter Employee Name for the Update: \n";
                    cout<<"--> Name: ";
                    cin.ignore(); getline(cin, name);
                    int name_found = 0, count = 0;
                    Employee temp_emp;
                    read.open("employees.txt",ios::app);
                        while(!read.eof() && count<(employee_id)){
                            read >> temp_emp.id;
                            read.ignore(); getline(read, temp_emp.name);
                            read >> temp_emp.email;
                            read >> temp_emp.password;
                            read >> temp_emp.fine;
                            read >> temp_emp.employee_record;
                            if(temp_emp.name!=name){
                                write_data_Employees("temp.txt",temp_emp);
                            }
                            else{
                                name_found=1;
                                int choice1;
                                cout<<"--> What field will you like to update ?\n";
                                cout<<"\n--> 1. Name\n--> 2. Email\n--> 3. Password\n--> 4. Fine\n--> 5.Employee Record\n--> ";
                                cin>>choice1;
                                char c;
                                string temp;
                                switch (choice1)
                                {
                                case 1:
                                    cout<<"\n--> Current Name: "<<temp_emp.name<<endl;
                                    cout<<"\n--> Enter New Name: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.name<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.name = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 2:
                                    cout<<"\n--> Current Email: "<<temp_emp.email<<endl;
                                    cout<<"\n--> Enter New Email: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.email<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.email = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 3:
                                    cout<<"\n--> Current Password: "<<temp_emp.password<<endl;
                                    cout<<"\n--> Enter New Password: ";
                                    cin.ignore(); getline(cin,temp);
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.password<<" --> "<< temp<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.password = temp;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 4:
                                    cout<<"\n--> Current Fine: "<<temp_emp.fine<<endl;
                                    cout<<"\n--> Enter New Fine: ";
                                    int newFine;
                                    cin>>newFine;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.fine<<" --> "<<newFine<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.fine = newFine;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                case 5:
                                    cout<<"\n--> Current Employee Record: "<<temp_emp.employee_record<<endl;
                                    cout<<"\n--> Enter New Employee Record: ";
                                    int newCR;
                                    cin>>newCR;
                                    cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_emp.employee_record<<" --> "<<newCR<<"\n--> ";
                                    cin>> c;
                                    if(c=='y'){
                                        temp_emp.employee_record = newCR;
                                    }
                                    else{
                                        cout<<"\nUpdate Cancelled\n\n";
                                        managerDashboard();
                                    }
                                    break;
                                default:
                                    cout<<"Please choose one of the above choices\n";
                                    managerDashboard();
                                }
                                write_data_Employees("temp.txt",temp_emp);
                            }
                            count++;
                        }
                    read.close();
                    if(!name_found){
                        cout<<"\n--> Employees with Name doesn't exist.\n";
                        remove("temp.txt");
                        managerDashboard();
                    }
                    else{
                        remove("employees.txt");
                        rename("temp.txt","employees.txt");
                        cout<<"\nThe Update Was Successful\n";
                        managerDashboard();
                    }
                    break;
                }
            default:{
                    managerDashboard();
                    break;
                }
        }
        break;
    }
    case 14:
        Start();
        break;
    default:
        exit(0);
        break;
    }
}

void Manager::addCar(){
    ifstream read;
    read.open("id.txt"); 
    if(!read.fail()){
        read >> customer_id;
        read >> employee_id;
        read >> car_id;
    }
    else{
        customer_id = 0;
        employee_id = 0;
        car_id = 0;
    }
    read.close();
    Car car;
    car.id = ++car_id;
    car.condition = "Brand New";
    car.isAvl = true;
    cout<<"\n--> Add new car details: \n";
    cout<<"\n--> Name of the Model: ";
    cin.ignore(); getline(cin, car.model);
    int same_model_found = 0;
    read.open("cars.txt",ios::app);
        while(!read.eof()){
            Car temp_car;
            read >> temp_car.id;
            read.ignore(); getline(read, temp_car.model);
            getline(read, temp_car.condition);
            read >> temp_car.price;
            read >> temp_car.isAvl;
            if(temp_car.model==car.model){
                cout << "\nCar with same Model Name, already exists\n";
                same_model_found = 1;
                break;
            }
        }
    read.close();
    if(same_model_found){
        addCar();
    }
    else{
        cout<<"--> Rent Price: ";
        cin>>car.price;
        write_data_cars("cars.txt",car);
        Customer c;
        write_data_Customers("id.txt", c);
        cout<<"\nCar Added To Collection Successfully\n";
        managerDashboard();
    }
}

void Manager::deleteCar(){
    ifstream read;
    Customer c;
    write_data_Customers("id.txt", c);
    int choice;
    cout<<"\nHow would you like to delete a car ?\n";
    cout<<"\n--> 1. By ID ?\n";
    cout<<"--> 2. By Model Name ?\n--> ";
    cin>>choice;
    string model;
    switch (choice){
        case 1:{
                int id, id_found = 0, count = 0;
                cout<<"\n--> Enter the ID you want deleted:\n";
                cout<<"--> ID: "; cin>>id;
                Car temp_car;
                read.open("cars.txt",ios::app);
                    while(!read.eof() && count<(car_id)){
                        read >> temp_car.id;
                        read.ignore(); getline(read, temp_car.model);
                        getline(read, temp_car.condition);
                        read >> temp_car.price;
                        read >> temp_car.isAvl;
                        if(temp_car.id!=id){
                            if(id_found){
                                temp_car.id--;
                            }
                            write_data_cars("temp.txt",temp_car);
                        }
                        else{
                            id_found=1;
                        }
                        count++;
                    }
                read.close();
                if(!id_found){
                    cout<<"Please enter a valid ID for deletion\n";
                    managerDashboard();
                    remove("temp.txt");
                }
                else{
                    remove("cars.txt");
                    rename("temp.txt","cars.txt");
                    car_id--;
                    Customer c;
                    write_data_Customers("id.txt", c);
                    cout<<"\nDeletion was successful\n";
                    managerDashboard();
                }
                break;
            }
        case 2:{
                cout<<"\n--> Enter Model Name for Deletion: \n";
                cout<<"--> Model Name: ";
                cin.ignore(); getline(cin, model);
                int model_found = 0, count = 0;
                Car temp_car;
                read.open("cars.txt",ios::app);
                    while(!read.eof() && count<(car_id)){
                        read >> temp_car.id;
                        read.ignore(); getline(read, temp_car.model);
                        getline(read, temp_car.condition);
                        read >> temp_car.price;
                        read >> temp_car.isAvl;
                        if(temp_car.model!=model){
                            if(model_found){
                                temp_car.id--;
                            }
                            write_data_cars("temp.txt",temp_car);
                        }
                        else{
                            model_found=1;
                        }
                        count++;
                    }
                read.close();
                if(!model_found){
                    cout<<"\n--> Model Name doesn't exist.\n";
                    remove("temp.txt");
                    managerDashboard();
                }
                else{
                    remove("cars.txt");
                    rename("temp.txt","cars.txt");
                    car_id--;
                    Customer c;
                    write_data_Customers("id.txt", c);
                    cout<<"\nDeletion was successful\n";
                    managerDashboard();
                }
                break;
            }
        default:{
                managerDashboard();
                break;
            }
    }
}

void Manager::updateCar(){
    ifstream read;
    int choice;
    cout<<"\nHow would you like to update a car ?\n";
    cout<<"\n--> 1. By ID ?\n";
    cout<<"--> 2. By Model Name ?\n--> ";
    cin>>choice;
    string model;
    switch (choice){
        case 1:{
                int id, id_found = 0, count = 0;
                cout<<"\n--> Enter the ID you want updated:\n";
                cout<<"--> ID: "; cin>>id;
                Car temp_car;
                read.open("cars.txt",ios::app);
                    while(!read.eof() && count<(car_id)){
                        read >> temp_car.id;
                        read.ignore(); getline(read, temp_car.model);
                        getline(read, temp_car.condition);
                        read >> temp_car.price;
                        read >> temp_car.isAvl;
                        if(temp_car.id!=id){
                            write_data_cars("temp.txt",temp_car);
                        }
                        else{
                            id_found=1;
                            int choice1;
                            cout<<"--> What field will you like to update ?\n";
                            cout<<"\n--> 1. Model Name\n--> 2. Condition\n--> 3. Price\n--> 4. Availability\n\n--> ";
                            cin>>choice1;
                            char c;
                            string temp;
                            switch (choice1)
                            {
                            case 1:
                                cout<<"\n--> Current Model Name: "<<temp_car.model<<endl;
                                cout<<"\n--> Enter New Model Name: ";
                                cin.ignore(); getline(cin,temp);
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.model<<" --> "<< temp<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.model = temp;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            case 2:
                                cout<<"\n--> Current Condition: "<<temp_car.condition<<endl;
                                cout<<"\n--> Enter New Condition: ";
                                cin.ignore(); getline(cin,temp);
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.condition<<" --> "<< temp<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.condition = temp;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            case 3:
                                cout<<"\n--> Current Price: "<<temp_car.price<<endl;
                                cout<<"\n--> Enter New Price: ";
                                int x;
                                cin>>x;
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.price<<" --> "<<x<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.price = x;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            case 4:
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.isAvl<<" --> "<<!temp_car.isAvl<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.isAvl = !temp_car.isAvl;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            default:
                                cout<<"Please choose one of the above choices\n";
                                updateCar();
                                return;
                            }
                            write_data_cars("temp.txt",temp_car);
                        }
                        count++;
                    }
                read.close();
                if(!id_found){
                    cout<<"Please enter a valid ID for updating\n";
                    managerDashboard();
                    remove("temp.txt");
                }
                else{
                    remove("cars.txt");
                    rename("temp.txt","cars.txt");
                    cout<<"\nUpdate Successful\n";
                    managerDashboard();
                }
                break;
            }
        case 2:{
                cout<<"\n--> Enter Model Name for the Update: \n";
                cout<<"--> Model Name: ";
                cin.ignore(); getline(cin, model);
                int model_found = 0, count = 0;
                Car temp_car;
                read.open("cars.txt",ios::app);
                    while(!read.eof() && count<(car_id)){
                        read >> temp_car.id;
                        read.ignore(); getline(read, temp_car.model);
                        getline(read, temp_car.condition);
                        read >> temp_car.price;
                        read >> temp_car.isAvl;
                        if(temp_car.model!=model){
                            write_data_cars("temp.txt",temp_car);
                        }
                        else{
                            model_found=1;
                            int choice1;
                            cout<<"--> What field will you like to update ?\n";
                            cout<<"\n--> 1. Model Name\n--> 2. Condition\n--> 3. Price\n--> 4. Availability\n\n--> ";
                            cin>>choice1;
                            char c;
                            string temp;
                            switch (choice1)
                            {
                            case 1:
                                cout<<"\n--> Current Model Name: "<<temp_car.model<<endl;
                                cout<<"\n--> Enter New Model Name: ";
                                cin.ignore(); getline(cin,temp);
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.model<<" --> "<< temp<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.model = temp;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            case 2:
                                cout<<"\n--> Current Condition: "<<temp_car.condition<<endl;
                                cout<<"\n--> Enter New Condition: ";
                                cin.ignore(); getline(cin,temp);
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.condition<<" --> "<< temp<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.condition = temp;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            case 3:
                                cout<<"\n--> Current Price: "<<temp_car.price<<endl;
                                cout<<"\n--> Enter New Price: ";
                                int x;
                                cin>>x;
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.price<<" --> "<<x<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.price = x;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            case 4:
                                cout<<"Are you sure you want the following update ? (y/n):\n > "<<temp_car.isAvl<<" --> "<<!temp_car.isAvl<<"\n--> ";
                                cin>> c;
                                if(c=='y'){
                                    temp_car.isAvl = !temp_car.isAvl;
                                }
                                else{
                                    cout<<"\nUpdate Cancelled\n\n";
                                    managerDashboard();
                                    return;
                                }
                                break;
                            default:
                                cout<<"Please choose one of the above choices\n";
                                updateCar();
                                return;
                            }
                            write_data_cars("temp.txt",temp_car);
                        }
                        count++;
                    }
                read.close();
                if(!model_found){
                    cout<<"\n--> Model Name doesn't exist.\n";
                    remove("temp.txt");
                    managerDashboard();
                }
                else{
                    remove("cars.txt");
                    rename("temp.txt","cars.txt");
                    cout<<"\nThe Update Was Successful\n";
                    managerDashboard();
                }
                break;
            }
        default:{
                managerDashboard();
                break;
            }
    }
}

void Manager::deleteCustomer(){
    ifstream read;
    customer_id--;
    Customer c;
    write_data_Customers("id.txt", c);
    int choice;
    cout<<"\nHow would you like to delete a customer ?\n";
    cout<<"\n--> 1. By ID ?\n";
    cout<<"--> 2. By Name of the customer ?\n--> ";
    cin>>choice;
    string name;
    switch (choice){
        case 1:{
                int id, id_found = 0, count = 0;
                cout<<"\n--> Enter the customer ID you want deleted:\n";
                cout<<"--> ID: "; cin>>id;
                Customer temp_cust;
                read.open("customers.txt",ios::app);
                    while(!read.eof() && count<(customer_id+1)){
                        read >> temp_cust.id;
                        read.ignore(); getline(read, temp_cust.name);
                        read>> temp_cust.email;
                        read >> temp_cust.password;
                        read >> temp_cust.fine;
                        read >> temp_cust.customer_record;
                        if(temp_cust.id!=id){
                            if(id_found){
                                temp_cust.id--;
                            }
                            write_data_Customers("temp.txt",temp_cust);
                        }
                        else{
                            id_found=1;
                        }
                        count++;
                    }
                read.close();
                if(!id_found){
                    cout<<"Please enter a valid ID for deletion\n";
                    remove("temp.txt");
                    managerDashboard();
                }
                else{
                    remove("customers.txt");
                    rename("temp.txt","customers.txt");
                    cout<<"\nDeletion was successful\n";
                    managerDashboard();
                }
                break;
            }
        case 2:{
                cout<<"\n--> Enter Customer Name for Deletion: \n";
                cout<<"--> Customer Name: ";
                cin.ignore(); getline(cin, name);
                int name_found = 0, count = 0;
                Customer temp_cust;
                read.open("customers.txt",ios::app);
                    while(!read.eof() && count<(customer_id+1)){
                        read >> temp_cust.id;
                        read.ignore(); getline(read, temp_cust.name);
                        read>> temp_cust.email;
                        read >> temp_cust.password;
                        read >> temp_cust.fine;
                        read >> temp_cust.customer_record;
                        if(temp_cust.name!=name){
                            if(name_found){
                                temp_cust.id--;
                            }
                            write_data_Customers("temp.txt",temp_cust);
                        }
                        else{
                            name_found=1;
                        }
                        count++;
                    }
                read.close();
                if(!name_found){
                    cout<<"\n--> Customer with this Name doesn't exist.\n";
                    remove("temp.txt");
                    managerDashboard();
                }
                else{
                    remove("customers.txt");
                    rename("temp.txt","customers.txt");
                    cout<<"\nDeletion was successful\n";
                    managerDashboard();
                }
                break;
            }
        default:{
                managerDashboard();
                break;
            }
    }
}

void Manager::deleteEmployee(){
    ifstream read;
    employee_id--;
    Employee e;
    write_data_Employees("id.txt", e);
    int choice;
    cout<<"\nHow would you like to delete an employee ?\n";
    cout<<"\n--> 1. By ID ?\n";
    cout<<"--> 2. By Name of the customer ?\n--> ";
    cin>>choice;
    string name;
    switch (choice){
        case 1:{
                int id, id_found = 0, count = 0;
                cout<<"\n--> Enter the employee ID you want deleted:\n";
                cout<<"--> ID: "; cin>>id;
                Employee temp_emp;
                read.open("employees.txt",ios::app);
                    while(!read.eof() && count<(employee_id+1)){
                        read >> temp_emp.id;
                        read.ignore(); getline(read, temp_emp.name);
                        read>> temp_emp.email;
                        read >> temp_emp.password;
                        read >> temp_emp.fine;
                        read >> temp_emp.employee_record;
                        if(temp_emp.id!=id){
                            if(id_found){
                                temp_emp.id--;
                            }
                            write_data_Employees("temporary.txt", temp_emp);
                        }
                        else{
                            id_found=1;
                        }
                        count++;
                    }
                read.close();
                if(!id_found){
                    cout<<"Please enter a valid ID for deletion\n";
                    remove("temporary.txt");
                    managerDashboard();
                }
                else{
                    remove("employees.txt");
                    rename("temporary.txt","employees.txt");
                    cout<<"\nDeletion was successful\n";
                    managerDashboard();
                }
                break;
            }
        case 2:{
                cout<<"\n--> Enter Employee Name for Deletion: \n";
                cout<<"--> Employee Name: ";
                cin.ignore(); getline(cin, name);
                int name_found = 0;
                Employee temp_emp;
                read.open("employees.txt",ios::app);
                    while(read >> temp_emp.id){
                        read.ignore(); getline(read, temp_emp.name);
                        read>> temp_emp.email;
                        read >> temp_emp.password;
                        read >> temp_emp.fine;
                        read >> temp_emp.employee_record;
                        if(temp_emp.name!=name){
                            if(name_found){
                                temp_emp.id--;
                            }
                            write_data_Employees("temporary.txt", temp_emp);
                        }
                        else{
                            name_found=1;
                        }
                    }
                read.close();
                if(!name_found){
                    cout<<"\n--> Employee with this Name doesn't exist.\n";
                    remove("temporary.txt");
                    managerDashboard();
                }
                else{
                    remove("employees.txt");
                    rename("temporary.txt","employees.txt");
                    cout<<"\nDeletion was successful\n";
                    managerDashboard();
                }
                break;
            }
        default:{
                managerDashboard();
                break;
            }
    }
}

int main(){
    Start Initiate;
}
