#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int TABLE_SIZE = 20;

enum Status { KOSONG, TERISI, DIHAPUS };

struct Mahasiswa {
    long long nim;
    string nama;
    Status status;

    Mahasiswa() {
        nim = 0;
        nama = "";
        status = KOSONG;
    }
};

class HashTableMahasiswa {
private:
    vector<Mahasiswa> table;

    int hash1(long long key) {
        return key % 20;
    }

    int hash2(long long key) {
        return 19 - (key % 19);
    }

public:
    HashTableMahasiswa() {
        table.resize(TABLE_SIZE);
    }

    void insert(long long nim, string nama) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);
        int firstDeleted = -1;

        for (int i = 0; i < TABLE_SIZE; i++) {
            int index = (h1 + i * h2) % TABLE_SIZE;

            if (table[index].status == TERISI) {
                if (table[index].nim == nim) {
                    table[index].nama = nama; 
                    cout << "-> NIM " << nim << " diupdate di index " << index << endl;
                    return;
                }
                if (i == 0) {
                    cout << "Bentrok di index " << index << ", mencari index lain..." << endl;
                }
            } else if (table[index].status == DIHAPUS) {
                if (firstDeleted == -1) {
                    firstDeleted = index;
                }
            } else if (table[index].status == KOSONG) {
                int target = (firstDeleted != -1) ? firstDeleted : index;
                table[target].nim = nim;
                table[target].nama = nama;
                table[target].status = TERISI;
                cout << "-> NIM " << nim << " masuk ke index " << target << endl;
                return;
            }
        }

        if (firstDeleted != -1) {
            table[firstDeleted].nim = nim;
            table[firstDeleted].nama = nama;
            table[firstDeleted].status = TERISI;
            cout << "-> NIM " << nim << " masuk ke index " << firstDeleted << endl;
        } else {
            cout << "-> Hash Table penuh!" << endl;
        }
    }

    void search(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int index = (h1 + i * h2) % TABLE_SIZE;

            if (table[index].status == KOSONG) {
                break; 
            }
            if (table[index].status == TERISI && table[index].nim == nim) {
                cout << "Ketemu! NIM " << nim << " (" << table[index].nama << ") ada di index " << index << endl;
                return;
            }
        }
        cout << "NIM " << nim << " tidak ditemukan." << endl;
    }

    void remove(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int index = (h1 + i * h2) % TABLE_SIZE;

            if (table[index].status == KOSONG) {
                break;
            }
            if (table[index].status == TERISI && table[index].nim == nim) {
                table[index].status = DIHAPUS;
                cout << "NIM " << nim << " berhasil dihapus dari index " << index << endl;
                return;
            }
        }
        cout << "Gagal hapus, NIM " << nim << " tidak ada." << endl;
    }

    void display() {
        cout << "--- Isi Hash Table ---" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << "\t: ";
            if (table[i].status == TERISI) {
                cout << table[i].nim << " - " << table[i].nama << endl;
            } else if (table[i].status == DIHAPUS) {
                cout << "<Terhapus>" << endl;
            } else {
                cout << "<Kosong>" << endl;
            }
        }
    }
};

int main() {
    HashTableMahasiswa ht;
    int jumlahData;

    cout << "=== INPUT DATA MAHASISWA ===" << endl;
    cout << "Masukkan jumlah data yang ingin di-input: ";
    cin >> jumlahData;

    for (int i = 0; i < jumlahData; i++) {
        long long nim;
        string nama;
        cout << "\nData ke-" << i + 1 << endl;
        cout << "Masukkan NIM  : ";
        cin >> nim;
        cin.ignore();
        cout << "Masukkan Nama : ";
        getline(cin, nama);
        ht.insert(nim, nama);
    }

    ht.display();

    long long cariNIM;
    cout << "=== UJI PENCARIAN (SEARCH) ===" << endl;
    cout << "Masukkan NIM yang ingin dicari: ";
    cin >> cariNIM;
    ht.search(cariNIM);

    long long hapusNIM;
    cout << "UJI PENGHAPUSAN (REMOVE) ===" << endl;
    cout << "Masukkan NIM yang ingin dihapus: ";
    cin >> hapusNIM;
    ht.remove(hapusNIM);

    ht.display();

    return 0;
}