#include <ostream>
#include <memory>
#include <iomanip>
#include "blackjacklib.h"

class Date
{
private:
	int m_day;
	int m_month;
	int m_year;
public:
	Date() {};
	Date(int d, int m, int y) : m_day(d), m_month(m), m_year(y) {};
	~Date() {};

	int GetDay() const {
		return m_day;
	}

	int GetMonth() const {
		return m_month;
	}

	int GetYear() const {
		return m_year;
	}


	
	friend ostream& operator<< (ostream &out, const Date &date);
};

ostream& operator<< (ostream &out, const Date &date)
{
	out << date.GetDay() << "." << date.GetMonth() << "." << date.GetYear();
    return out;
}

unique_ptr<Date>& LaterDate(unique_ptr<Date>& d1, unique_ptr<Date>& d2) {

	if(d1->GetYear() == d2->GetYear()){
		if(d1->GetMonth() == d2->GetMonth()){
			if(d1->GetDay() == d2->GetDay()){
				return d1;
			} else if(d1->GetDay() > d2->GetDay()){
				return d1;
			} else {return d2;}
		} else if(d1->GetMonth() > d2->GetMonth()){
			return d1;
		} else {return d2;}
	} else if(d1->GetYear() > d2->GetYear()){
		return d1;
	} else {return d2;}

}

void SwitchDate(unique_ptr<Date>& d1, unique_ptr<Date>& d2) {
	unique_ptr<Date> tmp = make_unique<Date>();
	d1 = move(tmp);
	d2 = move(d1);
	tmp = move(d2);
}




int main(int argc, char const *argv[])
{

	unique_ptr<Date> today = make_unique<Date>(14, 6, 2021);
	unique_ptr<Date> date = make_unique<Date>();
	unique_ptr<Date> date1 = make_unique<Date>(12, 12, 1998);
	unique_ptr<Date> date2 = make_unique<Date>(23, 4, 2001);
	cout << today->GetDay() << endl;
	cout << today->GetMonth() << endl;
	cout << today->GetYear() << endl;
	cout << *today << endl;;
	date = move(today);
	if(date == nullptr) {
		cout << "Date is nullptr" << endl;;
	} else { 
		cout << "Date is " << *date << endl;;
	}
	if(today == nullptr) {
		cout << "Today is nullptr" << endl;
	} else { 
		cout << "Today is " << *today << endl;
	}
	
	cout << "Between: " << *date1 << " and: " << *date2 << " later date is: " << *LaterDate(date1, date2) << endl;
	SwitchDate(date1, date2);
	cout << "Between: " << *date1 << " and: " << *date2 << " later date is: " << *LaterDate(date1, date2) << endl;

	return 0;
}