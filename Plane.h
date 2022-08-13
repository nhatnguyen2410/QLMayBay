#ifndef PLANE
#define PLANE
#define MAXMB 300
struct mayBay{
	char soHieuMB[15];
	char loaiMB[40];
	int soCho;
};
struct listMayBay{
	int soluong;
	mayBay *maybay[MAXMB];
};
typedef struct listMayBay ListMayBay;

int Empty_MB(ListMayBay dsMB)
{
	return dsMB.soluong == 0;
}
int Full_MB(ListMayBay dsMB)
{
	return dsMB.soluong == MAXMB;
}
int Check_SoHieu_MB(ListMayBay listMB, char sohieu[])
{
	if (Empty_MB(listMB))
		return -1;
	else
	{
		for (int i = 0; i < listMB.soluong; i++)
		{
			if (stricmp(listMB.maybay[i]->soHieuMB, sohieu) == 0)
				return i;
		}
		return -1;
	}
}
mayBay *SearchMB(ListMayBay lmb, char sohieu[])
{
	
	for (int i = 0; i < lmb.soluong; i++){
		if (strcmp(lmb.maybay[i]->soHieuMB, sohieu) == 0)
			return lmb.maybay[i];
	}
	return NULL;
}

#endif
