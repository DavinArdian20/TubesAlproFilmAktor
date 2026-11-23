#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

typedef struct elemenFilm *adrFilm;
typedef struct elemenAktor *adrAktor;
typedef struct elemenRelasi *adrRelasi;
typedef struct nodeBST *BSTFilm;

struct Film {
    string kode;
    string judul;
    int tahunRilis;
    string genre;
    double rating;
};

struct Aktor {
    string id;
    string nama;
    string negaraAsal;
};

struct Relasi {
    string namaPeran;
    bool isPemeranUtama;
};

struct elemenRelasi {
    Relasi info;
    adrAktor aktor;
    adrRelasi next;
    adrRelasi prev;
};

struct elemenFilm {
    Film info;
    adrFilm next;
    adrFilm prev;
    adrRelasi firstRelasi;
};

struct elemenAktor {
    Aktor info;
    adrAktor next;
    adrAktor prev;
};

struct ListFilm {
    adrFilm first;
    adrFilm last;
};

struct ListAktor {
    adrAktor first;
    adrAktor last;
};

struct nodeBST {
    adrFilm film;
    BSTFilm left;
    BSTFilm right;
};

void createListFilm(ListFilm &LF);
void createListAktor(ListAktor &LA);
void createBST(BSTFilm &root);
bool isEmptyFilm(ListFilm LF);
bool isEmptyAktor(ListAktor LA);
bool isEmptyRelasi(adrFilm f);

adrFilm createElemenFilm(string kode, string judul, string genre, int tahun, double rating);
adrAktor createElemenAktor(string id, string nama, string negara);
adrRelasi createElemenRelasi(adrAktor a, string peran, bool utama);

void insertBST(BSTFilm &root, adrFilm f);
void addFilm(ListFilm &LF, BSTFilm &root, adrFilm f);
void addAktor(ListAktor &LA, adrAktor a);
void addRelasi(adrFilm f, adrRelasi r);
adrFilm searchFilm(ListFilm LF, string kode);
adrAktor searchAktor(ListAktor LA, string id);
void displayListFilm(ListFilm LF);

#endif // MLL_H_INCLUDED