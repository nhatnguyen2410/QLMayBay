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

#endif
