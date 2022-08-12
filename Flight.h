#ifndef FLIGHT
#define FLIGHT
#include "Time.h"
#include "Plane.h"
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

nodeCB *Search_Flight(listCB list, char macb[]){
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
#endif
