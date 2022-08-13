#ifndef TIME
#define TIME

struct ThoiGian{
	int gio, phut, ngay, thang, nam;
};
bool Check_Date(int nam, int thang, int ngay)
{
	int Thang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ( (nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
	{
		Thang[1] = 29;
	}
	if (thang >= 1 && thang <= 12)
	{
		if (ngay >= 1 && ngay <= Thang[thang - 1])
		{
			return true;	
		}
	}
	return false;
}
#endif
