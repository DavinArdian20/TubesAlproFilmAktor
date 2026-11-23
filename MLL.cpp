#include <iostream>
#include "MLL.h"

using namespace std;

void createListFilm(ListFilm &LF) {
    LF.first = nullptr;
    LF.last = nullptr;
}

void createListAktor(ListAktor &LA) {
    LA.first = nullptr;
    LA.last = nullptr;
}

void createBST(BSTFilm &root) {
    root = nullptr;
}

bool isEmptyFilm(ListFilm LF) {
    return LF.first == nullptr;
}

bool isEmptyAktor(ListAktor LA) {
    return LA.first == nullptr;
}

bool isEmptyRelasi(adrFilm f) {
    return f == nullptr || f->firstRelasi == nullptr;
}

adrFilm createElemenFilm(string kode, string judul, string genre, int tahun, double rating) {
    adrFilm p = new elemenFilm;
    p->info.kode = kode;
    p->info.judul = judul;
    p->info.genre = genre;
    p->info.tahunRilis = tahun;
    p->info.rating = rating;
    p->next = nullptr;
    p->prev = nullptr;
    p->firstRelasi = nullptr;
    return p;
}

adrAktor createElemenAktor(string id, string nama, string negara) {
    adrAktor p = new elemenAktor;
    p->info.id = id;
    p->info.nama = nama;
    p->info.negaraAsal = negara;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

adrRelasi createElemenRelasi(adrAktor a, string peran, bool utama) {
    adrRelasi p = new elemenRelasi;
    p->aktor = a;
    p->info.namaPeran = peran;
    p->info.isPemeranUtama = utama;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

BSTFilm createNodeBST(adrFilm f) {
    BSTFilm node = new nodeBST;
    node->film = f;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void insertBST(BSTFilm &root, adrFilm f) {
    if (root == nullptr) {
        root = createNodeBST(f);
    } else if (f->info.rating < root->film->info.rating) {
        insertBST(root->left, f);
    } else {
        insertBST(root->right, f);
    }
}

void addFilm(ListFilm &LF, BSTFilm &root, adrFilm f) {
    if (isEmptyFilm(LF)) {
        LF.first = f;
        LF.last = f;
    } else {
        f->prev = LF.last;
        LF.last->next = f;
        LF.last = f;
    }
    insertBST(root, f);
}

void addAktor(ListAktor &LA, adrAktor a) {
    if (isEmptyAktor(LA)) {
        LA.first = a;
        LA.last = a;
    } else {
        a->prev = LA.last;
        LA.last->next = a;
        LA.last = a;
    }
}

void addRelasi(adrFilm f, adrRelasi r) {
    if (f == nullptr || r == nullptr) {
        return;
    }
    if (isEmptyRelasi(f)) {
        f->firstRelasi = r;
    } else {
        adrRelasi q = f->firstRelasi;
        while (q->next != nullptr) {
            q = q->next;
        }
        q->next = r;
        r->prev = q;
    }
}

adrFilm searchFilm(ListFilm LF, string kode) {
    adrFilm p = LF.first;
    while (p != nullptr) {
        if (p->info.kode == kode) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

adrAktor searchAktor(ListAktor LA, string id) {
    adrAktor q = LA.first;
    while (q != nullptr) {
        if (q->info.id == id) {
            return q;
        }
        q = q->next;
    }
    return nullptr;
}

void displayListFilm(ListFilm LF) {
    if (isEmptyFilm(LF)) {
        cout << "(Belum ada data film)" << endl;
        return;
    }

    int no = 1;
    adrFilm f = LF.first;
    while (f != nullptr) {
        cout << no << ". " << f->info.judul << " (" << f->info.kode << ") | Tahun: "
             << f->info.tahunRilis << " | Genre: " << f->info.genre
             << " | Rating: " << f->info.rating << endl;

        adrRelasi r = f->firstRelasi;
        if (r == nullptr) {
            cout << "   (Belum ada data pemeran)" << endl;
        } else {
            while (r != nullptr) {
                cout << "   - " << r->aktor->info.nama << " sebagai " << r->info.namaPeran;
                if (r->info.isPemeranUtama) {
                    cout << " [Pemeran Utama]" << endl;
                } else {
                    cout << " [Pendukung]" << endl;
                }
                r = r->next;
            }
        }
        no++;
        f = f->next;
    }
}