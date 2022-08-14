#ifndef FLIGHT
#define FLIGHT
#include "Time.h"
#include "Plane.h"
#include <ctime>
#include <sstream>
#include <locale>
#include <iomanip>
using namespace std;
struct Ve {
    char cmnd[16];
//    string TTVe;
};

struct ChuyenBay{
	char MaChuyenBay[15];
	char SanBayDen[20];
    ThoiGian ThoiGianDi;
	char soHieuMB[15];
	int TrangThai;// 0: huy chuyen 1: con ve, 2: het ve,3: hoan tat
	int TongSoDaBan;
	Ve *DsVe;
};


struct nodeCB {
	ChuyenBay CB;
	nodeCB *next;
};
typedef nodeCB *ptrCB;


struct listCB
{
	nodeCB *Head;
	nodeCB *Tail;
	int SoLuongChuyenBay;
};
typedef struct listCB* ListCB;


nodeCB *Search_MaCB(listCB list, char macb[]){
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return NULL;
	}
		
	else
	{
	
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.MaChuyenBay, macb) == 0){
			
				return temp;
			}
				
		}
	}
	return NULL;
}


int Get_slot(ListMayBay lmb, char soHieu[])
{
	for (int i = 0; i < lmb.soluong; i++)
	{
		if (strcmp(lmb.maybay[i]->soHieuMB, soHieu) == 0)
			return lmb.maybay[i]->soCho;
	}
	return -1;
}

bool checkFlightSameTime(listCB list,ListMayBay lmb, nodeCB *cb,char cmnd[16]){
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return false;
	}
	else{
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.MaChuyenBay, cb->CB.MaChuyenBay) != 0){
				if(temp->CB.ThoiGianDi.nam==cb->CB.ThoiGianDi.nam 
					&& temp->CB.ThoiGianDi.thang==cb->CB.ThoiGianDi.thang
					&& temp->CB.ThoiGianDi.ngay==cb->CB.ThoiGianDi.ngay
					&& temp->CB.ThoiGianDi.gio ==cb->CB.ThoiGianDi.gio
					&& temp->CB.ThoiGianDi.phut == cb->CB.ThoiGianDi.phut){
						int socho=Get_slot(lmb,temp->CB.soHieuMB);
						
						for(int i=1;i<=socho;i++){
							if(strcmp(temp->CB.DsVe[i].cmnd,cmnd)==0){
								return false;
							}
						}
					
					}
			}
				
		}
	}
	return true;
	
}
int test(nodeCB *cb){
	time_t now=time(0);
	tm *date=localtime(&now);
   date->tm_year=cb->CB.ThoiGianDi.nam-1900;
   date->tm_mon=cb->CB.ThoiGianDi.thang-1;
   date->tm_mday=cb->CB.ThoiGianDi.ngay;
   date->tm_hour=cb->CB.ThoiGianDi.gio;
   date->tm_min=cb->CB.ThoiGianDi.phut;
   date->tm_isdst = -1;
    time_t dateCB= mktime(*&date);
  
    return date->tm_mon;
}
bool validTimeBookingFlight(nodeCB *cb){ 
	time_t now=time(0);
	tm *date=localtime(&now);
   date->tm_year=cb->CB.ThoiGianDi.nam-1900;
   date->tm_mon=cb->CB.ThoiGianDi.thang-1;
   date->tm_mday=cb->CB.ThoiGianDi.ngay;
   date->tm_hour=cb->CB.ThoiGianDi.gio;
   date->tm_min=cb->CB.ThoiGianDi.phut;
   date->tm_isdst = -1;
    time_t dateCB= mktime(*&date);
  
  
	if((dateCB-now)/60>=30){
		return true;
	}
	
	return false;	
}


int InsertVe(ChuyenBay &cb,int vitri,char cmnd[16]){
	if (strcmp(cb.DsVe[vitri].cmnd,"\0"))
		return 0;
	else
	{
		strcpy(cb.DsVe[vitri].cmnd,cmnd);
		cb.TongSoDaBan++;
		return 1;
	}
}
int Huy1vemb(ListMayBay lmb,ChuyenBay &cb,char cmnd[15])
{
	int socho = Get_slot(lmb,cb.soHieuMB);
	for (int i = 1; i<=socho;i++)
	{
		if(strcmp(cb.DsVe[i].cmnd,cmnd)==0)
		{
			if(cb.TrangThai==2)
			{
				cb.TrangThai = 1; // HET VE -> CON VE
			}
			
			cb.TongSoDaBan--;
			strcpy(cb.DsVe[i].cmnd,"");
			return i;
		}
	}
	return 0;
}


int Check_NoiDen(listCB list, char noiden[])
{

	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return 0;
	}
		
	else
	{
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.SanBayDen, noiden) == 0){
			
				return 1;
			}
				
		}
	}
	return 0;
}
int CheckDSVe(listCB list,ListMayBay lmb,char MaCB[])
{
	ChuyenBay cb;
	int socho;
	cb = Search_MaCB(list,MaCB)->CB;
	socho = Get_slot(lmb,cb.soHieuMB);
	for(int dem= 1;dem <= socho;dem++)
	{
		if(strcmp(cb.DsVe[dem].cmnd,"") ){
			return 1;
		}
	}
	return 0;
}	

int Check_MaCB(listCB list, char macb[])
{
	if(Search_MaCB(list,macb)!=NULL){
		return 1;
	}
	return -1;
}
nodeCB *Search_MaMBinCB(listCB list, char maMB[]){
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return NULL;
	}
		
	else
	{
	
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.soHieuMB, maMB) == 0){
			
				return temp;
			}
				
		}
	}
	return NULL;
}
int Check_MaMBinCB(listCB list, char maMB[])
{
	if(Search_MaMBinCB(list,maMB)!=NULL){
		return 1;
	}
	return -1;
}

int CheckThoiGianNoiDen(ChuyenBay cb,ThoiGian tg,char noiden[])
{
			if (cb.ThoiGianDi.ngay == tg.ngay )
			{
				if(cb.ThoiGianDi.thang == tg.thang)
				{
					if(cb.ThoiGianDi.nam == tg.nam)
					{
						if(strcmp(cb.SanBayDen,noiden)==0)
						{
							return 1;
						}
					}
				}
			}
	return 0;
}


int CountCB_ThoiGianNoiDen(listCB list, ThoiGian tg, char noiden[])
{
	int dem = 0;
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return 0;
	}
		
	else
	{
		for (; temp != NULL; temp=temp->next)
		{
			if (temp->CB.ThoiGianDi.ngay == tg.ngay )
			{
				if(temp->CB.ThoiGianDi.thang == tg.thang)
				{
					if(temp->CB.ThoiGianDi.nam == tg.nam)
					{
						if(strcmp(temp->CB.SanBayDen,noiden)==0)
						{
							dem++;
						}
					}
				}
			}
				
		}
		return dem;
	}
	return 0;
}


int SearchVeHK(listCB list,ListMayBay lmb,char MaCB[],char cmnd[]){
	ChuyenBay cb;
	int socho;
	cb = Search_MaCB(list,MaCB)->CB;
	socho = Get_slot(lmb,cb.soHieuMB);
	
	for(int dem= 1;dem <= socho;dem++)
	{
		if(!strcmp(cb.DsVe[dem].cmnd,cmnd )){
			return dem;
		}
	}
	return 0;
	
}

// Tim so thu tu dua vao MaChuyenBay
int TimSTTChuyenBay( listCB list,char *MaChuyenBayCanTim)
{
	int index = 0;
	for( nodeCB *search = list.Head ; search != NULL; search = search->next)
	{
		/*so sanh 2 chuoi voi nhau co phan biet hoa thuong*/
		if( _stricmp(search->CB.MaChuyenBay,MaChuyenBayCanTim) == 0 )
		{
			return index;
		}
		index++;
	}
	return -1;
}

// TIM CHUYEN BAY THEO MA~
nodeCB *TimChuyenBay ( listCB list,char *MaChuyenBayCanTim)
{
	if( list.Head == NULL)
		return NULL;
	for( nodeCB *search = list.Head ; search != NULL; search = search->next)
	{
		if( _strcmpi(search->CB.MaChuyenBay,MaChuyenBayCanTim) == 0 )
		{
			return search;
		}
	}
	return NULL;
}

bool Check_ThoiGian_ChuyenBay(ThoiGian tg)
{
	int Thang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!Check_Date(tg.nam, tg.thang, tg.ngay)) return false;

	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	ThoiGian dtNow;
	dtNow.nam = 1900 + ltm->tm_year;
	dtNow.thang = 1 + ltm->tm_mon;
	dtNow.ngay = ltm->tm_mday;
	dtNow.gio = ltm->tm_hour;
	dtNow.phut = ltm->tm_min;

	if (tg.nam < dtNow.nam) return false;
	if ((tg.nam == dtNow.nam) && (tg.thang < dtNow.thang))  return false;
	if ((tg.nam % 400 == 0) || (tg.nam % 4 == 0 && tg.nam % 100 != 0))
		Thang[1] = 29;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay < dtNow.ngay)return false;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay == dtNow.ngay && tg.gio+5 < dtNow.gio)return false;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay == dtNow.ngay && tg.gio == dtNow.gio && tg.phut <= dtNow.phut)return false;
	return true;
}

bool CheckInvalidFlight(listCB list, ChuyenBay cb)
{
	int dem = 0;
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return false;
	}
		
	else
	{
		
		for (; temp != NULL; temp=temp->next)
		{
			
			
			if (temp->CB.ThoiGianDi.ngay == cb.ThoiGianDi.ngay)
			{
				if(temp->CB.ThoiGianDi.thang == cb.ThoiGianDi.thang)
				{
					if(temp->CB.ThoiGianDi.nam == cb.ThoiGianDi.nam)
					{
						if(((cb.ThoiGianDi.gio*60)+cb.ThoiGianDi.phut)-((temp->CB.ThoiGianDi.gio*60)+temp->CB.ThoiGianDi.phut)<180)
							{
							if(strcmp(temp->CB.soHieuMB,cb.soHieuMB)==0)
							{
								if(strcmp(temp->CB.MaChuyenBay,cb.MaChuyenBay)!=0)
								{
								
										if(temp->CB.TrangThai==0){
										return false;}
									
								return true;
								}
							}
							
							
							}	
					}
				}
			}
				
			
		}
		return false;
	}
}


#endif
