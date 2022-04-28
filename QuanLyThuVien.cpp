#include <iostream>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "mylib.h"
#include <windows.h>
#include <cmath>
using namespace std;

#define MAX 100
#define CTRL_F 6
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
// BAT PHIM = 0
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define F7 65
#define F8 66
#define F9 67
#define F10 68
// BAT PHIM = -32
#define HOME 71
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define PGUP 73
#define PGDOWN 81
#define END 79
#define INS 82
#define DEL 83

struct sach{
    string maSach;
    string vitri;
    int trangThai;
};
typedef struct sach SACH;

struct node_sach{
    SACH dataSach;
    node_sach* next;
};
typedef struct node_sach* PTR_SACH;

struct list_NodeSach{
	int n;
	int maSachLonNhat;
	PTR_SACH head;
};

struct dausach{
    string ISBN;
    string tenSach;
    string tacGia;
    string theLoai;
    int soLuongMuon;
    int soTrang;
    int namXuatBan;
    list_NodeSach listSach;
};
typedef struct dausach DAUSACH;

struct ds_dausach{
    int sl;
    DAUSACH* dsdsach[MAX];
};
typedef struct ds_dausach DS_DAUSACH;

struct muontra{
    string maSach;
    string ngayMuon;
    string ngayTra;
    int trangThai;
};
typedef struct muontra MUONTRA;

struct node_muontra{
    MUONTRA dataMuonTra;
    node_muontra* next;
};
typedef struct node_muontra* PTR_MUONTRA;

struct docgia{
    int maThe;
    string ho;
    string ten;
    string phai;
    int trangThaiThe;
    int soLuongMuon;
    int soLuongTra;
    int viTriMaThe;
    PTR_MUONTRA ptr_muontra;
};
typedef struct docgia DOCGIA;

struct node_docgia{
    DOCGIA dataDocGia;
    node_docgia* left;
    node_docgia* right;
};
typedef struct node_docgia* TREE_DOCGIA;

// Khai bao 2 struct de sap xep theo the loai va ten sach tang dan
struct IndexBookInGenre{
	int chiso;
	string tsach;
	string tloai;
};

struct listBookInGenre{
	int n;
	IndexBookInGenre *nodes;
};

//Khai bao 2 struct de sap xep theo ten va ho tang dan trong cay
struct IndexName{
    int maThe;
    string ho;
    string ten;
};

struct listName{
    int n;
    IndexName* nodes;
};

// khai bao 2 struct de sap xep theo so luot
struct IndexBookBorrowTimesNumber{
	int chiso;
	int soLuongMuon;
};


struct listBookBorrowTimesNumber{
	int n;
	IndexBookBorrowTimesNumber *nodes;
};

// khai bao 2 struct de sap xep theo so ngay qua han
struct IndexSoNgayQuaHan{
	int maThe;
	int soNgayQuaHan;
};


struct listSoNgayQuaHan{
	int n;
	IndexSoNgayQuaHan *nodes;
};


void Normal(){
	SetBGColor(0);
	SetColor(15);
}
void HighLight(){
	SetBGColor(6);
	SetColor(15);
}
void HighLight_Choose(){
	SetBGColor(2);
	SetColor(15);
}

int canhChuKhoangCach(int doDaiChu,int w){
	return (w - doDaiChu) / 2 + 1;
}

void ThongBao(int x,int y,string thongDiep){
	gotoxy(x,y);
	cout<<thongDiep;
}

void xoaNoiDung(int x,int y,int soLuong){
    for(int i = 0;i < soLuong;i++){
        gotoxy(x + i,y);
        cout<<" ";
    }
}

// ep kieu sang string
template <class T>
string changeToString(T n){
	stringstream convert;
	convert<<n;
	return convert.str();
}

void toLower(char &kyTu){
    if(kyTu >= 65 && kyTu <= 90)
        kyTu += 32;
}
void toUpper(char &kyTu){
    if(kyTu >= 97 && kyTu <= 122)
        kyTu -= 32;
}
void toUpperString(string &str){
    int len = str.length();
    for(int i = 0;i < len;i++){
        if(str[i] >= 97 && str[i] <= 122)
            str[i] -= 32;
    }
}


string chuanHoaMaSach(int maSach){
    string maChuyenDoi = "";
    if(maSach < 10)
        maChuyenDoi = "000" + changeToString(maSach);
    else if(maSach < 100)
        maChuyenDoi = "00" + changeToString(maSach);
    else if(maSach < 1000)
        maChuyenDoi = "0" + changeToString(maSach);
    else if(maSach < 1000)
        maChuyenDoi = changeToString(maSach);
    return maChuyenDoi;
}

int kiemTraNamNhuan(int year){
    if((year % 4 == 0) && (year % 100 != 0) || year % 400 == 0)
        return 1;
    return 0;
}

int soNgayCuaThang(int month,int year){
    int day;
    switch(month){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            day = 31;
            break;
        case 4: case 6: case 9: case 11:
            day = 30;
            break;
        default:
            if(kiemTraNamNhuan(year) == 1)
                day = 29;
            else
                day = 28;
    }
    return day;
}

void tachNgayThangNam(string ngay,int &d,int &m,int &y){
    string s[3] = {""};
    int vitri = 0;
    for(int i = 0;i < ngay.length();i++){
        if(ngay[i] != '-')
            s[vitri] += ngay[i];
        else{
            vitri++;
        }
    }
    d = atoi(s[0].c_str());
    m = atoi(s[1].c_str());
    y = atoi(s[2].c_str());
}

int soNgayMuonSach(string ngayQuaKhu,string ngayHienTai){
    int dQKhu, mQKhu, yQKhu;
    int dHTai, mHTai, yHTai;
    int soNgay = 0, soNgayDu = 0;
    tachNgayThangNam(ngayQuaKhu,dQKhu,mQKhu,yQKhu);
    tachNgayThangNam(ngayHienTai,dHTai,mHTai,yHTai);

    for(int i = yQKhu;i < yHTai;i++){
        if(kiemTraNamNhuan(i) == 1)
            soNgay += 366;
        else
            soNgay += 365;
    }

    for(int i = 1;i < mHTai;i++){
        soNgay += soNgayCuaThang(i,yHTai);
    }

    for(int i = 1;i < mQKhu;i++){
        soNgayDu += soNgayCuaThang(i,yQKhu);
    }
    soNgayDu += dQKhu - 1;
    return soNgay + dHTai - 1 - soNgayDu;
}

int kiemTraNgayHopLe(string ngay){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string ngayHienTai = "";
    ngayHienTai = changeToString(ltm->tm_mday) + "-" + changeToString(ltm->tm_mon + 1) + "-" + changeToString(1900 + ltm->tm_year);
    int d,m,y;
    tachNgayThangNam(ngay,d,m,y);
    if(y < 2010)
        return -1;
    if(m > 12 || m < 1)
        return 0;
    if(d > soNgayCuaThang(m,y) || d < 1)
        return 1;
    if(y > (1900 + ltm->tm_year)  || (y == (1900 + ltm->tm_year) && m > (ltm->tm_mon + 1)) || (y == (1900 + ltm->tm_year) && m == (ltm->tm_mon + 1)
                                                                                               && d > ltm->tm_mday))
        return -2;

    return 2;
}

// tao node cho cay
TREE_DOCGIA CreateNode(DOCGIA init)
{
    TREE_DOCGIA p = new node_docgia;
    p->dataDocGia = init;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void CreateTree(TREE_DOCGIA &root){
    root = NULL;
}

// huy cay
void DestroyTree(TREE_DOCGIA &root){
    if (root)
    {
        DestroyTree(root->left);
        DestroyTree(root->right);
        delete root;
    }
}

// them node cho cay
void AddNode(TREE_DOCGIA &root,TREE_DOCGIA node)
{
    if (root)
    {
        // kiem tra khong them gia tri trung
        if (root->dataDocGia.maThe == node->dataDocGia.maThe)
            return;
        if (node->dataDocGia.maThe < root->dataDocGia.maThe)
            AddNode(root->left, node);
        else
            AddNode(root->right, node);
    }
    else
    {
        root = node;
    }
}

// tim ma the thich hop theo dung vi tri
void findNodeInTreeByPos(TREE_DOCGIA root,int vitri,int &count,int &maThe)
{
    if (root)
    {
        findNodeInTreeByPos(root->left,vitri,count,maThe);
        count++;
        if(maThe == -1 && count == vitri){
            maThe = root->dataDocGia.maThe;
            count = 0;
        }
        findNodeInTreeByPos(root->right,vitri,count,maThe);
    }
}

// tim node cuc trai
void FindAndReplace(TREE_DOCGIA &p, TREE_DOCGIA &tree)
{
    if (tree->left)
        FindAndReplace(p, tree->left);
    else
    {
        p->dataDocGia = tree->dataDocGia;
        p = tree;
        tree = tree->right;
    }
}

// xoa mot node trong cay
void DeleteNode(TREE_DOCGIA &root, int maThe)
{
    if (root)
    {
        if (maThe > root->dataDocGia.maThe)
            DeleteNode(root->right, maThe);
        else if (maThe < root->dataDocGia.maThe)
            DeleteNode(root->left, maThe);
        else
        {
            TREE_DOCGIA p = root;
            if (!root->left)
                root = root->right;
            else if (!root->right)
                root = root->left;
            else
                FindAndReplace(p, root->right);
            delete p;
        }
    }
    else
    {
        cout << "Not found!\n";
    }
}



// tim node theo ma the
TREE_DOCGIA findNodeInTreeById(TREE_DOCGIA root, int maThe)
{
   TREE_DOCGIA p = root;
   while (p != NULL && p->dataDocGia.maThe != maThe){
        if(maThe < p->dataDocGia.maThe)
            p = p->left;
        else
            p = p->right;
   }
    return p;
}

// sinh ma tu dong cho the doc gia
void sinhMaTuDongTheDocGia(int a[],int n){
    int b = n, bac = 0, bacTruoc, KC, bn, bl, giaTriDau;
    a[0] = n/2 + 1;
    for(int i = 1;i < n;i++){
        b = b / 2;
        a[i++] = b / 2 + 1;
        a[i] = a[i - 1] + a[i - (int)pow(2,bac) - 1];
        bac++;
        bn = (int)pow(2,bac);
        bacTruoc = bac - 1;
        bl = 0;
        giaTriDau = a[i - 1];
        while(bn > 2){
            KC = (int)pow(2,bacTruoc) + bl;
            i++;
            a[i] = a[i - KC - 1] - giaTriDau;
            i++;
            a[i] = a[i - KC - 2] + giaTriDau;
            bl++;
            bn -= 2;
        }
    }
}

void PrintTree(TREE_DOCGIA root)// print tree using LNR
{
    if (root)
    {
        PrintTree(root->left);
        cout << root->dataDocGia.maThe << ' ';
        PrintTree(root->right);
    }
}

// do du lieu cho viec sap xep theo ten
void DoDuLieu(TREE_DOCGIA root,listName &listIndex,int &i){
    if(root){
        DoDuLieu(root->left,listIndex,i);
        listIndex.nodes[i].maThe = root->dataDocGia.maThe;
        listIndex.nodes[i].ten = root->dataDocGia.ten;
        listIndex.nodes[i].ho = root->dataDocGia.ho;
        i++;
        DoDuLieu(root->right,listIndex,i);
    }
}

// do ma the va so ngay qua han lon nhat de sap xep theo so ngay qua han
void DoDuLieuSoNgayQuaHan(TREE_DOCGIA root,listSoNgayQuaHan &listIndex,int &i,string ngayHienTai,int max = -1,int soNgayQuaHan = -1){
    if(root){
        DoDuLieuSoNgayQuaHan(root->left,listIndex,i,ngayHienTai);
        for(PTR_MUONTRA p = root->dataDocGia.ptr_muontra;p != NULL;p = p->next){
            if(p->dataMuonTra.trangThai == 0){
                soNgayQuaHan = soNgayMuonSach(p->dataMuonTra.ngayMuon,ngayHienTai);
                if(soNgayQuaHan > 7 && soNgayQuaHan > max)
                    max = soNgayQuaHan - 7;
            }
        }
        if(max != -1){
            listIndex.nodes[i].maThe = root->dataDocGia.maThe;
            listIndex.nodes[i].soNgayQuaHan = max;
            i++;
        }
        DoDuLieuSoNgayQuaHan(root->right,listIndex,i,ngayHienTai);
    }
}

// tong so nut hien co cua cay
void soNutCuaCay(TREE_DOCGIA root,int &count){
    if(root){
        soNutCuaCay(root->left, count);
        count++;
        soNutCuaCay(root->right,count);
    }
}

// sap xep theo chi so tong so luong muon
void IndexByBookBorrowTimesNumber(DS_DAUSACH &ds,listBookBorrowTimesNumber &listIndex){
    int sl = 0;
    for(int i = 0;i < ds.sl;i++){
        if(ds.dsdsach[i]->soLuongMuon > 0)
            sl++;
    }
    listIndex.nodes = new IndexBookBorrowTimesNumber[sl];
    listIndex.n = sl;
    sl = 0;
    for(int i = 0;i < ds.sl;i++){
        if(ds.dsdsach[i]->soLuongMuon > 0){
            listIndex.nodes[sl].chiso = i;
            listIndex.nodes[sl].soLuongMuon = ds.dsdsach[i]->soLuongMuon;
            sl++;
        }
	}
	// Sap xep theo  du lieu da do qua
	for(int i = 0;i < listIndex.n - 1;i++){
		for(int j = i + 1;j < listIndex.n;j++){
			if(listIndex.nodes[i].soLuongMuon < listIndex.nodes[j].soLuongMuon)
				swap(listIndex.nodes[i],listIndex.nodes[j]);
		}
	}
}

// sap xep theo ten va ho tang dan
void IndexByName(TREE_DOCGIA root,listName &listIndex){
    int i = 0;
    soNutCuaCay(root,i);
    listIndex.n = i;
    listIndex.nodes = new IndexName[listIndex.n];
    i = 0;
    DoDuLieu(root,listIndex,i);
    for(i = 0;i < listIndex.n - 1;i++){
        for(int j = i + 1;j < listIndex.n;j++){
            if((listIndex.nodes[i].ten > listIndex.nodes[j].ten) || ((listIndex.nodes[i].ten == listIndex.nodes[j].ten) &&
                                                                     (listIndex.nodes[i].ho > listIndex.nodes[j].ho)))
				swap(listIndex.nodes[i],listIndex.nodes[j]);
        }
    }
}

//Tinh tien dung vi tri trong dslk
PTR_SACH tinhTienVitriDSLK(PTR_SACH p,int vitri){
    for(int i = 0;i < vitri;i++)
            p = p->next;
    return p;
}


// Tao node cho sach
PTR_SACH CreateNodeSach(SACH data_book){
	PTR_SACH p = new node_sach;
	p->dataSach = data_book;
	p->next = NULL;
	return p;
}

PTR_MUONTRA CreateNodeMuonTra(MUONTRA data_mtra){
	PTR_MUONTRA p = new node_muontra;
	p->dataMuonTra = data_mtra;
	p->next = NULL;
	return p;
}

// them sach vao dau
void addFirst(PTR_SACH &head,SACH data_book){
	PTR_SACH p = CreateNodeSach(data_book);
	if(head == NULL)
		head = p;
	else{
		p->next = head;
		head = p;
	}
}

// them muon tra vao dau
void addFirstMuonTra(PTR_MUONTRA &head,MUONTRA data_mTra){
	PTR_MUONTRA p = CreateNodeMuonTra(data_mTra);
	if(head == NULL)
		head = p;
	else{
		p->next = head;
		head = p;
	}
}

// dem so phan tu cua dslk
int length(PTR_SACH head){
    PTR_SACH p;
    int count = 0;
    for(p = head;p != NULL;p = p->next)
        count++;
    return count;
}

// xoa dau trong dslk
void delBeg(PTR_SACH &head){
    PTR_SACH q;
    if(head != NULL){
        q = head;
        head = head->next;
        delete q;
    }
}

// xoa giua trong dslk
void delMid(PTR_SACH head,PTR_SACH q){
    PTR_SACH r;
    for(r = head;r->next != q;r = r->next);
    r->next = q->next;
    delete q;
}


// Xoa vi tri bat ky trong dslk
void delAt(PTR_SACH &head,int pos){
    int n,i;
    PTR_SACH q,p;
    n = length(head);
    if((pos < 0) || (pos >= n)){
        cout<<"Vitri xoa khong phu hop";
        return;
    }
    if(pos == 0)
        delBeg(head);
    else{
         p = tinhTienVitriDSLK(head,pos);
         delMid(head,p);
    }
}

// ve hop
void boxDoAn(int x,int y,int w,int h,int bcolor,int tcolor){
	SetColor(11);
	for(int ix=x;ix<=x+w;ix++){
		gotoxy(ix,y);
		cout<<char(205);
		gotoxy(ix,y+h);
		cout<<char(205);
	}
	for(int iy=y;iy<=y+h;iy++){
		gotoxy(x,iy);
		cout<<char(186);
		gotoxy(x+w,iy);
		cout<<char(186);
	}
	gotoxy(x,y);
	cout<<char(201);
	gotoxy(x+w,y);
	cout<<char(187);
	gotoxy(x,y+h);
	cout<<char(200);
	gotoxy(x+w,y+h);
	cout<<char(188);

	SetColor(tcolor);
	SetBGColor(bcolor);
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetBGColor(0);
}

// ve nhieu hop
void nboxDoAn(int x,int y,int bcolor,int tcolor,int sl,int w[],int h){
	int hi[2]={2,11};
	int ix = x;
	int iy = y;
	bool flag = false;
	if(h == 1)
		flag = true;
	else if(h == 0)
		hi[0] = 11;
	hi[1] = h;
	h = hi[0];
	for(int i = 0;i<sl;i++){
		boxDoAn(x,y,w[i],h,bcolor,tcolor);
		x = x + w[i] + 1;
		if(i == (sl - 1) && flag == false){
			x = ix;
			y = iy + hi[0] +1;
			i = -1;
			h = hi[1];
			flag = true;
		}
	}
}

// nhap du lieu cho dau sach, sach trong dau sach va doc gia
int DataInput(int x,int &y,int &i,string &s,string tenNhap){
    if(i != 0){
        SetBGColor(1);
        xoaNoiDung(25,y - 1,30);
    }
    SetBGColor(15);
    SetColor(0);
	char kyTu;
	while(true){
		gotoxy(x,y);
		kyTu = getch();
		if(kyTu == -32){
			kyTu = getch();
			if(kyTu == DOWN && y != 17)
			{
				i++;
				y += 2;
				break;
			}else if(kyTu == UP && y != 5)
			{
			    if(y == 7 && (tenNhap == "SACH" || tenNhap == "HIEUCHINHDAUSACH" || tenNhap == "DOCGIA"))
                    continue;
				i--;
				y -= 2;
				break;
			}
		}
		else if(kyTu == ESC){
			Normal();
			return 0;
		}
		else if(kyTu == BACKSPACE)
		{
			if(x == 25)
				continue;
			x--;
			s = s.substr(0,s.length() - 1);
			gotoxy(x,y);
			cout<<" ";
		}
		else if(kyTu == ENTER){
			i++;
			y += 2;
			break;
		}else{
		    toUpper(kyTu);
		    if(x == 53)
                continue;
		    if(i >= 0 && i <= 3){
                if(i != 2 || tenNhap != "SACH")
                {
                    if(i != 3 || tenNhap != "DOCGIA"){
                        if((kyTu >= 65 && kyTu <= 90) || kyTu == ' '){
                            gotoxy(x,y);
                            cout<<kyTu;
                            s += kyTu;
                            x++;
                        }
                    }
                }
		    }
		    if(i == 4 || i == 5 || (i == 1 && tenNhap != "DOCGIA") || (i == 2 && tenNhap == "SACH") || (i == 3 && tenNhap == "DOCGIA")){
                if(kyTu >= 48 && kyTu <= 57){
                    gotoxy(x,y);
                    cout<<kyTu;
                    s += kyTu;
                    x++;
                }
		    }
		    if(tenNhap == "SACH" && kyTu == '-' && i != 2){
                    gotoxy(x,y);
                    cout<<kyTu;
                    s += kyTu;
                    x++;
		    }
		}
	}
	return 1;
}

// khung tthd nhap doc gia
void KhungTTHDNhapDocGia(string tenNhap){
	int x = 61, y = 0,h = 13,w = 50;
	int ix = x + 2;
	int iy = y + 1;
	int bcolor = 6;
	boxDoAn(x,y,w,h,bcolor,7);
	SetBGColor(7);
	SetColor(0);
	gotoxy(canhChuKhoangCach(32,w) + x,iy);
	cout<<"THONG TIN HUONG DAN NHAP DOC GIA";
	SetBGColor(bcolor);
	SetColor(15);
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Ma doc gia: Duoc sinh tu dong!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Ho: Nhap tu 2 - > 25 ky tu, chi nhan chu!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Ten: Nhap tu 2 - > 10 ky tu, chi nhan chu!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Phai: Chon 1: Nam - 0: Nu!";
	iy += 2;
	gotoxy(ix,iy);
	if(tenNhap == "HIEUCHINH")
        cout<<"Trang thai: Chon 0: Khoa the - 1: Hoat dong!";
    else
        cout<<"Trang thai: Mac dinh la the hoat dong!";
	Normal();
}

//khung nhap muon tra sach
void KhungNhapMuonTraSach(int x,int y,int kiemTra = 1){
    int ix = x, iy = y,h = 10, w = 60;
    int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
    SetBGColor(7);
	h = 4;
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
    SetColor(0);
    if(kiemTra == 1){
        gotoxy(canhChuKhoangCach(9,w) + x,2 + y);
        cout<<"MUON SACH";
    }else if(kiemTra == 0){
        gotoxy(canhChuKhoangCach(8,w) + x,2 + y);
        cout<<"TRA SACH";
    }else{
        gotoxy(canhChuKhoangCach(12,w) + x,2 + y);
        cout<<"BAO MAT SACH";
    }


	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2 + x,5 + y);
	cout<<"Ma sach: ";
    gotoxy(2 + x,7 + y);
    if(kiemTra == 1)
        cout<<"Ngay muon: ";
    else if(kiemTra == 0)
        cout<<"Ngay tra";

	//Textfield
	SetBGColor(15);
	//SetColor(14);
	int i = 30;
	ix = 25 + x;
	iy = y + 5;
	while(iy != y + 9){
        if(iy == 19 && kiemTra == 2)
            break;
		while(i > 0){
            if(iy == 19){
                if((ix >= 33 && ix <= 35) || (ix >= 44 && ix <= 46))
                    SetBGColor(1);
            }
            gotoxy(ix,iy);
            cout<<" ";
			ix++;
			i--;
            SetBGColor(15);
		}
		iy += 2;
		ix = 25 + x;
		i = 30;
	}

	SetBGColor(4);
	SetColor(14);
	if(kiemTra == 1){
        gotoxy(27 + x,y + 9);
        cout<<"MUON";
	}
	else if(kiemTra == 0){
        gotoxy(29 + x,y + 9);
        cout<<"TRA";
	}else{
        gotoxy(25 + x,y + 9);
        cout<<"BAO MAT";
	}

	Normal();

}

// khung nhap doc gia
void KhungNhapDocGia(){
	int x = 0, y = 0,h = 17,w = 60;
	int ix = x;
	int iy = y;
	int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
	//SetColor(tcolor);
	SetBGColor(7);
	h = 4;
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetColor(0);
	gotoxy(canhChuKhoangCach(16,w),2);
	cout<<"THEM MOI DOC GIA";

	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2,5);
	cout<<"Ma doc gia: ";
	gotoxy(2,7);
	cout<<"Ho doc gia: ";
	gotoxy(2,9);
	cout<<"Ten doc gia: ";
	gotoxy(2,11);
	cout<<"Phai: ";
	gotoxy(2,13);
	cout<<"Trang thai: ";

	//Textfield
	SetBGColor(15);
	//SetColor(14);
	int i = 30;
	ix = 25;
	iy = 5;
	while(iy != 15){
		while(i > 0){
            if(iy == 5 || iy == 13)
                SetBGColor(8);
			gotoxy(ix,iy);
			cout<<" ";
			ix++;
			i--;
            SetBGColor(15);
		}
		iy += 2;
		ix = 25;
		i = 30;
	}

	SetBGColor(4);
	SetColor(14);
	gotoxy(27,15);
	cout<<"THEM";
	Normal();

	KhungTTHDNhapDocGia("");
}

// khung hieu chinh doc gia
void KhungHieuChinhDocGia(){
	int x = 0, y = 0,h = 17,w = 60;
	int ix = x;
	int iy = y;
	int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
	//SetColor(tcolor);
	SetBGColor(7);
	h = 4;
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetColor(0);
	gotoxy(canhChuKhoangCach(16,w),2);
	cout<<"HIEU CHINH DOC GIA";

	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2,5);
	cout<<"Ma doc gia: ";
	gotoxy(2,7);
	cout<<"Ho doc gia: ";
	gotoxy(2,9);
	cout<<"Ten doc gia: ";
	gotoxy(2,11);
	cout<<"Phai: ";
	gotoxy(2,13);
	cout<<"Trang thai: ";

	//Textfield
	SetBGColor(15);
	//SetColor(14);
	int i = 30;
	ix = 25;
	iy = 5;
	while(iy != 15){
		while(i > 0){
            if(iy == 5)
                SetBGColor(8);
			gotoxy(ix,iy);
			cout<<" ";
			ix++;
			i--;
            SetBGColor(15);
		}
		iy += 2;
		ix = 25;
		i = 30;
	}

	SetBGColor(4);
	SetColor(14);
    gotoxy(canhChuKhoangCach(12,60),15);
    cout<<"LUU THAY DOI";
	Normal();

	KhungTTHDNhapDocGia("HIEUCHINH");
}

// khung tthd nhap sach
void KhungTTHDNhapSach(string tenNhap){
	int x = 61, y = 0,h = 9,w = 50;
	int ix = x + 2;
	int iy = y + 1;
	int bcolor = 6;
	boxDoAn(x,y,w,h,bcolor,7);
	SetBGColor(7);
	SetColor(0);
	gotoxy(canhChuKhoangCach(32,w) + x,iy);
	cout<<"THONG TIN HUONG DAN NHAP SACH";
	SetBGColor(bcolor);
	SetColor(15);
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Ma sach: Duoc sinh tu dong!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Vi tri: Nhap chu va so hoac -, toi da 25 ky tu!";
	iy += 2;
	gotoxy(ix,iy);
	if(tenNhap == "HIEUCHINH")
        cout<<"Trang thai: 0: Chua muon 1: Da muon 2: Thanh ly";
    else
        cout<<"Trang thai: Sach mac dinh la co the muon duoc!";
	Normal();
}

// Khung hieu chinh sach trong dau sach
void KhungHieuChinhSachTrongDauSach(PTR_SACH head,int vitri){
	int x = 0, y = 0,h = 13,w = 60;
	int ix = x;
	int iy = y;
	int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
	SetBGColor(7);
	h = 4;
	PTR_SACH p;
	p = tinhTienVitriDSLK(head,vitri);
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetColor(0);
	gotoxy(canhChuKhoangCach(30,w),2);
	cout<<"HIEU CHINH SACH TRONG DAU SACH";

	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2,5);
	cout<<"Ma sach: ";
	gotoxy(2,7);
	cout<<"Vi tri: ";
	gotoxy(2,9);
	cout<<"Trang thai: ";

	//Textfield
	SetBGColor(15);
	int i = 30;
	ix = 25;
	iy = 5;
	while(iy != 11){
        while(i > 0){
            if(iy == 5)
                SetBGColor(8);
            gotoxy(ix,iy);
            cout<<" ";
            ix++;
            i--;
            SetBGColor(15);
        }
        i = 30;
        ix = 25;
        iy += 2;
	}

    ix = 25;
	iy = 5;
	gotoxy(canhChuKhoangCach(8,27) + ix,iy);
	SetBGColor(8);
	SetColor(15);
	cout<<p->dataSach.maSach;
	iy += 2;
	gotoxy(ix,iy);
	SetBGColor(15);
	SetColor(0);
	cout<<p->dataSach.vitri;
	iy += 2;
	gotoxy(ix,iy);
	cout<<p->dataSach.trangThai;


	SetBGColor(4);
	SetColor(14);
	gotoxy(canhChuKhoangCach(12,60),11);
	cout<<"LUU THAY DOI";
	Normal();

	KhungTTHDNhapSach("HIEUCHINH");
}

// Hieu chinh sach trong dau sach
int HieuChinhSachTrongDauSach(DS_DAUSACH &ds,int luachon,int vitri){
	hidecursor(true);
	KhungHieuChinhSachTrongDauSach(ds.dsdsach[luachon]->listSach.head,vitri);
    PTR_SACH p,q;
    p = tinhTienVitriDSLK(ds.dsdsach[luachon]->listSach.head,vitri);
    q = p;
	SACH sch = q->dataSach;
	SetBGColor(15);
	SetColor(0);
	char kyTu;
	int x = 25,y = 7,i = 1;
	string s[3] = {""};
 	s[1] = sch.vitri;
	s[2] = changeToString(sch.trangThai);
//    s[1] = "KE 1";
	//s[2] = "0";
	int giaTri;
	while(i < 3){
        giaTri = DataInput(x + s[i].length(),y,i,s[i],"SACH");
        if(giaTri == 0)
            return 0;
        if((s[1].length() > 25 || s[1].length() < 5) && i == 2){
            SetBGColor(1);
            SetColor(10);
            i = 1;
            y -= 2;
            ThongBao(25,8,"Vitri nhap 5 -> 25 ky tu");
        }else if((atoi(s[2].c_str()) < 0 || atoi(s[2].c_str()) > 2) && i == 3){
            SetBGColor(1);
            SetColor(10);
            i = 2;
            y -= 2;
            ThongBao(25,10,"Trang thai nhap so 0 -> 2");
        }

    }
    SetBGColor(1);
    xoaNoiDung(25,10,35);

        sch.vitri = s[1];
		sch.trangThai = atoi(s[2].c_str());
        q->dataSach = sch;
		SetBGColor(14);
		SetColor(0);
		gotoxy(canhChuKhoangCach(12,60),11);
		cout<<"LUU THAY DOI";
        hidecursor(false);
		while(true){
			kyTu = getch();
			if(kyTu == ENTER)
			{
				p = q;
				break;
			}
			if(kyTu == ESC){
				Normal();
				return 0;
			}
		}
		Normal();
	return 1;
}

// Khung nhap sach trong dau sach
void KhungNhapSach(){
	int x = 0, y = 0,h = 13,w = 60;
	int ix = x;
	int iy = y;
	int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
	SetBGColor(7);
	h = 4;
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetColor(0);
	gotoxy(canhChuKhoangCach(29,w),2);
	cout<<"THEM MOI SACH TRONG DAU SACH";

	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2,5);
	cout<<"Ma sach: ";
	gotoxy(2,7);
	cout<<"Vi tri: ";
	gotoxy(2,9);
	cout<<"Trang thai: ";

	//Textfield
	SetBGColor(15);
	//SetColor(14);
	int i = 30;
	ix = 25;
	iy = 5;
	while(iy != 11){
        while(i > 0){
            if(iy == 5 || iy == 9)
                SetBGColor(8);
            gotoxy(ix,iy);
            cout<<" ";
            ix++;
            i--;
            SetBGColor(15);
        }
        i = 30;
        ix = 25;
        iy += 2;
	}

	SetBGColor(4);
	SetColor(14);
	gotoxy(27,11);
	cout<<"THEM";
	Normal();

	KhungTTHDNhapSach("");
}

// khung tthd nhap dau sach
void KhungTTHDNhapDauSach(){
	int x = 61, y = 0,h = 15,w = 50;
	int ix = x + 2;
	int iy = y + 1;
	int bcolor = 6;
	boxDoAn(x,y,w,h,bcolor,7);
	SetBGColor(7);
	SetColor(0);
	gotoxy(canhChuKhoangCach(32,w) + x,iy);
	cout<<"THONG TIN HUONG DAN NHAP DAU SACH";
	SetBGColor(bcolor);
	SetColor(15);
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Ma dau sach: Phai chua 4 ky tu, chi nhan chu!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Ten sach: Tu 5 -> 28 ky tu, chi nhan chu!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Tac gia: Tu 7 -> 25 ky tu, chi nhan chu!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"The loai: Tu 5 -> 25 ky tu, chi nhan chu!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"So trang: Nhap so phai nho hon 10000!";
	iy += 2;
	gotoxy(ix,iy);
	cout<<"Nam xuat ban: Nhap nam nho hon nam hien tai!";
	//gotoxy(25,5);
	Normal();
}

// khung nhap dau sach
void KhungNhapDauSach(){
	int x = 0, y = 0,h = 19,w = 60;
	int ix = x;
	int iy = y;
	int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
	//SetColor(tcolor);
	SetBGColor(7);
	h = 4;
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetColor(0);
	gotoxy(canhChuKhoangCach(17,w),2);
	cout<<"THEM MOI DAU SACH";

	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2,5);
	cout<<"Ma dau sach (ISBN): ";
	gotoxy(2,7);
	cout<<"Ten sach: ";
	gotoxy(2,9);
	cout<<"Tac gia: ";
	gotoxy(2,11);
	cout<<"The loai: ";
	gotoxy(2,13);
	cout<<"So trang: ";
	gotoxy(2,15);
	cout<<"Nam xuat ban: ";

	//Textfield
	SetBGColor(15);
	//SetColor(14);
	int i = 30;
	ix = 25;
	iy = 5;
	while(iy != 17){
		while(i > 0){
			gotoxy(ix,iy);
			cout<<" ";
			ix++;
			i--;
		}
		iy += 2;
		ix = 25;
		i = 30;
	}

	SetBGColor(4);
	SetColor(14);
	gotoxy(27,17);
	cout<<"THEM";
	Normal();

	KhungTTHDNhapDauSach();
}

// khung Hieu chinh cho dau sach
void KhungHieuChinhDauSach(DS_DAUSACH &ds,int vitri){
	int x = 0, y = 0,h = 19,w = 60;
	int ix = x;
	int iy = y;
	int bcolor = 1;
	boxDoAn(x,y,w,h,bcolor,7);
	//SetColor(tcolor);
	SetBGColor(7);
	h = 4;
	for(int iy = y + 1;iy <= y + h - 1;iy++){
		for(int ix = x + 1;ix <= x + w - 1;ix++){
			gotoxy(ix,iy);
			cout<<" ";
		}
	}
	SetColor(0);
	gotoxy(canhChuKhoangCach(19,w),2);
	cout<<"HIEU CHINH DAU SACH";

	// Lable
	SetBGColor(bcolor);
	SetColor(14);
	gotoxy(2,5);
	cout<<"Ma dau sach (ISBN): ";
	gotoxy(2,7);
	cout<<"Ten sach: ";
	gotoxy(2,9);
	cout<<"Tac gia: ";
	gotoxy(2,11);
	cout<<"The loai: ";
	gotoxy(2,13);
	cout<<"So trang: ";
	gotoxy(2,15);
	cout<<"Nam xuat ban: ";

	//Textfield
	SetBGColor(15);
	SetColor(0);
	int i = 30;
	ix = 25;
	iy = 5;
	while(iy != 17){
		while(i > 0){
            if(iy == 5)
                SetBGColor(8);
			gotoxy(ix,iy);
			cout<<" ";
			ix++;
			i--;
		}
		iy += 2;
		ix = 25;
		i = 30;
		SetBGColor(15);
	}




	ix = 25;
	iy = 5;
	gotoxy(canhChuKhoangCach(4,27) + ix,iy);
	SetBGColor(8);
	SetColor(15);
	cout<<ds.dsdsach[vitri]->ISBN;
	iy += 2;
	gotoxy(ix,iy);
	SetBGColor(15);
	SetColor(0);
	cout<<ds.dsdsach[vitri]->tenSach;
	iy += 2;
	gotoxy(ix,iy);
	cout<<ds.dsdsach[vitri]->tacGia;
	iy += 2;
	gotoxy(ix,iy);
	cout<<ds.dsdsach[vitri]->theLoai;
	iy += 2;
	gotoxy(ix,iy);
	cout<<ds.dsdsach[vitri]->soTrang;
	iy += 2;
	gotoxy(ix,iy);
	cout<<ds.dsdsach[vitri]->namXuatBan;

	SetBGColor(4);
	SetColor(14);
	gotoxy(canhChuKhoangCach(12,w),17);
	cout<<"LUU THAY DOI";
	Normal();

	KhungTTHDNhapDauSach();
}

// hieu chinh dau sach
int HieuChinhDauSach(DS_DAUSACH &ds,int vitri){
	hidecursor(true);
	KhungHieuChinhDauSach(ds,vitri);
	DAUSACH dsach = *ds.dsdsach[vitri];
	SetBGColor(15);
	SetColor(0);
	char kyTu;
	int x = 25,y = 7,i = 1;
	string s[6] = {""};
 	s[1] = dsach.tenSach;
	s[2] = dsach.tacGia;
	s[3] = dsach.theLoai;
	s[4] = changeToString(dsach.soTrang);
	s[5] = changeToString(dsach.namXuatBan);
	int giaTri;
		while(i < 6){
			giaTri = DataInput(x + s[i].length(),y,i,s[i],"HIEUCHINHDAUSACH");
			if(giaTri == 0)
				return 0;
            if((s[1].length() < 5 || s[1].length() > 28) && i == 2){
                i = 1;
                y -= 2;
                SetBGColor(1);
                SetColor(10);
                ThongBao(25,8,"Ten sach nam tu 5 -> 25 ky tu");
                Normal();
            }else if((s[2].length() < 7 || s[2].length() > 25) && i == 3){
                i = 2;
                y -= 2;
                SetBGColor(1);
                SetColor(10);
                ThongBao(25,10,"Ten sach nam tu 7 -> 25 ky tu");
                Normal();
            }else if((s[3].length() < 5 || s[3].length() > 25) && i == 4){
                i = 3;
                y -= 2;
                SetBGColor(1);
                SetColor(10);
                ThongBao(25,12,"Ten sach nam tu 5 -> 25 ky tu");
                Normal();
            }else if(atoi(s[4].c_str()) >= 10000 && i == 5){
                i = 4;
                y -= 2;
                SetBGColor(1);
                SetColor(10);
                ThongBao(25,14,"So trang phai nho hon 10000");
                Normal();
            }else if(atoi(s[5].c_str()) > 2021 && i == 6){
                i = 5;
                y -= 2;
                SetBGColor(1);
                SetColor(10);
                ThongBao(25,16,"Nam khong duoc vuot qua hien tai");
                Normal();
            }
        }
    SetBGColor(1);
    xoaNoiDung(25,16,35);

		dsach.tenSach = s[1];
		dsach.tacGia = s[2];
		dsach.theLoai = s[3];
		dsach.soTrang = atoi(s[4].c_str());
		dsach.namXuatBan = atoi(s[5].c_str());

		SetBGColor(14);
		SetColor(0);
		gotoxy(canhChuKhoangCach(12,60),17);
		cout<<"LUU THAY DOI";
        hidecursor(false);
		while(true){
			kyTu = getch();
			if(kyTu == ENTER)
			{
				*ds.dsdsach[vitri] = dsach;
				break;
			}
			if(kyTu == ESC){
				Normal();
				return 0;
			}
		}
		Normal();
	return 1;
}

// kiem tra ma dau sach trung
int kiemTraMaDauSachTrung(DS_DAUSACH &ds,string s){
    for(int i = 0;i < ds.sl;i++){
        if(ds.dsdsach[i]->ISBN == s)
            return 1;
    }
    return 0;
}

// Nhap dau sach
int  NhapDauSach ( ds_dausach &ds, DAUSACH &dsach){
	KhungNhapDauSach();
	Normal();
	SetBGColor(15);
	SetColor(0);
	char kyTu;
	int x = 25,y = 5,i = 0;
	string s[6] = {""};
	int giaTri;
    while(i < 6){
        SetBGColor(15);
        SetColor(0);
        giaTri = DataInput(x + s[i].length(),y,i,s[i],"DAUSACH");
        if(giaTri == 0)
            return 0;

        if((s[0].length() != 4 || kiemTraMaDauSachTrung(ds,s[0]) == 1) && i == 1){
            i = 0;
            y -= 2;
            SetBGColor(1);
            SetColor(10);
            SetBGColor(1);
            xoaNoiDung(25,y + 1,30);
            if(s[0].length() == 4){
                ThongBao(25,6,"Ma dau sach da trung");
            }
            else
                ThongBao(25,6,"Ma dau sach phai chua 4 ky tu");
            Normal();
        }else if((s[1].length() < 5 || s[1].length() > 28) && i == 2){
            i = 1;
            y -= 2;
            SetBGColor(1);
            SetColor(10);
            ThongBao(25,8,"Ten sach nam tu 5 -> 25 ky tu");
            Normal();
        }else if((s[2].length() < 7 || s[2].length() > 25) && i == 3){
            i = 2;
            y -= 2;
            SetBGColor(1);
            SetColor(10);
            ThongBao(25,10,"Ten sach nam tu 7 -> 25 ky tu");
            Normal();
        }else if((s[3].length() < 5 || s[3].length() > 25) && i == 4){
            i = 3;
            y -= 2;
            SetBGColor(1);
            SetColor(10);
            ThongBao(25,12,"Ten sach nam tu 5 -> 25 ky tu");
            Normal();
        }else if(atoi(s[4].c_str()) >= 10000 && i == 5){
            i = 4;
            y -= 2;
            SetBGColor(1);
            SetColor(10);
            ThongBao(25,14,"So trang phai nho hon 10000");
            Normal();
        }else if(atoi(s[5].c_str()) > 2021 && i == 6){
            i = 5;
            y -= 2;
            SetBGColor(1);
            SetColor(10);
            ThongBao(25,16,"Nam khong duoc vuot qua hien tai");
            Normal();
        }
    }
    SetBGColor(1);
    xoaNoiDung(25,16,35);

    dsach.ISBN = s[0];
    dsach.tenSach = s[1];
    dsach.tacGia = s[2];
    dsach.theLoai = s[3];
    dsach.soTrang = atoi(s[4].c_str());
    dsach.namXuatBan = atoi(s[5].c_str());
    dsach.soLuongMuon = 0;
    dsach.listSach.head = NULL;
    dsach.listSach.maSachLonNhat = 0;
    dsach.listSach.n = 0;

    SetBGColor(14);
    SetColor(0);
    gotoxy(27,17);
    cout<<"THEM";

    hidecursor(false);
    while(true){
        kyTu = getch();
        if(kyTu == ENTER)
            break;
        if(kyTu == ESC){
            Normal();
            return 0;
        }
    }
    Normal();
	return 1;
}

// Nhap danh sach dau sach
void NhapDsDauSach (DS_DAUSACH &ds){
	hidecursor(true);
 	DAUSACH dsach;

 while (ds.sl < MAX)
 {
    if (NhapDauSach(ds, dsach) == 1)
    {
    	ds.dsdsach[ds.sl] = new DAUSACH;
    	*ds.dsdsach[ds.sl] = dsach;
    	ds.sl++;
	}
	else
		break;
 }
 hidecursor(false);
}

// Xoa dau sach
void XoaDauSach(DS_DAUSACH &ds,int vitri,bool &trangThai){
	if(ds.dsdsach[vitri]->listSach.n == 0){
		ThongBao(0,15,"Da xoa thanh cong ma dau sach " + ds.dsdsach[vitri]->ISBN);
		delete ds.dsdsach[vitri];
		for(int i = vitri + 1;i < ds.sl;i++)
			ds.dsdsach[i - 1] = ds.dsdsach[i];
		ds.sl--;
		trangThai = true;
	}
	else{
		ThongBao(0,15,"Xoa that bai do ma dau sach da co ma sach!");
	}
}


// Nhap sach cho dau sach
int  NhapSachTrongDauSach(DS_DAUSACH &ds, SACH &sch,int vitri){
	KhungNhapSach();
	Normal();
	SetBGColor(8);
	SetColor(15);
	char kyTu;
	int x = 25,y = 7,i = 1;
	string s = "";
	int giaTri;
	sch.maSach = ds.dsdsach[vitri]->ISBN + chuanHoaMaSach(ds.dsdsach[vitri]->listSach.maSachLonNhat + 1);
    gotoxy(x + canhChuKhoangCach(sch.maSach.length(),30),5);
    cout<<sch.maSach;
    sch.trangThai = 0;
    gotoxy(x + canhChuKhoangCach(1,30),9);
    cout<<sch.trangThai;
    SetBGColor(15);
	SetColor(0);
	while(i < 2){
        giaTri = DataInput(x + s.length(),y,i,s,"SACH");
        if(giaTri == 0)
            return 0;
        if((s.length() > 25 || s.length() < 5) && i == 2){
            SetBGColor(1);
            SetColor(10);
            i = 1;
            y -= 2;
            ThongBao(25,8,"Vitri nhap 5 -> 25 ky tu");
        }

    }
    SetBGColor(1);
    xoaNoiDung(25,8,30);

	sch.vitri = s;

    SetBGColor(14);
    SetColor(0);
    gotoxy(27,11);
    cout<<"THEM";
    hidecursor(false);

    while(true){
        kyTu = getch();
        if(kyTu == ENTER)
            break;
        if(kyTu == ESC){
            Normal();
            return 0;
        }
    }
    hidecursor(true);
    Normal();
	return 1;
}

// nhap doc gia
int  NhapDocGia(DOCGIA &dg,int maTheDocGia,int viTriMaThe){
	KhungNhapDocGia();
	Normal();
	SetBGColor(8);
	SetColor(15);
	char kyTu;
	int x = 25,y = 7,i = 1;
	string s[4] = {""};
	int giaTri;
    dg.viTriMaThe = viTriMaThe;
	dg.maThe = maTheDocGia;
    gotoxy(x + canhChuKhoangCach(3,30),5);
    cout<<dg.maThe;
    dg.trangThaiThe = 1;
    gotoxy(x + canhChuKhoangCach(1,30),13);
    cout<<dg.trangThaiThe;
    SetBGColor(15);
	SetColor(0);
	while(i < 4){
        giaTri = DataInput(x + s[i].length(),y,i,s[i],"DOCGIA");
        if(giaTri == 0)
            return 0;
        if((s[1].length() > 25 || s[1].length() < 2) && i == 2){
            SetBGColor(1);
            SetColor(10);
            gotoxy(0,19);
            i = 1;
            y -= 2;
            ThongBao(25,8,"Nhap ho tu 2 -> 25 ky tu");
        }else if((s[2].length() > 10 || s[2].length() < 2) && i == 3){
            SetBGColor(1);
            SetColor(10);
            i = 2;
            y -= 2;
            ThongBao(25,10,"Nhap ho tu 2 -> 10 ky tu");
        }else if((atoi(s[3].c_str()) != 0 && atoi(s[3].c_str()) != 1) && i == 4){
            SetBGColor(1);
            SetColor(10);
            i = 3;
            y -= 2;
            ThongBao(25,12,"Chi nhap 1 hoac 0");
        }

    }
    SetBGColor(1);
    xoaNoiDung(25,12,30);

    dg.ho = s[1];
    dg.ten = s[2];
    if(atoi(s[3].c_str()) == 1)
        dg.phai = "NAM";
    else
        dg.phai = "NU";
    dg.soLuongMuon = 0;
    dg.soLuongTra = 0;
    dg.ptr_muontra = NULL;

    SetBGColor(14);
    SetColor(0);
    gotoxy(27,15);
    cout<<"THEM";
    hidecursor(false);

    while(true){
        kyTu = getch();
        if(kyTu == ENTER)
            break;
        if(kyTu == ESC){
            Normal();
            return 0;
        }
    }
    hidecursor(true);
    Normal();
	return 1;
}

// nhap ds doc gia
void nhapDsDocGia(TREE_DOCGIA &root,int sl,int mangSinhTheDocGia[],int checkTheDocGia[],int &vitri){
    hidecursor(true);
    TREE_DOCGIA p;
	DOCGIA dg;
	while(sl > 0){
		if(NhapDocGia(dg,mangSinhTheDocGia[vitri],vitri) == 1){
            p = CreateNode(dg);
            AddNode(root,p);
            sl--;
            checkTheDocGia[vitri] = 1;
            vitri++;
		}else
            break;
	}
	hidecursor(false);
}

// hieu chinh doc gia
int HieuChinhDocGia(TREE_DOCGIA &root,int vitri,int maThe = -1){
	hidecursor(true);
	KhungHieuChinhDocGia();
	int count = 0;
	if(maThe == -1)
        findNodeInTreeByPos(root,vitri + 1,count,maThe);
	TREE_DOCGIA p = findNodeInTreeById(root,maThe);
	SetBGColor(8);
	SetColor(15);
	char kyTu;
	int x = 25,y = 7,i = 1;
	string s[5] = {""};
 	s[1] = p->dataDocGia.ho;
	s[2] = p->dataDocGia.ten;
	if(p->dataDocGia.phai == "NAM")
        s[3] = "1";
    else
        s[3] = "0";
	s[4] = changeToString(p->dataDocGia.trangThaiThe);
	int giaTri;
    gotoxy(x + canhChuKhoangCach(3,30),5);
    cout<<p->dataDocGia.maThe;
    SetBGColor(15);
	SetColor(0);
    gotoxy(x,7);
    cout<<p->dataDocGia.ho;
    gotoxy(x,9);
    cout<<p->dataDocGia.ten;
    gotoxy(x,11);
    cout<<atoi(p->dataDocGia.phai.c_str());
    gotoxy(x,13);
    cout<<p->dataDocGia.trangThaiThe;

	while(i < 5){
        giaTri = DataInput(x + s[i].length(),y,i,s[i],"DOCGIA");
        if(giaTri == 0)
            return 0;
        if((s[1].length() > 25 || s[1].length() < 2) && i == 2){
            SetBGColor(1);
            SetColor(10);
            gotoxy(0,19);
            cout<<s[i].length();
            i = 1;
            y -= 2;
            ThongBao(25,8,"Nhap ho tu 2 -> 25 ky tu");
        }else if((s[2].length() > 10 || s[2].length() < 2) && i == 3){
            SetBGColor(1);
            SetColor(10);
            i = 2;
            y -= 2;
            ThongBao(25,10,"Nhap ho tu 2 -> 10 ky tu");
        }else if((atoi(s[3].c_str()) != 0 && atoi(s[3].c_str()) != 1) && i == 4){
            SetBGColor(1);
            SetColor(10);
            i = 3;
            y -= 2;
            ThongBao(25,12,"Chi nhap 1 hoac 0");
        }else if((atoi(s[4].c_str()) != 0 && atoi(s[4].c_str()) != 1) && i == 5){
            SetBGColor(1);
            SetColor(10);
            i = 4;
            y -= 2;
            ThongBao(25,14,"Chi nhap 1 hoac 0");
        }

    }
    SetBGColor(1);
    xoaNoiDung(25,14,30);

    p->dataDocGia.ho = s[1];
	p->dataDocGia.ten = s[2];
	if(atoi(s[3].c_str()) == 1)
        p->dataDocGia.phai = "NAM";
    else
        p->dataDocGia.phai = "NU";
	p->dataDocGia.trangThaiThe = atoi(s[4].c_str());

		SetBGColor(14);
		SetColor(0);
		gotoxy(canhChuKhoangCach(12,60),15);
		cout<<"LUU THAY DOI";
        hidecursor(false);
		while(true){
			kyTu = getch();
			if(kyTu == ENTER)
			{
				//*ds.dsdsach[vitri] = dsach;
				break;
			}
			if(kyTu == ESC){
				Normal();
				return 0;
			}
		}
		Normal();
	return 1;
}

// Xoa doc gia
void XoaDocGia(TREE_DOCGIA &root,int vitri,bool &trangThai,int maThe = -1){
    int count = 0;
    if(maThe == -1)
        findNodeInTreeByPos(root,vitri + 1,count,maThe);
    TREE_DOCGIA p = findNodeInTreeById(root,maThe);
	if(p->dataDocGia.soLuongMuon == 0){
		ThongBao(0,15,"Da xoa thanh cong ma the doc gia " + changeToString(maThe));
		DeleteNode(root,maThe);
		trangThai = true;
	}
	else{
		ThongBao(0,20,"Xoa that bai do doc gia da co muon sach!");
	}
}



// Nhap danh sach cho dau sach
void nhapDsSach(DS_DAUSACH &ds,int sl,int vitri){
    hidecursor(true);
	SACH book;
	while(sl > 0){
		if(NhapSachTrongDauSach(ds,book,vitri) == 1){
            addFirst(ds.dsdsach[vitri]->listSach.head,book);
            sl--;
            ds.dsdsach[vitri]->listSach.n++;
            ds.dsdsach[vitri]->listSach.maSachLonNhat++;
		}else
            break;
	}
	hidecursor(false);
}

// xoa sach trong dau sach
void XoaSachTrongDauSach(DS_DAUSACH &ds,int vitri,int delPos,bool &trangThai){
    PTR_SACH p;
    p = tinhTienVitriDSLK(ds.dsdsach[vitri]->listSach.head,delPos);
	if(p->dataSach.trangThai == 0 || p->dataSach.trangThai == 2){
		ThongBao(0,15,"Da xoa thanh cong ma sach " + p->dataSach.maSach);
		delAt(ds.dsdsach[vitri]->listSach.head,delPos);
		ds.dsdsach[vitri]->listSach.n--;
		trangThai = true;
	}
	else{
		ThongBao(0,15,"Xoa that bai do ma sach da co doc gia muon!");
	}
}


// Xuat cac sach cua dau sach
void XuatSachTrongKhung(DS_DAUSACH &ds,int luachon,int vitri,int trangHienTai,int trangCuoi,string tenNhap){
	system("cls");
	list_NodeSach list = ds.dsdsach[luachon]->listSach;
	SACH sch;
	PTR_SACH p = list.head;
	int x = 0,y = 0,h = 11,bcolor = 0,tcolor = 7;
	int ix = x,iy = y;
	int w[6] = {11,30,16},sl = 3;
	int slConLai = ds.dsdsach[luachon]->listSach.n - vitri, count = 0;
	string tieude[3] = {"Ma sach","Vi tri sach","Trang thai"};
	if(slConLai >= 10){
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
		gotoxy(90,15);
		cout<<"Trang "<<trangHienTai<<" / "<<trangCuoi;
	}
	else{
		h = slConLai + 1;
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
		if(slConLai != 0){
			gotoxy(90,h + 4);
			cout<<"Trang "<<trangHienTai<<" / "<<trangCuoi;
		}
	}
    if(tenNhap != "MUONTRA"){
        gotoxy(2,25);
        cout<<"INSERT - THEM";
        gotoxy(32,25);
        cout<<"DELETE - XOA";
        gotoxy(62,25);
        cout<<"F2 - SUA";
    }
	gotoxy(2,27);
	cout<<"ESC - THOAT";
	gotoxy(32,27);
	cout<<"PGUP - TRANG TRUOC";
	gotoxy(62,27);
	cout<<"PGDOWN - TRANG SAU";
	SetColor(14);
	// Ve khung tieu de
	for(int i = 0;i < sl;i++){
		gotoxy(ix + canhChuKhoangCach(tieude[i].length(),w[i]),iy + 1);
		cout<<tieude[i];
		ix = ix + w[i] + 1;
	}
	if(slConLai != 0){
		ix = x;
		iy = y + 4;
		SetColor(15);
		// Tinh tien den vi tri thich hop
		p = tinhTienVitriDSLK(p,vitri);
		for(int i = 0;i < slConLai;i++){
			gotoxy(ix + 2,iy + i);
			cout<<p->dataSach.maSach;
			ix = ix + w[0] + 1;
			gotoxy(ix + 2,iy + i);
			cout<<p->dataSach.vitri;
			ix = ix + w[1] + 1;
			gotoxy(ix + 2,iy + i);
			if(p->dataSach.trangThai == 0)
                cout<<"CHUA MUON";
            else if(p->dataSach.trangThai == 1)
                cout<<"DA MUON";
            else
                cout<<"THANH LY";
			p = p->next;
			count++;
			vitri++;
			ix = x;
			if(count == 10)
				break;
		}
		SetColor(0);
	}
}

// tim ten sach theo ma dau sach
string timSachTheoMaDauSach(DS_DAUSACH &ds,string maDauSach){
    for(int i = 0;i < ds.sl;i++){
        if(ds.dsdsach[i]->ISBN == maDauSach)
            return ds.dsdsach[i]->tenSach;
    }
    return "";
}

// liet ke sach dang muon
void LietKeSachDangMuon(TREE_DOCGIA &root,DS_DAUSACH &ds,int vitri,int maThe,string maSach,int kiemTra = 1){
	system("cls");
	TREE_DOCGIA p;
	PTR_MUONTRA First;
	int count = 0;
	if(maThe == -1)
        findNodeInTreeByPos(root,vitri + 1,count,maThe);
	p = findNodeInTreeById(root,maThe);
	First = p->dataDocGia.ptr_muontra;
	int x = 0,y = 0,h = 11,bcolor = 0,tcolor = 7;
	int ix = x,iy = y;
	int slSachDangMuon = p->dataDocGia.soLuongMuon - p->dataDocGia.soLuongTra;
	string tieude[6] = {"Ma sach","Ten sach","Ngay muon","Ngay tra","So ngay muon","Trang thai"};
	int w[6] = {11,31,13,13,15,13};
	int sl;
	if(kiemTra == 1){
        w[3] = 15;
        w[4] = 13;
        tieude[3] = "So ngay muon";
        tieude[4] = "Trang thai";
        sl = 5;
	}
    else{
        sl = 6;
    }

	if(slSachDangMuon == 0){
        if(maSach == "")
            h = 1;
        else
            h = 2;
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
	}
	else{
		h = slSachDangMuon + 1;
        if(maSach != "")
            h += 1;
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
	}

	gotoxy(2,27);
	cout<<"ESC - THOAT";
	gotoxy(20,27);

	if(kiemTra == 1)
        cout<<"F3 - MUON SACH";
    else if(kiemTra == 0){
        cout<<"F4 - TRA SACH";
        gotoxy(40,27);
        cout<<"F5 - BAO MAT SACH";
    }
	SetColor(14);
	// Ve khung tieu de
	for(int i = 0;i < sl;i++){
		gotoxy(ix + canhChuKhoangCach(tieude[i].length(),w[i]),iy + 1);
		cout<<tieude[i];
		ix = ix + w[i] + 1;
	}
	if(slSachDangMuon != 0 || (slSachDangMuon == 0 && maSach != "")){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string ngayHienTai = "";
        ngayHienTai = changeToString(ltm->tm_mday) + "-" + changeToString(ltm->tm_mon + 1) + "-" + changeToString(1900 + ltm->tm_year);
		ix = x;
		iy = y + 4;
		SetColor(15);
		PTR_MUONTRA q;
		int i = 0;
		if(kiemTra == 1){
            for(q = First;q != NULL;q = q->next){
                if(q->dataMuonTra.trangThai != 0)
                    continue;
                gotoxy(ix + 2,iy + i);
                cout<<q->dataMuonTra.maSach;
                ix = ix + w[0] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<timSachTheoMaDauSach(ds,q->dataMuonTra.maSach.substr(0,4));
                ix = ix + w[1] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<q->dataMuonTra.ngayMuon;
                ix = ix + w[2] + 1;
                gotoxy(ix + 6,iy + i);
                cout<<soNgayMuonSach(q->dataMuonTra.ngayMuon,ngayHienTai);
                ix = ix + w[3] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<"DANG MUON";
                count++;
                if(count == 3)
                    break;
                ix = x;
                i++;
            }
		}else{
            for(q = First;q != NULL;q = q->next){
                if(q->dataMuonTra.trangThai == 0 || ((q->dataMuonTra.trangThai == 1 || q->dataMuonTra.trangThai == 2) && q->dataMuonTra.maSach == maSach)){
                    gotoxy(ix + 2,iy + i);
                    cout<<q->dataMuonTra.maSach;
                    ix = ix + w[0] + 1;
                    gotoxy(ix + 2,iy + i);
                    cout<<timSachTheoMaDauSach(ds,q->dataMuonTra.maSach.substr(0,4));
                    ix = ix + w[1] + 1;
                    gotoxy(ix + 2,iy + i);
                    cout<<q->dataMuonTra.ngayMuon;
                    ix = ix + w[2] + 1;
                    gotoxy(ix + 2,iy + i);
                    cout<<q->dataMuonTra.ngayTra;
                    ix = ix + w[3] + 1;
                    gotoxy(ix + 6,iy + i);
                    if(q->dataMuonTra.trangThai != 1)
                        cout<<soNgayMuonSach(q->dataMuonTra.ngayMuon,ngayHienTai);
                    else
                        cout<<soNgayMuonSach(q->dataMuonTra.ngayMuon,q->dataMuonTra.ngayTra);
                    ix = ix + w[4] + 1;
                    gotoxy(ix + 2,iy + i);
                    if(q->dataMuonTra.trangThai == 1)
                        cout<<"DA TRA";
                    else if(q->dataMuonTra.trangThai == 0)
                        cout<<"DANG MUON";
                    else
                        cout<<"MAT SACH";
                    count++;
                    if(count == 3)
                        break;
                    ix = x;
                    i++;
                }
            }
		}

		SetColor(0);
	}
}

// Sap xep ten sach trong tung the loai
void indexByBookInGenre(DS_DAUSACH &ds,listBookInGenre &listIndex){
	listIndex.nodes = new IndexBookInGenre[ds.sl];
	listIndex.n = ds.sl;
	// Do du lieu qua de sap xep
	for(int i = 0;i < ds.sl;i++){
		listIndex.nodes[i].chiso = i;
		listIndex.nodes[i].tloai = ds.dsdsach[i]->theLoai;
		listIndex.nodes[i].tsach = ds.dsdsach[i]->tenSach;
	}

	// Sap xep theo  du lieu da do qua
	for(int i = 0;i < ds.sl - 1;i++){
		for(int j = i + 1;j < ds.sl;j++){
			if(listIndex.nodes[i].tloai > listIndex.nodes[j].tloai)
				swap(listIndex.nodes[i],listIndex.nodes[j]);
			else if(listIndex.nodes[i].tloai == listIndex.nodes[j].tloai){
				if(listIndex.nodes[i].tsach > listIndex.nodes[j].tsach)
					swap(listIndex.nodes[i],listIndex.nodes[j]);
			}
		}
	}
}

// liet ke ds dau sach
void LietKeTrongKhung(DS_DAUSACH &ds,int vitri,int trangHienTai,int trangCuoi,string tenNhap,listBookInGenre &listIndex){
	system("cls");
	int cs;
	int x = 0,y = 0,h = 11,bcolor = 0,tcolor = 7;
	int ix = x,iy = y;
	int w[6] = {7,31,26,26,8,8},sl = 6;
	int slConLai = ds.sl - vitri,count = 0;
	string tieude[6] = {"ISBN","Ten sach","Tac gia","The loai"
						,"Trang","NXB"};
	if(slConLai >= 10){
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
		gotoxy(90,15);
		cout<<"Trang "<<trangHienTai<<" / "<<trangCuoi;
	}
	else{
		h = slConLai + 1;
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
		if(ds.sl != 0){
			gotoxy(90,h + 4);
			cout<<"Trang "<<trangHienTai<<" / "<<trangCuoi;
		}
	}
	if(tenNhap != "MUONTRA"){
        gotoxy(2,25);
        cout<<"INSERT - THEM";
        gotoxy(32,25);
        cout<<"DELETE - XOA";
        gotoxy(62,25);
        cout<<"F2 - SUA";
	}
	gotoxy(2,27);
	cout<<"ESC - THOAT";
	gotoxy(32,27);
	cout<<"PGUP - TRANG TRUOC";
	gotoxy(62,27);
	cout<<"PGDOWN - TRANG SAU";
	SetColor(14);
	// Ve khung tieu de
	for(int i = 0;i < 6;i++){
		gotoxy(ix + canhChuKhoangCach(tieude[i].length(),w[i]),iy + 1);
		cout<<tieude[i];
		ix = ix + w[i] + 1;
	}
	if(slConLai != 0){
		ix = x;
		iy = y + 4;
		SetColor(15);
		for(int i = 0;i < slConLai;i++){
            cs = listIndex.nodes[vitri].chiso;
			gotoxy(ix + 2,iy + i);
			cout<<ds.dsdsach[cs]->ISBN;
			ix = ix + w[0] + 1;
			gotoxy(ix + 2,iy + i);
			cout<<ds.dsdsach[cs]->tenSach;
			ix = ix + w[1] + 1;
			gotoxy(ix + 2,iy + i);
			cout<<ds.dsdsach[cs]->tacGia;
			ix = ix + w[2] + 1;
			gotoxy(ix + 2,iy + i);
			cout<<ds.dsdsach[cs]->theLoai;
			ix = ix + w[3] + 1;
			gotoxy(ix + 2,iy + i);
			cout<<ds.dsdsach[cs]->soTrang;
			ix = ix + w[4] + 1;
			gotoxy(ix + 2,iy + i);
			cout<<ds.dsdsach[cs]->namXuatBan;
			count++;
			vitri++;
			ix = x;
			if(count == 10)
				break;
		}
		SetColor(0);
	}
}

// Do du lieu cay qua mang cho doc gia
void doDuLieuCayQuaMang(TREE_DOCGIA root,DOCGIA dgia[],int &i){
	if (root)
    {
        doDuLieuCayQuaMang(root->left,dgia,i);
        dgia[i] = root->dataDocGia;
        dgia[i].ptr_muontra = root->dataDocGia.ptr_muontra;
        i++;
        doDuLieuCayQuaMang(root->right,dgia,i);
    }
}

// Liet Ke Doc Gia
void LietKeDocGia(TREE_DOCGIA root,int vitri,int trangHienTai,int trangCuoi,int traCuu,listName &listIndex,string theLoaiXuat){
	system("cls");
	TREE_DOCGIA p = root;
	DOCGIA *dgia;
	int soLuongDG = 0, i = 0;
	soNutCuaCay(root,soLuongDG);
    if(soLuongDG != 0){
        dgia = new DOCGIA[soLuongDG];
        doDuLieuCayQuaMang(root,dgia,i);
    }


	int x = 0,y = 0,h = 11,bcolor = 0,tcolor = 7;
	int ix = x,iy = y;
	int w[6] = {8,28,14,7,13},sl = 5;
	int slConLai = soLuongDG - vitri,count = 0;
	string tieude[5] = {"Ma DG","Ho Doc Gia","Ten Doc Gia","Phai"
						,"Trang Thai"};
	if(slConLai >= 10){
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
		gotoxy(90,15);
		cout<<"Trang "<<trangHienTai<<" / "<<trangCuoi;
	}
	else{
		h = slConLai + 1;
		nboxDoAn(x,y,bcolor,tcolor,sl,w,h);
		if(slConLai != 0){
			gotoxy(90,h + 4);
			cout<<"Trang "<<trangHienTai<<" / "<<trangCuoi;
		}
	}
	if(traCuu == 0){
        gotoxy(2,25);
        cout<<"INSERT - THEM";
        gotoxy(32,25);
        cout<<"DELETE - XOA";
        gotoxy(62,25);
        cout<<"F2 - SUA";
        gotoxy(2,27);
        cout<<"ESC - THOAT";
        gotoxy(32,27);
        cout<<"PGUP - TRANG TRUOC";
        gotoxy(62,27);
        cout<<"PGDOWN - TRANG SAU";
	}

	SetColor(14);
	// Ve khung tieu de
	for(int i = 0;i < 5;i++){
		gotoxy(ix + canhChuKhoangCach(tieude[i].length(),w[i]),iy + 1);
		cout<<tieude[i];
		ix = ix + w[i] + 1;
	}
	if(slConLai != 0){
		ix = x;
		iy = y + 4;
		SetColor(15);
		int maThe;
		TREE_DOCGIA pDG;
		for(i = 0;i < slConLai;i++){
            if(theLoaiXuat != ""){
                maThe = listIndex.nodes[vitri].maThe;
                pDG = findNodeInTreeById(root,maThe);
                gotoxy(ix + 2,iy + i);
                cout<<pDG->dataDocGia.maThe;
                ix = ix + w[0] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<pDG->dataDocGia.ho;
                ix = ix + w[1] + 1;
                gotoxy(ix + 5,iy + i);
                cout<<pDG->dataDocGia.ten;
                ix = ix + w[2] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<pDG->dataDocGia.phai;
                ix = ix + w[3] + 1;
                gotoxy(ix + canhChuKhoangCach(9,13),iy + i);
                if(pDG->dataDocGia.trangThaiThe == 1)
                    cout<<"HOAT DONG";
                else
                    cout<<"BI KHOA";
            }
            else{
                gotoxy(ix + 2,iy + i);
                cout<<dgia[vitri].maThe;
                ix = ix + w[0] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<dgia[vitri].ho;
                ix = ix + w[1] + 1;
                gotoxy(ix + 5,iy + i);
                cout<<dgia[vitri].ten;
                ix = ix + w[2] + 1;
                gotoxy(ix + 2,iy + i);
                cout<<dgia[vitri].phai;
                ix = ix + w[3] + 1;
                gotoxy(ix + canhChuKhoangCach(9,13),iy + i);
                if(dgia[vitri].trangThaiThe == 1)
                    cout<<"HOAT DONG";
                else
                    cout<<"BI KHOA";

            }
			count++;
			vitri++;
			ix = x;
			if(count == 10)
				break;

		}
		SetColor(0);
	}
}

// xoa khi tim kiem sach
void xoaNoiDungKhung(){
	int x = 0,y = 4, ix;
	ix = x;
    int w[6] = {7,31,26,26,8,8};
    for(int i = 0;i < 10;i++){
        xoaNoiDung(ix + 1,y + i,6);
        ix = ix + w[0] + 1;
        xoaNoiDung(ix + 1,y + i,30);
        ix = ix + w[1] + 1;
        xoaNoiDung(ix + 1,y + i,25);
        ix = ix + w[2] + 1;
        xoaNoiDung(ix + 1,y + i,25);
        ix = ix + w[3] + 1;
        xoaNoiDung(ix + 1,y + i,7);
        ix = ix + w[4] + 1;
        xoaNoiDung(ix + 1,y + i,7);
        ix = x;
    }
	Normal();
}

// khung tim kiem
void KhungTimKiem(int x,int y,string tieude){
    int h = 4, w = 50;
    boxDoAn(x,y,w,h,9,15);
    gotoxy(canhChuKhoangCach(tieude.length(),w) + x,y);
    cout<<tieude;
    y += 2;
    SetBGColor(15);
    SetColor(0);
    for(int i = x + 2;i < w + x - 1;i++){
        gotoxy(i,y);
        cout<<" ";
    }
    Normal();
}

// xuat du lieu cho tim kiem sach
void XuatDuLieu(DS_DAUSACH &ds,string strPat,int &viTriCuoiCung){
    hidecursor(false);
    Normal();
    int vitri, count = 0;
    int viTriHopLe = viTriCuoiCung;
    int x = 0,iy = 4, ix;
    int w[6] = {7,31,26,26,8,8};
	ix = x;
	xoaNoiDungKhung();
    for(int i = 0;i < ds.sl;i++){
        toUpperString(ds.dsdsach[i]->tenSach);
        vitri = ds.dsdsach[i]->tenSach.find(strPat,0);
        if(vitri == 0){
            gotoxy(ix + 2,iy + count);
			cout<<ds.dsdsach[i]->ISBN;
			ix = ix + w[0] + 1;
			gotoxy(ix + 2,iy + count);
			cout<<ds.dsdsach[i]->tenSach;
			ix = ix + w[1] + 1;
			gotoxy(ix + 2,iy + count);
			cout<<ds.dsdsach[i]->tacGia;
			ix = ix + w[2] + 1;
			gotoxy(ix + 2,iy + count);
			cout<<ds.dsdsach[i]->theLoai;
			ix = ix + w[3] + 1;
			gotoxy(ix + 2,iy + count);
			cout<<ds.dsdsach[i]->soTrang;
			ix = ix + w[4] + 1;
			gotoxy(ix + 2,iy + count);
			cout<<ds.dsdsach[i]->namXuatBan;
			count++;
			if(count == 1)
                viTriCuoiCung = i;
			ix = x;
			if(count == 10)
                break;
        }
    }
    if(viTriHopLe == 0 || count > 1)
        viTriCuoiCung = -1;
	SetBGColor(15);
	SetColor(0);
	hidecursor(true);
}

// tim sach tho ten da nhap
void findBook(DS_DAUSACH &ds,string &tenSach){
    xoaNoiDung(90,15,20);
	KhungTimKiem(0,16,"TIM KIEM THEO TEN SACH");
	int x = 2, y = 18;
	char kyTu;
	int viTriCuoiCung = -1;
	string strPat = "";
	gotoxy(x,y);
	SetBGColor(15);
	SetColor(0);
	while(true){
            if(viTriCuoiCung != -1){
                strPat = ds.dsdsach[viTriCuoiCung]->tenSach;
                viTriCuoiCung = strPat.length() - x + 3;
                viTriCuoiCung *= -1;
                xoaNoiDung(2,y,47);
                gotoxy(2,y);
                cout<<strPat;
                x = 2 + strPat.length();
            }
            gotoxy(x,y);
            kyTu = getch();
            toUpper(kyTu);
            if(kyTu >= 65 && kyTu <= 90 || kyTu == 32){
                if(x == 47)
                    continue;
                gotoxy(x,y);
                cout<<kyTu;
                strPat += kyTu;
                XuatDuLieu(ds,strPat,viTriCuoiCung);
                x++;
            }else if(kyTu == BACKSPACE){
                if(x == 2)
                    continue;
                strPat = strPat.substr(0,strPat.length() + viTriCuoiCung);
                for(int i = 0;i < abs(viTriCuoiCung);i++){
                    x--;
                    gotoxy(x,y);
                    cout<<" ";
                }
                viTriCuoiCung = 0;
                XuatDuLieu(ds,strPat,viTriCuoiCung);
            }
            else if(kyTu == ESC){
                return;
            }else if(kyTu == ENTER){
                tenSach = strPat;
                break;
            }
	}
}

// Lay ra tung token
int GetToken(string &token,string s,int &startPos){
	string sep = "|\n";
	int fromPos,toPos,length = s.length(),nTokenLength = 0;
	token = "";
	fromPos = s.find_first_not_of(sep,startPos);
	if(fromPos == -1)
		return nTokenLength;
	toPos = s.find_first_of(sep,fromPos);
	if(toPos == -1)
		toPos = length;
	nTokenLength = toPos - fromPos;
	token = s.substr(fromPos,nTokenLength);
	startPos = toPos;
	return nTokenLength;
}

// Lay cac token da tach bo vao mang
int ParseString(vector<string>& arrToken,string s){
	string token;
	int nTokens = 0,startPos = 0;
	while(GetToken(token,s,startPos) > 0){
		arrToken.push_back(token);
		nTokens++;
	}
	return nTokens;
}

// Doc file dau sach
void LoadFileDauSach(DS_DAUSACH &ds){
	const char* fileName = "dausach.txt";
    FILE *fpIn = fopen(fileName,"rt");
    if(fpIn != NULL){
    	PTR_SACH p = NULL;
		SACH sch;
		string s;
		char *str = new char[256];
		vector<string> arrToken;
		int nTokens,slMaSach;
		fscanf(fpIn,"%d",&ds.sl);
		fgetc(fpIn);
		for(int i = 0;i < ds.sl;i++){
			fgets(str,256,fpIn);
			s = changeToString(str);
			nTokens = ParseString(arrToken,s);
			ds.dsdsach[i] = new DAUSACH;
			ds.dsdsach[i]->ISBN = arrToken[0];
			ds.dsdsach[i]->tenSach = arrToken[1];
			ds.dsdsach[i]->tacGia = arrToken[2];
			ds.dsdsach[i]->theLoai = arrToken[3];
			ds.dsdsach[i]->soTrang = atoi(arrToken[4].c_str());
			ds.dsdsach[i]->namXuatBan = atoi(arrToken[5].c_str());
			ds.dsdsach[i]->soLuongMuon = atoi(arrToken[6].c_str());
			fscanf(fpIn,"%d",&ds.dsdsach[i]->listSach.n);
			fscanf(fpIn,"%d",&ds.dsdsach[i]->listSach.maSachLonNhat);
			fgetc(fpIn);
			slMaSach = ds.dsdsach[i]->listSach.n;
			ds.dsdsach[i]->listSach.head = NULL;
			for(int j = 0;j < slMaSach;j++){
				arrToken.resize(0);
				fgets(str,256,fpIn);
				s = changeToString(str);
				nTokens = ParseString(arrToken,s);
				sch.maSach = arrToken[0];
				sch.vitri = arrToken[1];
				sch.trangThai = atoi(arrToken[2].c_str());
				addFirst(ds.dsdsach[i]->listSach.head,sch);
			}
			arrToken.resize(0);
		}
    	fclose(fpIn);
    	cout<<"Load file thanh cong\n";
	}
}

// luu file dau sach
void SaveFileDauSach(DS_DAUSACH &ds){
	const char* fileName = "dausach.txt";
    FILE *fpIn = fopen(fileName,"wt");
    if(fpIn != NULL){
    	PTR_SACH p = NULL;
		DAUSACH dsach;
		string s;
		fprintf(fpIn,"%d",ds.sl);
		fprintf(fpIn,"%s","\n");
		for(int i = 0;i < ds.sl;i++){
			dsach = *ds.dsdsach[i];
			s = dsach.ISBN + "|" + dsach.tenSach + "|" + dsach.tacGia + "|" + dsach.theLoai + "|" +
				changeToString(dsach.soTrang) + "|" + changeToString(dsach.namXuatBan) + "|" + changeToString(dsach.soLuongMuon) + "\n";
			fputs(s.c_str(),fpIn);
			fprintf(fpIn,"%d",dsach.listSach.n);
			fputc(32,fpIn);
			fprintf(fpIn,"%d",dsach.listSach.maSachLonNhat);
			fprintf(fpIn,"%s","\n");
			p = dsach.listSach.head;
			for(int j = 0;j < dsach.listSach.n;j++){
				s = p->dataSach.maSach + "|" + p->dataSach.vitri + "|" +
				changeToString(p->dataSach.trangThai) + "\n";
				fputs(s.c_str(),fpIn);
				//fprintf(fpIn,"%s","\n");
				p = p->next;
			}
		}
    	fclose(fpIn);
    	gotoxy(0,18);
    	cout<<"Save file thanh cong\n";
	}
}

// doc file doc gia
void LoadFileDocGia(TREE_DOCGIA &root,int &vitriMaTheHienTai){
	const char* fileName = "docgia.txt";
    FILE *fpIn = fopen(fileName,"rt");
    if(fpIn != NULL){
    	TREE_DOCGIA p;
		MUONTRA mTra;
		//DOCGIA dGia;
		string s;
		char *str = new char[256];
		vector<string> arrToken;
		int nTokens,slMuonTra,soLuongDG;
		fscanf(fpIn,"%d",&soLuongDG);
		if(soLuongDG != 0)
        {
            fgetc(fpIn);
            for(int i = 0;i < soLuongDG;i++){
                DOCGIA dGia;
                dGia.ptr_muontra = NULL;
                fgets(str,256,fpIn);
                s = changeToString(str);
                nTokens = ParseString(arrToken,s);

                dGia.maThe = atoi(arrToken[0].c_str());
                dGia.ho = arrToken[1];
                dGia.ten = arrToken[2];
                dGia.phai = arrToken[3];
                dGia.trangThaiThe = atoi(arrToken[4].c_str());
                dGia.viTriMaThe = atoi(arrToken[5].c_str());
                if(dGia.viTriMaThe > vitriMaTheHienTai)
                    vitriMaTheHienTai = dGia.viTriMaThe;
                fscanf(fpIn,"%d",&dGia.soLuongMuon);
                fscanf(fpIn,"%d",&dGia.soLuongTra);
                fgetc(fpIn);
                slMuonTra = dGia.soLuongMuon;
                for(int j = 0;j < slMuonTra;j++){
                    arrToken.resize(0);
                    fgets(str,256,fpIn);
                    s = changeToString(str);
                    nTokens = ParseString(arrToken,s);
                    mTra.maSach = arrToken[0];
                    mTra.ngayMuon = arrToken[1];
                    mTra.ngayTra = arrToken[2];
                    mTra.trangThai = atoi(arrToken[3].c_str());
                    addFirstMuonTra(dGia.ptr_muontra,mTra);
                }
                p = CreateNode(dGia);
                AddNode(root,p);
                arrToken.resize(0);
            }
        }

    	fclose(fpIn);
    	cout<<"Load file thanh cong\n";
	}else{
		cout<<"fail";
	}
}

// luu file doc gia
void SaveFileDocGia(TREE_DOCGIA &root){
	const char* fileName = "docgia.txt";
    FILE *fpIn = fopen(fileName,"wt");
    if(fpIn != NULL){
    	PTR_MUONTRA p = NULL;
		DOCGIA *dgia;
		string s;
		int soLuong = 0, i = 0;
		soNutCuaCay(root,soLuong);
		if(soLuong != 0){
            dgia = new DOCGIA[soLuong];
            doDuLieuCayQuaMang(root,dgia,i);
		}
		fprintf(fpIn,"%d",soLuong);
		fprintf(fpIn,"%s","\n");
		for(int i = 0;i < soLuong;i++){
			s = changeToString(dgia[i].maThe) + "|" + dgia[i].ho + "|" + dgia[i].ten + "|" + dgia[i].phai + "|" +
				changeToString(dgia[i].trangThaiThe) + "|" + changeToString(dgia[i].viTriMaThe) + "\n";
			fputs(s.c_str(),fpIn);
			fprintf(fpIn,"%d",dgia[i].soLuongMuon);
			fputc(32,fpIn);
			fprintf(fpIn,"%d",dgia[i].soLuongTra);
			fprintf(fpIn,"%s","\n");
			p = dgia[i].ptr_muontra;
			for(int j = 0;j < dgia[i].soLuongMuon;j++){
				s = p->dataMuonTra.maSach + "|" + p->dataMuonTra.ngayMuon + "|" +
				p->dataMuonTra.ngayTra + "|" + changeToString(p->dataMuonTra.trangThai) + "\n";
				fputs(s.c_str(),fpIn);
				p = p->next;
			}
		}
    	fclose(fpIn);
    	gotoxy(0,19);
    	cout<<"Save file thanh cong\n";
	}
}

// menu chinh cua chuong trinh
int menuDong(){
	hidecursor(false);
	string items[6] = {"QUAN LY DAU SACH","QUAN LY DOC GIA","MUON SACH","TRA SACH","THONG KE",
						"THOAT"};
	int x = 0,ix,y = 0,iy,h = 4,w = 30,bcolor = 6,tcolor = 15;
	int kc,chon = 0;
	char kyTu;
	ix = x;
	iy = y;
	for(int i = 0;i < 6;i++){
		if(i == 3){
			iy = y + h + 3;
			ix = x;
		}
		boxDoAn(ix,iy,w,h,bcolor,tcolor);
		kc = (w - items[i].length()) / 2;
		//SetColor(tcolor);
		HighLight();
		gotoxy(ix + kc,iy + 2);
		cout<<items[i];
		ix = ix + w + 5;
		Normal();
	}
	ix = x;
	iy = y;
	bcolor = 2;
	boxDoAn(ix,iy,w,h,bcolor,tcolor);
	SetBGColor(bcolor);
	gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
	cout<<items[chon];
	bcolor = 6;
	while(true){
		bcolor = 6;
		kyTu = getch();
		if(kyTu == -32){
			kyTu = getch();
			if(kyTu == UP && ((chon - 3) >= 0)){
				Normal();
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
				iy = iy - h - 3;
				chon -= 3;
				Normal();
				bcolor = 2;
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight_Choose();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
			}
			else if(kyTu == DOWN && ((chon + 3) < 6)){
				Normal();
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
				iy = iy + h + 3;
				chon += 3;
				Normal();
				bcolor = 2;
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight_Choose();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
			}
			else if(kyTu == LEFT && chon != 0 && chon != 3)
			{
				Normal();
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
				ix = ix - w - 5;
				chon -= 1;
				Normal();
				bcolor = 2;
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight_Choose();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
			}
			else if(kyTu == RIGHT && chon != 2 && chon != 5)
			{
				Normal();
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
				ix = ix + w + 5;
				chon += 1;
				Normal();
				bcolor = 2;
				boxDoAn(ix,iy,w,h,bcolor,tcolor);
				HighLight_Choose();
				gotoxy(ix + (w - items[chon].length()) / 2,iy + 2);
				cout<<items[chon];
			}
		}
		else if(kyTu == ENTER){
			Normal();
			return chon + 1;
		}
	}
}

//QUAN LY SACH TRONG DAU SACH
void QuanLySachTrongDauSach(DS_DAUSACH &ds,int luachon,string &tenNhap){
	int vitri = 0;
	int chon = -1;
	int trangCuoi,trangHienTai = 1;
	int slConLai;
	int soLuongTong;
	char kyTu;
	bool flag = true;
	list_NodeSach list = ds.dsdsach[luachon]->listSach;
	PTR_SACH p = list.head;
	while(true){
        list = ds.dsdsach[luachon]->listSach;
        p = list.head;
	    soLuongTong = ds.dsdsach[luachon]->listSach.n;
		slConLai = soLuongTong - vitri;
		if(flag == true){
            if(slConLai % 10 == 0)
                trangCuoi = soLuongTong / 10;
            else
                trangCuoi = soLuongTong / 10 + 1;
			XuatSachTrongKhung(ds,luachon,vitri,trangHienTai,trangCuoi,tenNhap);
			flag = false;
		}
		while(kbhit()){
			kyTu = getch();
			if(kyTu == ESC)
                return;
            else if(kyTu == ENTER && chon != -1 && tenNhap == "MUONTRA"){
                p = tinhTienVitriDSLK(p,vitri + chon);
                tenNhap = p->dataSach.maSach;
                return;
            }
            else if(kyTu == 0){
				kyTu = getch();
				if(kyTu == F2 && tenNhap != "MUONTRA"){
					system("cls");
					if(chon != -1){
						int kq = HieuChinhSachTrongDauSach(ds,luachon,vitri + chon);
						hidecursor(false);
						if(kq == 1){
							ThongBao(0,22,"Hieu Chinh Thanh Cong!");
							Sleep(2000);
						}
						flag = true;
						chon = -1;
					}
				}
			}
            else if(kyTu == -32){
                kyTu = getch();
                if(kyTu == INS && tenNhap != "MUONTRA"){
                    system("cls");
                    nhapDsSach(ds,5,luachon);
                    chon = -1;
                    flag = true;
                    soLuongTong = ds.dsdsach[luachon]->listSach.n;
                }else if(kyTu == PGDOWN && trangHienTai < trangCuoi){
					trangHienTai++;
					vitri  += 10;
					chon = -1;
					flag = true;
				}
				else if(kyTu == PGUP && trangHienTai > 1){
					trangHienTai--;
					vitri  -= 10;
					chon = -1;
					flag = true;
				}else if(kyTu == DOWN && chon < (slConLai - 1) && chon != 9){
					if(chon == -1){
						HighLight_Choose();
						for(int i = 1;i <= 10;i++){
							gotoxy(i,4);
							cout<<" ";
						}
						chon++;
						gotoxy(2,4);
						p = tinhTienVitriDSLK(p,vitri + chon);
						cout<<p->dataSach.maSach;
						p = list.head;
						Normal();
					}else{
						Normal();
						for(int i = 1;i <= 10;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						p = tinhTienVitriDSLK(p,vitri + chon);
						cout<<p->dataSach.maSach;
						chon++;
						HighLight_Choose();
						for(int i = 1;i <= 10;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						p = p->next;
						cout<<p->dataSach.maSach;
						p = list.head;
						Normal();
					}

				}else if(kyTu == UP && chon > 0){
						Normal();
						for(int i = 1;i <= 10;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						p = tinhTienVitriDSLK(p,vitri + chon);
						cout<<p->dataSach.maSach;
						p = list.head;
						chon--;
						HighLight_Choose();
						for(int i = 1;i <= 6;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						p = tinhTienVitriDSLK(p,vitri + chon);
						cout<<p->dataSach.maSach;
						p = list.head;
						Normal();
				}else if(kyTu == DEL && tenNhap != "MUONTRA"){
					if(chon != -1){
						XoaSachTrongDauSach(ds,luachon,vitri + chon,flag);
						Sleep(2500);
						for(int i = 0;i <= 45;i++)
							ThongBao(i,15," ");
                        if(flag == true){
                            chon = -1;
                        }
					}
				}
			}
		}
	}
}

// tim vi tri theo ten sach
int timVitriDauSach(DS_DAUSACH &ds,string sachCanTim){
    for(int i = 0;i < ds.sl;i++){
        if(ds.dsdsach[i]->tenSach == sachCanTim)
            return i;
    }
    return -1;
}


//QUAN LY DAU SACH
void QuanLyDauSach(DS_DAUSACH &ds,string &tenNhap){
	int vitri = 0;
	int cs;
	int chon = -1;
	int trangCuoi,trangHienTai = 1;
	int slConLai = ds.sl;
	char kyTu;
	bool flag = true;
	string sachCanTim = "";
	int viTriSach;
	listBookInGenre listIndex;
	while(true){
		slConLai = ds.sl - vitri;
		if(flag == true){
            if(ds.sl % 10 == 0)
                trangCuoi = ds.sl / 10;
            else
                trangCuoi = ds.sl / 10 + 1;
            indexByBookInGenre(ds,listIndex);
			LietKeTrongKhung(ds,vitri,trangHienTai,trangCuoi,tenNhap,listIndex);
			flag = false;
		}
		while(kbhit()){
			kyTu = getch();
			if(kyTu == CTRL_F && tenNhap != "MUONTRA"){
                hidecursor(true);
				findBook(ds,sachCanTim);
                hidecursor(false);
                viTriSach = timVitriDauSach(ds,sachCanTim);
                Normal();
                if(viTriSach != -1)
                    QuanLySachTrongDauSach(ds,viTriSach,tenNhap);
                chon = -1;
				flag = true;
			}
			else if(kyTu == -32){
				kyTu = getch();
				if(kyTu == PGDOWN && trangHienTai < trangCuoi){
					trangHienTai++;
					vitri  += 10;
					chon = -1;
					flag = true;
				}
				else if(kyTu == PGUP && trangHienTai > 1){
					trangHienTai--;
					vitri  -= 10;
					chon = -1;
					flag = true;
				}else if(kyTu == INS && tenNhap != "MUONTRA"){
					system("cls");
					NhapDsDauSach(ds);
					chon = -1;
					flag = true;
					trangHienTai = 1;
					vitri = 0;
				}else if(kyTu == DEL && tenNhap != "MUONTRA"){
					if(chon != -1){
                        cs = listIndex.nodes[vitri + chon].chiso;
						XoaDauSach(ds,cs,flag);
						Sleep(2500);
						for(int i = 0;i <= 45;i++)
							ThongBao(i,15," ");
						if(ds.sl % 10 == 0)
							trangCuoi = ds.sl / 10;
						else
							trangCuoi = ds.sl / 10 + 1;
						if(flag == true){
                            chon = -1;
                            trangHienTai = 1;
                            vitri = 0;
						}
					}
				}else if(kyTu == DOWN && chon < (slConLai - 1) && chon != 9){
					if(chon == -1){
						HighLight_Choose();
						for(int i = 1;i <= 6;i++){
							gotoxy(i,4);
							cout<<" ";
						}
						chon++;
						gotoxy(2,4);
						cs = listIndex.nodes[vitri + chon].chiso;
						cout<<ds.dsdsach[cs]->ISBN;
						Normal();
					}else{
						Normal();
						for(int i = 1;i <= 6;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						cs = listIndex.nodes[vitri + chon].chiso;
						cout<<ds.dsdsach[cs]->ISBN;
						chon++;
						HighLight_Choose();
						for(int i = 1;i <= 6;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						cs = listIndex.nodes[vitri + chon].chiso;
						cout<<ds.dsdsach[cs]->ISBN;
						Normal();
					}

				}else if(kyTu == UP && chon > 0){
						Normal();
						for(int i = 1;i <= 6;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						cs = listIndex.nodes[vitri + chon].chiso;
						cout<<ds.dsdsach[cs]->ISBN;
						chon--;
						HighLight_Choose();
						for(int i = 1;i <= 6;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						cs = listIndex.nodes[vitri + chon].chiso;
						cout<<ds.dsdsach[cs]->ISBN;
						Normal();
				}
			}else if(kyTu == 0){
				kyTu = getch();
				if(kyTu == F2 && tenNhap != "MUONTRA"){
					system("cls");
					if(chon != -1){
                        cs = listIndex.nodes[vitri + chon].chiso;
						int kq = HieuChinhDauSach(ds,cs);
						hidecursor(false);
						if(kq == 1){
							ThongBao(0,22,"Hieu Chinh Thanh Cong!");
							Sleep(2000);
						}
                        flag = true;
                        chon = -1;
					}
				}
			}
			else if(kyTu == ESC)
				return;
            else if(kyTu == ENTER && chon != -1){
                cs = listIndex.nodes[vitri + chon].chiso;
                QuanLySachTrongDauSach(ds,cs,tenNhap);
                if(tenNhap == "MUONTRA" || tenNhap == ""){
                    chon = -1;
                    flag = true;
                }
                else{
                    return;
                }
            }
		}
	}
}

//QUAN LY DOC GIA
void QuanLyDocGia(TREE_DOCGIA &root,DS_DAUSACH &ds,int mangTheSinhTuDong[],int checkTheSinhTuDong[],int &vitriMaThe,string theLoaiXuat = ""){
	TREE_DOCGIA curNode;
	int count = 0,maThe = -1;
	int vitri = 0;
	int chon = -1;
	int giaTriMaThe;
	int cs;
	int trangCuoi = 1,trangHienTai = 1;
	int slConLai,soLuongDG = 0;
	soNutCuaCay(root,soLuongDG);
	slConLai = soLuongDG;
	char kyTu;
	bool flag = true;
    listName listIndex;
	while(true){
		slConLai = soLuongDG - vitri;
		if(flag == true){
            if(soLuongDG % 10 == 0)
                trangCuoi = soLuongDG / 10;
            else
                trangCuoi = soLuongDG / 10 + 1;
            if(theLoaiXuat != "")
                IndexByName(root,listIndex);
			LietKeDocGia(root,vitri,trangHienTai,trangCuoi,0,listIndex,theLoaiXuat);
			flag = false;
		}
		while(kbhit()){
			kyTu = getch();
			if(kyTu == -32){
                kyTu = getch();
                if(kyTu == INS){
					system("cls");
					nhapDsDocGia(root,1,mangTheSinhTuDong,checkTheSinhTuDong,vitriMaThe);
					flag = true;
					soLuongDG = 0;
                    soNutCuaCay(root,soLuongDG);
                    chon = -1;
                    vitri = 0;
                    trangHienTai = 1;
				}else if(kyTu == DEL){
					if(chon != -1){
                        if(theLoaiXuat != "")
                            XoaDocGia(root,vitri + chon,flag,listIndex.nodes[vitri + chon].maThe);
                        else
                            XoaDocGia(root,vitri + chon,flag);
						Sleep(2500);
						for(int i = 0;i <= 45;i++)
							ThongBao(i,15," ");
						if(flag == true)
							chon = -1;
                        soLuongDG = 0;
                        soNutCuaCay(root,soLuongDG);
					}
				}
                else if(kyTu == DOWN && chon < (slConLai - 1) && chon != 9){
                    if(theLoaiXuat != "")
                    {
                        if(chon == -1){
                            HighLight_Choose();
                            for(int i = 1;i <= 7;i++){
                                gotoxy(i,4);
                                cout<<" ";
                            }
                            chon++;
                            gotoxy(2,4);
                            cout<<listIndex.nodes[vitri + chon].maThe;
                            Normal();
                        }else{
                            Normal();
                            for(int i = 1;i <= 7;i++){
                                gotoxy(i,4 + chon);
                                cout<<" ";
                            }
                            gotoxy(2,4 + chon);
                            cout<<listIndex.nodes[vitri + chon].maThe;
                            chon++;
                            HighLight_Choose();
                            for(int i = 1;i <= 7;i++){
                                gotoxy(i,4 + chon);
                                cout<<" ";
                            }
                            gotoxy(2,4 + chon);
                            cout<<listIndex.nodes[vitri + chon].maThe;
                            Normal();
                        }
                    }else{
                        if(chon == -1){
                            HighLight_Choose();
                            for(int i = 1;i <= 7;i++){
                                gotoxy(i,4);
                                cout<<" ";
                            }
                            chon++;
                            gotoxy(2,4);
                            findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                            cout<<maThe;
                            Normal();
                            maThe = -1;
                            count = 0;
                        }else{
                            Normal();
                            for(int i = 1;i <= 7;i++){
                                gotoxy(i,4 + chon);
                                cout<<" ";
                            }
                            gotoxy(2,4 + chon);
                            findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                            cout<<maThe;
                            chon++;
                            HighLight_Choose();
                            for(int i = 1;i <= 7;i++){
                                gotoxy(i,4 + chon);
                                cout<<" ";
                            }
                            maThe = -1;
                            count = 0;
                            gotoxy(2,4 + chon);
                            findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                            cout<<maThe;
                            Normal();
                            maThe = -1;
                            count = 0;
                        }

                    }
				}else if(kyTu == UP && chon > 0){
				    if(theLoaiXuat != ""){
                        Normal();
						for(int i = 1;i <= 7;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						cout<<listIndex.nodes[vitri + chon].maThe;
						chon--;
						HighLight_Choose();
						for(int i = 1;i <= 7;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						cout<<listIndex.nodes[vitri + chon].maThe;
						Normal();
				    }
                    else{
						Normal();
						for(int i = 1;i <= 7;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						gotoxy(2,4 + chon);
						findNodeInTreeByPos(root,vitri + chon  + 1,count,maThe);
						cout<<maThe;
						chon--;
						HighLight_Choose();
						for(int i = 1;i <= 7;i++){
							gotoxy(i,4 + chon);
							cout<<" ";
						}
						maThe = -1;
						count = 0;
						gotoxy(2,4 + chon);
						findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
						cout<<maThe;
						Normal();
						maThe = -1;
						count = 0;
                    }
				}else if(kyTu == PGDOWN && trangHienTai < trangCuoi){
					trangHienTai++;
					vitri  += 10;
					chon = -1;
					flag = true;
				}
				else if(kyTu == PGUP && trangHienTai > 1){
					trangHienTai--;
					vitri  -= 10;
					chon = -1;
					flag = true;
				}
			}else if(kyTu == 0){
				kyTu = getch();
				if(kyTu == F2){
					system("cls");
					if(chon != -1){
					    int kq;
                        if(theLoaiXuat != "")
                            kq = HieuChinhDocGia(root,vitri + chon,listIndex.nodes[vitri + chon].maThe);
                        else
                            kq = HieuChinhDocGia(root,vitri + chon);
						hidecursor(false);
						if(kq == 1){
							ThongBao(0,22,"Hieu Chinh Thanh Cong!");
							Sleep(2000);
						}
						flag = true;
						chon = -1;
					}
				}
			}
			if(kyTu == ESC)
				return;
            if(kyTu == ENTER && chon != -1){
                if(theLoaiXuat == "")
                    LietKeSachDangMuon(root,ds,vitri + chon,-1,"",2);
                else
                    LietKeSachDangMuon(root,ds,vitri + chon,listIndex.nodes[vitri + chon].maThe,"",2);
                while(true){
                    kyTu = getch();
                    if(kyTu == ESC)
                        break;
                }
                chon = -1;
                flag = true;
            }
		}
	}
}

// MENU QLDG
void menuQLDG(TREE_DOCGIA &root,DS_DAUSACH &ds,int mangTheSinhTuDong[],int checkTheSinhTuDong[],int &viTriMaThe){
    system("cls");
    int chon = -1;
    char kyTu;
    bool flag = true;
    int x = 37,y = 10,bcolor = 2,tcolor = 7,w = 50,h = 4;
    string s[2] = {"XUAT DANH SACH DOC GIA THEO MA THE TANG DAN","XUAT DANH SACH DOC GIA THEO TEN + HO TANG DAN"};

    while(true){
        if(flag == true){
            system("cls");
            boxDoAn(x,y,w,h,bcolor,tcolor);
            Normal();
            gotoxy(x + canhChuKhoangCach(s[0].length(),w),y + 2);
            SetBGColor(2);
            cout<<s[0];
            Normal();
            bcolor = 0;
            boxDoAn(x,y + 6,w,h,bcolor,tcolor);
            Normal();
            gotoxy(x + canhChuKhoangCach(s[1].length(),w),y + 8);
            cout<<s[1];
            flag = false;
        }

        kyTu = getch();
        if(kyTu == ESC)
            break;
        if(kyTu == ENTER){
            if(chon == 2){
                Normal();
                QuanLyDocGia(root,ds,mangTheSinhTuDong,checkTheSinhTuDong,viTriMaThe,"HOTEN");
                flag = true;
                chon = -1;
                bcolor = 2;
            }else{
                Normal();
                QuanLyDocGia(root,ds,mangTheSinhTuDong,checkTheSinhTuDong,viTriMaThe);
                flag = true;
                chon = -1;
                bcolor = 2;
            }
        }
        else if(kyTu == -32){
            kyTu = getch();
            if(kyTu == UP && chon > 1){
				Normal();
				bcolor = 0;
				boxDoAn(x,y + 6,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[1].length(),w),y + 8);
				cout<<s[1];
				chon = 1;
				bcolor = 2;
				boxDoAn(x,y,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[0].length(),w),y + 2);
				SetBGColor(2);
				cout<<s[0];
			}
			else if(kyTu == DOWN && chon < 2){
				Normal();
				bcolor = 0;
				boxDoAn(x,y,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[0].length(),w),y + 2);
				cout<<s[0];
				chon = 2;
				bcolor = 2;
				boxDoAn(x,y + 6,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[1].length(),w),y + 8);
				SetBGColor(2);
				cout<<s[1];
			}
        }
    }
    Normal();
}

// xem ds doc gia
int xemDanhSachDocGia(TREE_DOCGIA &root){
    hidecursor(false);
    bool flag = true;
    int soLuongDg = 0;
    int count = 0, vitri = 0;
    int maThe = -1;
    char kyTu;
    int chon = -1, trangHienTai = 1, trangCuoi = 1;
    listName listIndex;
    soNutCuaCay(root,soLuongDg);
    int slConLai = soLuongDg;
    if(soLuongDg % 10 == 0)
        trangCuoi = soLuongDg / 10;
    else
        trangCuoi = soLuongDg / 10 + 1;
    while(true){
        slConLai = soLuongDg - vitri;
        if(flag == true){
            LietKeDocGia(root,vitri,trangHienTai,trangCuoi,1,listIndex,"");
            flag = false;
        }
        while(kbhit()){
            kyTu = getch();
            if(kyTu == ENTER && chon != -1)
                return chon + vitri;
            if(kyTu == ESC)
                return -1;
            if(kyTu == DOWN && chon < (slConLai - 1) && chon != 9){
                if(chon == -1){
                    HighLight_Choose();
                    for(int i = 1;i <= 7;i++){
                        gotoxy(i,4);
                        cout<<" ";
                    }
                    chon++;
                    gotoxy(2,4);
                    findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                    cout<<maThe;
                    Normal();
                    maThe = -1;
                    count = 0;
                }else{
					Normal();
                    for(int i = 1;i <= 7;i++){
                        gotoxy(i,4 + chon);
                        cout<<" ";
                    }
                    gotoxy(2,4 + chon);
                    findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                    cout<<maThe;
                    chon++;
                    HighLight_Choose();
                    for(int i = 1;i <= 7;i++){
                        gotoxy(i,4 + chon);
                        cout<<" ";
                    }
                    maThe = -1;
                    count = 0;
                    gotoxy(2,4 + chon);
                    findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                    cout<<maThe;
                    Normal();
                    maThe = -1;
                    count = 0;
                }
            }else if(kyTu == UP && chon > 0){
                Normal();
                for(int i = 1;i <= 7;i++){
                    gotoxy(i,4 + chon);
                    cout<<" ";
                }
                gotoxy(2,4 + chon);
                findNodeInTreeByPos(root,vitri + chon  + 1,count,maThe);
                cout<<maThe;
                chon--;
                HighLight_Choose();
                for(int i = 1;i <= 7;i++){
                    gotoxy(i,4 + chon);
                    cout<<" ";
                }
                maThe = -1;
                count = 0;
                gotoxy(2,4 + chon);
                findNodeInTreeByPos(root,vitri + chon + 1,count,maThe);
                cout<<maThe;
                Normal();
                maThe = -1;
                count = 0;
            }else if(kyTu == PGDOWN && trangHienTai < trangCuoi){
                trangHienTai++;
                vitri  += 10;
                chon = -1;
                flag = true;
            }
            else if(kyTu == PGUP && trangHienTai > 1){
					trangHienTai--;
					vitri  -= 10;
					chon = -1;
					flag = true;
            }
        }
    }
    hidecursor(true);
}

// KIEM TRA MA SACH TON TAI VA CHUA MUON
int kiemTraMaSachTonTaiVaChuaMuon(DS_DAUSACH &ds,string maSach,int &vitri,int &kiemTra){
    PTR_SACH First = NULL;
    kiemTra = 0; // ma sach khong ton tai
    if(maSach.length() == 8){
        string maDauSach = maSach.substr(0,4);
        for(int i = 0;i < ds.sl;i++){
            if(ds.dsdsach[i]->ISBN == maDauSach)
            {
                vitri = i;
                First = ds.dsdsach[i]->listSach.head;
                break;
            }
        }

        if(First != NULL){
            for(PTR_SACH q = First;q != NULL;q = q->next){
                if(q->dataSach.maSach == maSach){
                    if(q->dataSach.trangThai == 0)
                        return 1;
                    else{
                        if(q->dataSach.trangThai == 1)
                            kiemTra = 1;
                        else
                            kiemTra = 2;
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}

// KIEM TRA SACH CO TRUNG KHI DANG MUON
int kiemTraMaSachTrungMaDauSach(PTR_MUONTRA First,string maSach){
    maSach = maSach.substr(0,4);
    string maDauSach = "";
    for(PTR_MUONTRA p = First;p != NULL;p = p->next){
        if(p->dataMuonTra.trangThai == 0){
            maDauSach = p->dataMuonTra.maSach.substr(0,4);
            if(maDauSach == maSach)
                return 1;
        }
    }
    return 0;
}

// KIEM TRA SACH CO NAM TRONG DS DANG MUON
int kiemTraMaSachCoNamTrongDsDangMuon(PTR_MUONTRA First,string maSach){
    for(PTR_MUONTRA p = First;p != NULL;p = p->next){
        if(p->dataMuonTra.maSach == maSach && p->dataMuonTra.trangThai == 0)
            return 1;
    }
    return 0;
}

// NHAP MUON SACH
void nhapMuonSach(TREE_DOCGIA &root,DS_DAUSACH &ds,string &tenNhap,int maThe){
    int x = 25,y = 17;
    int vitri = -1;
    int kiemTra;
    char kyTu;
    time_t now;
    tm *ltm;
    hidecursor(true);
    string s = "",s1 = "";
    MUONTRA p;
    TREE_DOCGIA q = findNodeInTreeById(root,maThe);
    KhungNhapMuonTraSach(0,12);
    gotoxy(0,23);
    cout<<"F1: Xem danh sach ma dau sach!";
    string str[2] = {""};
    PTR_SACH First;
    while(true){
        SetBGColor(15);
        SetColor(0);
        if(y == 21)
            break;
        gotoxy(x,y);
        kyTu = getch();
        if(kyTu == 0){
            kyTu = getch();
            if(kyTu == F1){
                tenNhap = "MUONTRA";
                Normal();
                hidecursor(false);
                QuanLyDauSach(ds,tenNhap);
                hidecursor(true);
                LietKeSachDangMuon(root,ds,0,maThe,"");
                KhungNhapMuonTraSach(0,12);
                gotoxy(0,23);
                cout<<"F1: Xem danh sach ma dau sach!";
                SetBGColor(15);
                SetColor(0);
                if(tenNhap != "MUONTRA"){
                    gotoxy(25, 17);
                    cout<<tenNhap;
                    s = tenNhap;
                    x = s.length() + 25;
                    y = 17;
                }else{
                    gotoxy(25, 17);
                    cout<<s;
                }
            }
        }
        else if(kyTu == BACKSPACE){
            if(x == 25)
                continue;
            if(y == 19){
                if(x == 36){
                    s = s.substr(0,s.length() - 1);
                    x = 25 + s.length();
                }
                if(x == 47){
                    s = s.substr(0,s.length() - 1);
                    if(s.length() == 3 || (s.length() == 4 && s[2] == '-'))
                        x = 37;
                    else
                        x = 38;
                }
            }
            x--;
			s = s.substr(0,s.length() - 1);
			gotoxy(x,y);
			cout<<" ";
        }else{
            if(kyTu == ESC){
                Normal();
                return;
            }
            else if(kyTu == ENTER){
                if(y == 17){

                    if(kiemTraMaSachTonTaiVaChuaMuon(ds,s,vitri,kiemTra) == 1){
                        if(kiemTraMaSachTrungMaDauSach(q->dataDocGia.ptr_muontra,s) == 0){
                            str[0] = s;
                            y += 2;
                            s = "";
                            x = 25;
                            SetBGColor(1);
                            xoaNoiDung(25,18,30);
                        }else{
                            SetBGColor(1);
                            SetColor(10);
                            ThongBao(25,18,"Da trung ma dau sach!");
                            Normal();
                        }
                    }else
                    {
                        SetBGColor(1);
                        SetColor(10);
                        xoaNoiDung(25,18,30);
                        if(kiemTra == 0)
                            ThongBao(25,18,"Ma sach khong ton tai!");
                        else if(kiemTra == 1)
                            ThongBao(25,18,"Ma sach da co doc gia muon!");
                        else
                            ThongBao(25,18,"Ma sach da thanh ly!");
                        Normal();
                    }
                    SetBGColor(15);
                    SetColor(0);
                }
                else if(y == 19){
                    if(x == 26 || x == 27){
                        s = s + "-";
                        x = 36;
                    }
                    if(x == 37 || x == 38){
                        s = s + "-";
                        x = 47;
                    }
                    if(x == 51){
                        SetBGColor(1);
                        SetColor(10);
                        xoaNoiDung(25,20,30);
                        kiemTra = kiemTraNgayHopLe(s);
                        if(kiemTra == 2){
                            str[1] = s;
                            y += 2;
                            xoaNoiDung(25,20,30);
                        }else if(kiemTra == -1)
                            ThongBao(25,20,"Nam phai >= 2010!");
                        else if(kiemTra == 0)
                            ThongBao(25,20,"Thang phai >= 1 va <= 12!");
                        else if(kiemTra == 1)
                            ThongBao(25,20,"Ngay <= ngay cua thang!");
                        else
                            ThongBao(25,20,"Ngay <= ngay hien tai!");
                        Normal();
                    }
                }
            }
            else{
                toUpper(kyTu);
                if(x == 33 || x == 51)
                    continue;
                if(x == 27 && y == 19){
                    s += "-";
                    x = 36;
                }
                if(x == 38 && y == 19){
                    s += "-";
                    x = 47;
                }
                if((kyTu >= 48 && kyTu <= 57) || (((kyTu >= 65 && kyTu <= 90) || (kyTu >= 97 && kyTu <= 122)) && y  == 17)){
                    gotoxy(x,y);
                    cout<<kyTu;
                    s += kyTu;
                    x++;
                }
            }
        }
    }
    p.maSach = str[0];
    p.ngayMuon = str[1];
    p.ngayTra = "00-00-0000";
    p.trangThai = 0;

    SetBGColor(14);
    SetColor(0);
    gotoxy(27,21);
    cout<<"MUON";


    hidecursor(false);
    while(true){
        kyTu = getch();
        if(kyTu == ENTER){
            addFirstMuonTra(q->dataDocGia.ptr_muontra,p);
            q->dataDocGia.soLuongMuon++;
            First = ds.dsdsach[vitri]->listSach.head;
            ds.dsdsach[vitri]->soLuongMuon++;
            for(PTR_SACH r = First;r != NULL;r = r->next){
                if(r->dataSach.maSach == str[0]){
                    r->dataSach.trangThai = 1;
                    break;
                }
            }
            break;
        }
        if(kyTu == ESC){
            break;
        }
    }

    Normal();
}

// KIEM TRA NGAY TRA CO LON HON NGAY MUON
int kiemTraNgayTraLonHonNgayMuon(PTR_MUONTRA First,string ngayTra,string maSach){
    for(PTR_MUONTRA p = First;p != NULL;p = p->next){
        if(p->dataMuonTra.maSach == maSach && soNgayMuonSach(p->dataMuonTra.ngayMuon,ngayTra) > 0)
            return 1;
    }
    return 0;
}

// TRA SACH
void traSach(TREE_DOCGIA &root,DS_DAUSACH &ds,string &tenNhap,int maThe,string &maSach){
    int x = 25,y = 17;
    int vitri = -1;
    int kiemTra;
    char kyTu;
    hidecursor(true);
    string s = "",s1 = "";
    MUONTRA p;
    TREE_DOCGIA q = findNodeInTreeById(root,maThe);
    if(tenNhap == "F4")
        KhungNhapMuonTraSach(0,12,0);
    else
        KhungNhapMuonTraSach(0,12,2);
    string str[2] = {""};
    PTR_SACH First;
    while(true){
        SetBGColor(15);
        SetColor(0);
        if(y == 21)
            break;
        gotoxy(x,y);
        kyTu = getch();
        if(kyTu == BACKSPACE){
            if(x == 25)
                continue;
            if(y == 19){
                if(x == 36){
                    s = s.substr(0,s.length() - 1);
                    x = 25 + s.length();
                }
                if(x == 47){
                    s = s.substr(0,s.length() - 1);
                    if(s.length() == 3 || (s.length() == 4 && s[2] == '-'))
                        x = 37;
                    else
                        x = 38;
                }
            }
            x--;
			s = s.substr(0,s.length() - 1);
			gotoxy(x,y);
			cout<<" ";
        }else{
            if(kyTu == ESC){
                Normal();
                return;
            }
            else if(kyTu == ENTER){
                if(y == 17){
                    if(kiemTraMaSachCoNamTrongDsDangMuon(q->dataDocGia.ptr_muontra,s) == 1){
                        str[0] = s;
                        if(tenNhap == "F5")
                            y += 4;
                        else
                            y += 2;
                        s = "";
                        x = 25;
                        SetBGColor(1);
                        xoaNoiDung(25,18,35);
                    }else
                    {
                        SetBGColor(1);
                        SetColor(10);
                        ThongBao(25,18,"Ma sach nam ngoai sach dang muon!");
                        Normal();
                    }
                    SetBGColor(15);
                    SetColor(0);
                }
                else if(y == 19){
                    if(x == 26 || x == 27){
                        s = s + "-";
                        x = 36;
                    }
                    if(x == 37 || x == 38){
                        s = s + "-";
                        x = 47;
                    }
                    if(x == 51){
                        SetBGColor(1);
                        SetColor(10);
                        xoaNoiDung(25,20,30);
                        kiemTra = kiemTraNgayHopLe(s);
                        if(kiemTra == 2){
                            if(kiemTraNgayTraLonHonNgayMuon(q->dataDocGia.ptr_muontra,s,str[0]) == 1){
                                str[1] = s;
                                y += 2;
                                xoaNoiDung(25,20,30);
                            }
                            else{
                                xoaNoiDung(25,20,30);
                                ThongBao(25,20,"Ngay tra phai lon hon ngay muon!");
                            }

                        }else if(kiemTra == -1)
                            ThongBao(25,20,"Nam phai >= 2010!");
                        else if(kiemTra == 0)
                            ThongBao(25,20,"Thang phai >= 1 va <= 12!");
                        else if(kiemTra == 1)
                            ThongBao(25,20,"Ngay <= ngay cua thang!");
                        else
                            ThongBao(25,20,"Ngay <= ngay hien tai!");

                        Normal();
                    }
                }
            }
            else{
                toUpper(kyTu);
                if(x == 33 || x == 51)
                    continue;
                if(x == 27 && y == 19){
                    s += "-";
                    x = 36;
                }
                if(x == 38 && y == 19){
                    s += "-";
                    x = 47;
                }
                if((kyTu >= 48 && kyTu <= 57) || (((kyTu >= 65 && kyTu <= 90) || (kyTu >= 97 && kyTu <= 122)) && y  == 17)){
                    gotoxy(x,y);
                    cout<<kyTu;
                    s += kyTu;
                    x++;
                }
            }
        }
    }
    for(PTR_MUONTRA pMT = q->dataDocGia.ptr_muontra; pMT != NULL;pMT = pMT->next){
        if(pMT->dataMuonTra.maSach == str[0])
        {
            maSach = str[0];

            if(tenNhap == "F4"){
                pMT->dataMuonTra.ngayTra = str[1];
                pMT->dataMuonTra.trangThai = 1;
            }
            else{
                pMT->dataMuonTra.trangThai = 2;
            }
            break;
        }
    }

    SetBGColor(14);
    SetColor(0);
    if(tenNhap == "F4"){
        gotoxy(29,21);
        cout<<"TRA";
    }else{
        gotoxy(25,21);
        cout<<"BAO MAT";
    }



    hidecursor(false);
    string maDauSach = str[0].substr(0,4);
    while(true){
        kyTu = getch();
        if(kyTu == ENTER){
            q->dataDocGia.soLuongTra++;
            for(int i = 0;i < ds.sl;i++){
                if(ds.dsdsach[i]->ISBN == maDauSach){
                    vitri = i;
                    break;
                }
            }
            First = ds.dsdsach[vitri]->listSach.head;
            for(PTR_SACH r = First;r != NULL;r = r->next){
                if(r->dataSach.maSach == str[0]){
                    if(tenNhap == "F4")
                        r->dataSach.trangThai = 0;
                    else
                        r->dataSach.trangThai = 2;
                    break;
                }
            }
            break;
        }
        if(kyTu == ESC){
            break;
        }
    }

    Normal();
}

//QUAN LY MUON SACH
void QuanLyMuonSach(DS_DAUSACH &ds,TREE_DOCGIA &root){
    system("cls");
    TREE_DOCGIA tDgia;
	int x = 37,y = 13;
	int kiemTra = -1;
	int count = 0;
	string tenNhap = "";
	int vitri = -1,maThe = -1;
	char kyTu;
	string s = "";
    bool flag = true;
    time_t now;
    tm *ltm;
//	SetBGColor(15);
//	SetColor(0);
	while(true){
        if(flag == true){
            system("cls");
            hidecursor(true);
            KhungTimKiem(35,11,"NHAP MA DOC GIA DE MUON SACH");
            gotoxy(37,16);
            cout<<"F1: Xem danh sach doc gia!";
            if(vitri != -1){
                findNodeInTreeByPos(root,vitri + 1,count,maThe);
                gotoxy(37,13);
                SetBGColor(15);
                SetColor(0);
                cout<<maThe;
                s = changeToString(maThe);
                count = 0;
                maThe = -1;
                x = 37 + s.length();
            }else{
                x = s.length() + 37;
                gotoxy(37,13);
                SetBGColor(15);
                SetColor(0);
                cout<<s;
            }
            flag = false;
        }
        SetBGColor(15);
        SetColor(0);
        gotoxy(x,y);
        kyTu = getch();
        if(kyTu == 0){
            kyTu = getch();
            if(kyTu == F1){
                Normal();
                vitri = xemDanhSachDocGia(root);
            }
            flag = true;
        }else{
            toUpper(kyTu);
            if(kyTu == ESC){
                Normal();
                return;
            }
            if(kyTu == ENTER){
                Normal();
                maThe = atoi(s.c_str());
                tDgia = findNodeInTreeById(root,maThe);
                if(tDgia != NULL){
                    if(tDgia->dataDocGia.trangThaiThe == 0){
                        Normal();
                        SetBGColor(14);
                        SetColor(0);
                        gotoxy(37,14);
                        hidecursor(false);
                        cout<<"The da bi khoa!";
                        Sleep(2000);
                        hidecursor(true);
                        flag = true;
                        maThe = -1;
                        Normal();
                        vitri = -1;
                        continue;
                    }
                    if(tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra == 3){
                        Normal();
                        SetBGColor(14);
                        SetColor(0);
                        gotoxy(37,14);
                        hidecursor(false);
                        cout<<"Da muon toi da 3 quyen sach!";
                        Sleep(2000);
                        hidecursor(true);
                        flag = true;
                        maThe = -1;
                        Normal();
                        vitri = -1;
                        continue;
                    }
                    if(tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra > 0){
                        time_t now = time(0);
                        tm *ltm = localtime(&now);
                        string ngayHienTai = "";
                        ngayHienTai = changeToString(ltm->tm_mday) + "-" + changeToString(ltm->tm_mon + 1) + "-" + changeToString(1900 + ltm->tm_year);
                        for(PTR_MUONTRA pMT = tDgia->dataDocGia.ptr_muontra;pMT != NULL;pMT = pMT->next){
                            if(pMT->dataMuonTra.trangThai == 0){
                                if(soNgayMuonSach(pMT->dataMuonTra.ngayMuon,ngayHienTai) > 7){
                                    kiemTra = 1;
                                    break;
                                }
                            }
                        }
                        if(kiemTra == 1){
                            Normal();
                            SetBGColor(14);
                            SetColor(0);
                            gotoxy(37,14);
                            hidecursor(false);
                            cout<<"CO SACH MUON QUA HAN 7 NGAY!";
                            Sleep(2000);
                            hidecursor(true);
                            flag = true;
                            maThe = -1;
                            Normal();
                            vitri = -1;
                            kiemTra = -1;
                            continue;
                        }
                    }
                    vitri = -1;
                    flag = true;
                    while(true){
                        if(flag == true){
                            LietKeSachDangMuon(root,ds,0,maThe,"");
                            flag = false;
                            hidecursor(false);
                        }
                        kyTu = getch();
                        if(kyTu == ESC){
                            flag = true;
                            break;
                        }
                        if(kyTu == 0){
                            kyTu = getch();
                            if(kyTu == F3){
                                if(tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra == 3)
                                {
                                    SetColor(11);
                                    gotoxy(0,12);
                                    cout<<"So sach muon da toi da 3 quyen!";
                                    Sleep(2500);
                                    flag = true;
                                    Normal();
                                    break;
                                }else if(tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra > 0){
                                    time_t now = time(0);
                                    tm *ltm = localtime(&now);
                                    string ngayHienTai = "";
                                    ngayHienTai = changeToString(ltm->tm_mday) + "-" + changeToString(ltm->tm_mon + 1) + "-" + changeToString(1900 + ltm->tm_year);
                                    for(PTR_MUONTRA pMT = tDgia->dataDocGia.ptr_muontra;pMT != NULL;pMT = pMT->next){
                                        if(pMT->dataMuonTra.trangThai == 0){
                                            if(soNgayMuonSach(pMT->dataMuonTra.ngayMuon,ngayHienTai) > 7){
                                                kiemTra = 1;
                                                break;
                                            }
                                        }
                                    }
                                    if(kiemTra == 1){
                                        SetColor(11);
                                        gotoxy(0,12);
                                        cout<<"Da co sach muon qua han 7 ngay!";
                                        Sleep(2500);
                                        flag = true;
                                        Normal();
                                        kiemTra = -1;
                                        break;
                                    }
                                    kiemTra = -1;
                                }
                                if(kiemTra == -1){
                                    nhapMuonSach(root,ds,tenNhap,maThe);
                                    flag = true;
                                }
                            }
                        }

                    }
                }
                maThe = -1;
                //Normal();
            }
            else if(kyTu == BACKSPACE){
                if(x == 37)
                    continue;
                x--;
                s = s.substr(0,s.length() - 1);
                gotoxy(x,y);
                cout<<" ";
            }else if(kyTu >= 48 && kyTu <= 57){
                if(x == 41)
                    continue;
                gotoxy(x,y);
                cout<<kyTu;
                s += kyTu;
                x++;
            }
        }
	}
	Normal();

}

//Quan ly tra sach
void QuanLyTraSach(DS_DAUSACH &ds,TREE_DOCGIA &root){
    system("cls");
    TREE_DOCGIA tDgia;
    int chon = -1;
	int x = 37,y = 13;
	int soLuongSachMuon = -1;
	int count = 0;
	string maSach = "";
	string tenNhap = "";
	int vitri = -1,maThe = -1;
	char kyTu;
	string s = "";
    bool flag = true;
//	SetBGColor(15);
//	SetColor(0);
	while(true){
        if(flag == true){
            system("cls");
            hidecursor(true);
            KhungTimKiem(35,11,"NHAP MA DOC GIA DE TRA SACH");
            gotoxy(37,16);
            cout<<"F1: Xem danh sach doc gia!";
            if(vitri != -1){
                findNodeInTreeByPos(root,vitri + 1,count,maThe);
                gotoxy(37,13);
                SetBGColor(15);
                SetColor(0);
                cout<<maThe;
                s = changeToString(maThe);
                count = 0;
                maThe = -1;
                x = 37 + s.length();
            }else{
                x = s.length() + 37;
                gotoxy(37,13);
                SetBGColor(15);
                SetColor(0);
                cout<<s;
            }
            flag = false;
        }
        SetBGColor(15);
        SetColor(0);
        gotoxy(x,y);
        kyTu = getch();
        if(kyTu == 0){
            kyTu = getch();
            if(kyTu == F1){
                Normal();
                vitri = xemDanhSachDocGia(root);
            }
            flag = true;
        }else{
            toUpper(kyTu);
            if(kyTu == ESC){
                Normal();
                return;
            }
            if(kyTu == ENTER){
                Normal();
                maThe = atoi(s.c_str());
                tDgia = findNodeInTreeById(root,maThe);
                if(tDgia != NULL){
                    if(tDgia->dataDocGia.trangThaiThe == 0){
                        Normal();
                        SetBGColor(14);
                        SetColor(0);
                        gotoxy(37,14);
                        hidecursor(false);
                        cout<<"The da bi khoa!";
                        Sleep(2000);
                        hidecursor(true);
                        flag = true;
                        maThe = -1;
                        Normal();
                        vitri = -1;
                        continue;
                    }
                    if(tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra == 0){
                        Normal();
                        SetBGColor(14);
                        SetColor(0);
                        gotoxy(37,14);
                        hidecursor(false);
                        cout<<"Hien tai khong co sach dang muon!";
                        Sleep(2000);
                        hidecursor(true);
                        flag = true;
                        maThe = -1;
                        Normal();
                        vitri = -1;
                        continue;
                    }
                    vitri = -1;
                    flag = true;
                    soLuongSachMuon = tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra;
                    while(true){
                        if(flag == true){
                            LietKeSachDangMuon(root,ds,0,maThe,maSach,0);
                            maSach = "";
                            flag = false;
                            hidecursor(false);
                        }
                        kyTu = getch();
                        if(kyTu == ESC){
                            flag = true;
                            break;
                        }
                        if(kyTu == 0){
                            kyTu = getch();
                            if(kyTu == F4 || kyTu == F5){
                                if(tDgia->dataDocGia.soLuongMuon - tDgia->dataDocGia.soLuongTra == 0)
                                {
                                    SetColor(11);
                                    gotoxy(0,12);
                                    cout<<"Khong co sach de tra!";
                                    Sleep(2500);
                                    flag = true;
                                    Normal();
                                    break;
                                }
                                else{
                                    if(kyTu == F4)
                                        tenNhap = "F4";
                                    else
                                        tenNhap = "F5";
                                    traSach(root,ds,tenNhap,maThe,maSach);
                                    flag = true;
                                }
                            }
                        }

                    }
                }
                maThe = -1;
                //Normal();
            }
            else if(kyTu == BACKSPACE){
                if(x == 37)
                    continue;
                x--;
                s = s.substr(0,s.length() - 1);
                gotoxy(x,y);
                cout<<" ";
            }else if(kyTu >= 48 && kyTu <= 57){
                if(x == 41)
                    continue;
                gotoxy(x,y);
                cout<<kyTu;
                s += kyTu;
                x++;
            }
        }
	}
	Normal();

}

// top 10 sach co so luong muon nhieu nhat
void topTenBook(DS_DAUSACH &ds,listBookBorrowTimesNumber &listIndex){
    Normal();
    system("cls");
	int cs,j = 0;
	string tieude[3] = {"ISBN","TEN SACH","SO LUONG"};
	int x = 0,y = 0,w[3] = {7,30,11},h = 11,bcolor=0,tcolor=7;
	nboxDoAn(x,y,bcolor,tcolor,3,w,h);
	SetColor(14);
	for(int i = 0;i < 3;i++){
		gotoxy(x + canhChuKhoangCach(tieude[i].length(),w[i]),y + 1);
		cout<<tieude[i];
		x = x + w[i] + 1;
	}
	x = 0;
	y = 4;
	SetColor(15);
	for(int i = 0;i < listIndex.n;i++){
        if(i == 10)
            break;
	    cs = listIndex.nodes[i].chiso;
        gotoxy(x + 2,y + j);
        cout<<ds.dsdsach[cs]->ISBN;
        x = x + w[0] + 1;
        gotoxy(x + 2,y + j);
		cout<<ds.dsdsach[cs]->tenSach;
        x = x + w[1] + 1;
        gotoxy(x + 5,y + j);
        cout<<ds.dsdsach[cs]->soLuongMuon;
		x = 0;
		j++;
    }
}

// SAP XEP TANG DAN THEO SO NGAY QUA HAN
void IndexBySoNgayQuaHan(TREE_DOCGIA root,listSoNgayQuaHan &listIndex){
    int i = 0;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string ngayHienTai = "";
    ngayHienTai = changeToString(ltm->tm_mday) + "-" + changeToString(ltm->tm_mon + 1) + "-" + changeToString(1900 + ltm->tm_year);
    soNutCuaCay(root,listIndex.n);
    listIndex.nodes = new IndexSoNgayQuaHan[listIndex.n];
    DoDuLieuSoNgayQuaHan(root,listIndex,i,ngayHienTai);
    listIndex.n = i;
    if(listIndex.n > 1){
        for(i = 0;i < listIndex.n - 1;i++){
            for(int j = i + 1;j < listIndex.n;j++){
                if(listIndex.nodes[i].soNgayQuaHan < listIndex.nodes[j].soNgayQuaHan)
                    swap(listIndex.nodes[i],listIndex.nodes[j]);
            }
        }
    }

}

// LIET DS DOC GIA DANG MUON SACH QUA HAN
void DsDgMuonSachQuaHan(TREE_DOCGIA root,listSoNgayQuaHan &listIndex){
    Normal();
    system("cls");
	int j = 0;
	string tieude[4] = {"MA DG","HO DG","TEN DG","NGAY QUA HAN"};
	int x = 0,y = 0,w[4] = {8,30,10,15},h = 21,bcolor=0,tcolor=7;
	nboxDoAn(x,y,bcolor,tcolor,4,w,h);
	SetColor(14);
	for(int i = 0;i < 4;i++){
		gotoxy(x + canhChuKhoangCach(tieude[i].length(),w[i]),y + 1);
		cout<<tieude[i];
		x = x + w[i] + 1;
	}
	x = 0;
	y = 4;
	int count = 0;
	int giaTriMaThe;
	SetColor(15);
	TREE_DOCGIA p;
	for(int i = 0;i < listIndex.n;i++){
        if(i == 20)
            break;
        giaTriMaThe = listIndex.nodes[i].maThe;
        p = findNodeInTreeById(root, giaTriMaThe);
        gotoxy(x + 2,y + j);
        cout<<p->dataDocGia.maThe;
        x = x + w[0] + 1;
        gotoxy(x + 2,y + j);
        cout<<p->dataDocGia.ho;
        x = x + w[1] + 1;
        gotoxy(x + 2,y + j);
        cout<<p->dataDocGia.ten;
        x = x + w[2] + 1;
        gotoxy(x + 5,y + j);
        cout<<listIndex.nodes[i].soNgayQuaHan;
        count++;
        if(count == 10)
            break;

		x = 0;
		j++;
    }
}


// THONG KE
void ThongKe(TREE_DOCGIA root,DS_DAUSACH &ds){
    system("cls");
    int chon = -1;
    char kyTu;
    bool flag = true;
    int x = 37,y = 10,bcolor = 2,tcolor = 7,w = 45,h = 4;
    string s[2] = {"DANH SACH DOC GIA MUON SACH QUA HAN","LIET KE 10 QUYEN SACH CO LUOT MUON CAO NHAT"};

    while(true){
        if(flag == true){
            system("cls");
            boxDoAn(x,y,w,h,bcolor,tcolor);
            Normal();
            gotoxy(x + canhChuKhoangCach(s[0].length(),45),y + 2);
            SetBGColor(2);
            cout<<s[0];
            Normal();
            bcolor = 0;
            boxDoAn(x,y + 6,w,h,bcolor,tcolor);
            Normal();
            gotoxy(x + canhChuKhoangCach(s[1].length(),45),y + 8);
            cout<<s[1];
            flag = false;
        }

        kyTu = getch();
        if(kyTu == ESC)
            break;
        if(kyTu == ENTER){
            if(chon == 2){
                flag = true;
                while(true){
                    if(flag == true){
                        listBookBorrowTimesNumber listIndex;
                        IndexByBookBorrowTimesNumber(ds,listIndex);
                        topTenBook(ds,listIndex);
                        flag = false;
                        chon = -1;
                    }
                    kyTu = getch();
                    if(kyTu == ESC){
                        flag = true;
                        break;
                    }
                }
            }else{
                chon = 1;
                flag = true;
                while(true){
                    if(flag == true){
                        listSoNgayQuaHan listIndex;
                        IndexBySoNgayQuaHan(root,listIndex);
                        DsDgMuonSachQuaHan(root,listIndex);
                        flag = false;
                        chon = -1;
                    }
                    kyTu = getch();
                    if(kyTu == ESC){
                        bcolor = 2;
                        flag = true;
                        break;
                    }
                }
            }
        }
        else if(kyTu == -32){
            kyTu = getch();
            if(kyTu == UP && chon > 1){
				Normal();
				bcolor = 0;
				boxDoAn(x,y + 6,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[1].length(),w),y + 8);
				cout<<s[1];
				chon = 1;
				bcolor = 2;
				boxDoAn(x,y,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[0].length(),w),y + 2);
				SetBGColor(2);
				cout<<s[0];
			}
			else if(kyTu == DOWN && chon < 2){
				Normal();
				bcolor = 0;
				boxDoAn(x,y,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[0].length(),w),y + 2);
				cout<<s[0];
				chon = 2;
				bcolor = 2;
				boxDoAn(x,y + 6,w,h,bcolor,tcolor);
				Normal();
				gotoxy(x + canhChuKhoangCach(s[1].length(),w),y + 8);
				SetBGColor(2);
				cout<<s[1];
			}
        }
    }
    Normal();
}

// QUAN LY THU VIEN
void QuanLyThuVien(){
	//resizeConsole(950, 500);
	int theSinhTuDong[511];
    sinhMaTuDongTheDocGia(theSinhTuDong,511);
    int checkTheSinhTuDong[511];
    for(int i = 0;i < 511;i++){
        checkTheSinhTuDong[i] = 0;
    }
    int viTriMathe = -1;
	int chon;
	string tenNhap = "";
	DS_DAUSACH ds;
	TREE_DOCGIA root = NULL;
	ds.sl = 0;
	LoadFileDauSach(ds);
	LoadFileDocGia(root,viTriMathe);
	Sleep(1000);
	for(int i = 0;i < 511;i++){
        if(viTriMathe == -1){
            viTriMathe++;
            break;
        }
        if(i == viTriMathe){
            checkTheSinhTuDong[i] = 1;
            viTriMathe++;
            break;
        }
        checkTheSinhTuDong[i] = 1;
    }

	while(true){
		system("cls");
		chon = menuDong();
		switch(chon){
			case 1:
				QuanLyDauSach(ds,tenNhap);
				break;
			case 2:
				menuQLDG(root,ds,theSinhTuDong,checkTheSinhTuDong,viTriMathe);
				break;
            case 3:
				QuanLyMuonSach(ds,root);
				break;
            case 4:
				QuanLyTraSach(ds,root);
				break;
            case 5:
                ThongKe(root,ds);
                break;
			case 6:
				SaveFileDauSach(ds);
				SaveFileDocGia(root);
				Sleep(1000);
				return;
		}
	}
}

int main()
{
	QuanLyThuVien();
	getch();
    return 0;
}

