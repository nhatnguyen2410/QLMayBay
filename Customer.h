#ifndef CUSTOMER
#define CUSTOMER
#include "Flight.h"
#include "Plane.h"
struct Customer{
	char cmnd[16];// day la key chinh
	char ho[20];
	char ten[10];
	char phai[10];// 1 la nam , 0 la nu
	bool Booked;// kiem tra xem da mua ve chua
};

struct NodeCustomer{
	Customer HK;
	NodeCustomer *pLeft;
	NodeCustomer *pRight;
};

//typedef NodeCustomer *TREE_HK;
typedef NodeCustomer *NODPTR;

NODPTR tree = NULL;

void InitTreeHK(NODPTR &tree_hk)
{
	tree_hk = NULL;
}

bool Empty_HK(NODPTR tree_hk)
{
	return tree_hk == NULL;
}

NodeCustomer *SearchCustomer(NODPTR tree_hk, char cmnd[])
{
	if (tree_hk != NULL)
	{
		NodeCustomer *pNode = tree_hk;
		while (pNode != NULL)
		{
			if (strcmp(pNode->HK.cmnd, cmnd) == 0)
				return pNode;
			else if (strcmp(pNode->HK.cmnd, cmnd) > 0)
				pNode = pNode->pLeft;
			else if (strcmp(pNode->HK.cmnd, cmnd) < 0)
				pNode = pNode->pRight;
		}
	}
	return NULL;
}


void InsertHKToTree(NODPTR &tree_hk, Customer hk)
{
	if (tree_hk == NULL)
	{
		NodeCustomer *pNode = new NodeCustomer;
		pNode->HK = hk;
		pNode->pLeft = pNode->pRight = NULL;
		tree_hk = pNode;
	}
	else
	{
		if (atoi(tree_hk->HK.cmnd) > atoi(hk.cmnd))
			InsertHKToTree(tree_hk->pLeft, hk);
		else if (atoi(tree_hk->HK.cmnd) < atoi(hk.cmnd))
			InsertHKToTree(tree_hk->pRight, hk);
	}
}

int CheckHKtrongCB(listCB list,ListMayBay lmb,char MaCB[],char cmnd[])
{
	ChuyenBay cb;
	int socho;
	cb = Search_Flight(list,MaCB)->CB;
	socho = Get_slot(lmb,cb.soHieuMB);
	for(int dem= 1;dem <= socho;dem++)
	{
		if(!strcmp(cb.DsVe[dem].cmnd,cmnd)){
			return 1;
		}
	}
	return 0;
}


#endif
