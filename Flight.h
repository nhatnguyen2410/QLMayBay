#ifndef FLIGHT
#define FLIGHT
#include "Time.h"

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

#endif
