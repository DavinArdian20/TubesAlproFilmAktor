#include <iostream>
#include <string>
#include "MLL.h"

using namespace std;

void tambahFilmDummy(ListFilm &LF, BSTFilm &root, string kode, string judul,
                     int tahun, string genre, double rating) {
    adrFilm f = createElemenFilm(kode, judul, genre, tahun, rating);
    addFilm(LF, root, f);
}

void tambahAktorDummy(ListAktor &LA, string id, string nama, string negara) {
    adrAktor a = createElemenAktor(id, nama, negara);
    addAktor(LA, a);
}

void tambahRelasiDummy(ListFilm &LF, ListAktor &LA, string kodeFilm, string idAktor,
                       string peran, bool utama) {
    adrFilm f = searchFilm(LF, kodeFilm);
    adrAktor a = searchAktor(LA, idAktor);
    if (f != nullptr && a != nullptr) {
        adrRelasi r = createElemenRelasi(a, peran, utama);
        addRelasi(f, r);
    }
}

void isiDataDummy(ListFilm &LF, ListAktor &LA, BSTFilm &root) {
    tambahFilmDummy(LF, root, "F001", "Inception",       2010, "Sci-Fi", 88.5);
    tambahFilmDummy(LF, root, "F002", "Interstellar",    2014, "Sci-Fi", 91.0);
    tambahFilmDummy(LF, root, "F003", "The Dark Knight", 2008, "Action", 94.0);

    tambahAktorDummy(LA, "A001", "Leonardo DiCaprio",   "Amerika Serikat");
    tambahAktorDummy(LA, "A002", "Matthew McConaughey", "Amerika Serikat");
    tambahAktorDummy(LA, "A003", "Anne Hathaway",       "Amerika Serikat");
    tambahAktorDummy(LA, "A004", "Christian Bale",      "Inggris");

    tambahRelasiDummy(LF, LA, "F001", "A001", "Dom Cobb",      true);
    tambahRelasiDummy(LF, LA, "F002", "A002", "Joseph Cooper", true);
    tambahRelasiDummy(LF, LA, "F002", "A003", "Amelia Brand",  true);
    tambahRelasiDummy(LF, LA, "F003", "A004", "Bruce Wayne",   true);
}

void menuTambahFilm(ListFilm &LF, BSTFilm &root) {
    string kode, judul, genre;
    int tahun;
    double rating;

    cout << "[INPUT DATA FILM]" << endl;
    cout << "Masukkan kode film: ";
    cin >> kode;

    if (searchFilm(LF, kode) != nullptr) {
        cout << "Gagal: kode film " << kode << " sudah ada." << endl;
        return;
    }

    cout << "Masukkan judul film: ";
    getline(cin >> ws, judul);
    cout << "Masukkan tahun rilis: ";
    cin >> tahun;
    cout << "Masukkan genre: ";
    cin >> genre;
    cout << "Masukkan rating (0-100): ";
    cin >> rating;

    adrFilm f = createElemenFilm(kode, judul, genre, tahun, rating);
    addFilm(LF, root, f);
    cout << "Film " << judul << " (" << kode << ") berhasil ditambahkan." << endl;
}

void menuTambahAktor(ListAktor &LA) {
    string id, nama, negara;

    cout << "[INPUT DATA AKTOR]" << endl;
    cout << "Masukkan ID aktor: ";
    cin >> id;

    if (searchAktor(LA, id) != nullptr) {
        cout << "Gagal: ID aktor " << id << " sudah ada." << endl;
        return;
    }

    cout << "Masukkan nama aktor: ";
    getline(cin >> ws, nama);
    cout << "Masukkan negara asal: ";
    getline(cin >> ws, negara);

    adrAktor a = createElemenAktor(id, nama, negara);
    addAktor(LA, a);
    cout << "Aktor " << nama << " (" << id << ") berhasil ditambahkan." << endl;
}

void menuTambahRelasi(ListFilm &LF, ListAktor &LA) {
    string kode, id, peran;
    int utama;

    cout << "[INPUT RELASI PERAN]" << endl;
    cout << "Masukkan kode film: ";
    cin >> kode;
    adrFilm f = searchFilm(LF, kode);
    if (f == nullptr) {
        cout << "Gagal: film tidak ditemukan." << endl;
        return;
    }

    cout << "Masukkan ID aktor: ";
    cin >> id;
    adrAktor a = searchAktor(LA, id);
    if (a == nullptr) {
        cout << "Gagal: aktor tidak ditemukan." << endl;
        return;
    }

    cout << "Masukkan nama peran: ";
    getline(cin >> ws, peran);
    cout << "Apakah pemeran utama (1=Ya, 0=Tidak): ";
    cin >> utama;

    adrRelasi r = createElemenRelasi(a, peran, utama == 1);
    addRelasi(f, r);
    cout << a->info.nama << " ditambahkan ke film " << f->info.judul << " sebagai " << peran << "." << endl;
}

void tampilSemuaAktor(ListAktor LA) {
    if (isEmptyAktor(LA)) {
        cout << "(Belum ada data aktor)" << endl;
        return;
    }
    int no = 1;
    adrAktor q = LA.first;
    while (q != nullptr) {
        cout << no << ". " << q->info.nama << " (" << q->info.id << ") | Negara: "
             << q->info.negaraAsal << endl;
        no++;
        q = q->next;
    }
}

void tampilMenu() {
    cout << endl;
    cout << "======= DATABASE FILM DAN AKTOR (PROGRESS 1) =======" << endl;
    cout << "  1. Tambah film" << endl;
    cout << "  2. Tambah aktor" << endl;
    cout << "  3. Tambah relasi peran (film-aktor)" << endl;
    cout << "  4. Tampilkan semua film beserta aktor" << endl;
    cout << "  5. Tampilkan semua aktor" << endl;
    cout << "  0. Keluar" << endl;
    cout << "====================================================" << endl;
}

int main() {
    ListFilm LFilm;
    ListAktor LAktor;
    BSTFilm root;

    createListFilm(LFilm);
    createListAktor(LAktor);
    createBST(root);

    isiDataDummy(LFilm, LAktor, root);
    cout << "Data dummy awal dimuat: 3 film, 4 aktor, beserta relasi peran." << endl;

    int pilih = -1;
    while (pilih != 0) {
        tampilMenu();
        cout << "Pilih menu: ";
        cin >> pilih;
        cout << endl;

        if (pilih == 1) {
            menuTambahFilm(LFilm, root);
        } else if (pilih == 2) {
            menuTambahAktor(LAktor);
        } else if (pilih == 3) {
            menuTambahRelasi(LFilm, LAktor);
        } else if (pilih == 4) {
            displayListFilm(LFilm);
        } else if (pilih == 5) {
            tampilSemuaAktor(LAktor);
        } else if (pilih == 0) {
            cout << "Program selesai." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}