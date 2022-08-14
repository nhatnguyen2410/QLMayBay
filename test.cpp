#include <iostream>
#include <ctime>

using namespace std;
time_t convertDateToNumber(int year,int month, int day, int hour, int minute){
 	tm date;
   date.tm_year=year-1900;
   date.tm_mon=month-1;
   date.tm_mday=day;
   date.tm_hour=hour;
   date.tm_min=minute;
   date.tm_isdst = -1;
  
   return mktime(&date);
}
int main() {
   // current date/time based on current system
   time_t now = time(0);
   tm now2;
   now2.tm_year=2022-1900;
   now2.tm_mon=8-1;
   now2.tm_mday=14;
   now2.tm_hour=16;
   now2.tm_min=30;
 
   time_t cb=mktime(&now2);

   cout<<now2.tm_hour;
   if((cb-now)/60>=30){
   		cout<<"cb-now";
   }
   else{
   	cout<<"hi";
   }

//	time_t now2 = time
//   cout << "Number of sec since January 1,1970 is:: " << now << endl;
//
//   tm *ltm = localtime(&now);
//
//   // print various components of tm structure.
//   cout << "Year:" << 1900 + ltm->tm_year<<endl;
//   cout << "Month: "<< 1 + ltm->tm_mon<< endl;
//   cout << "Day: "<< ltm->tm_mday << endl;
//   cout << "Time: "<< 5+ltm->tm_hour << ":";
//   cout << 30+ltm->tm_min << ":";
//   cout << ltm->tm_sec << endl;
}
