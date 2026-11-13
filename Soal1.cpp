#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string NIM;
    char Nama[50]; 
    int Nilai;
    Mahasiswa* next;
};

Mahasiswa* head = NULL;

void tambahMahasiswa(string nim, char nama[], int nilai) {
    Mahasiswa* nodeBaru = new Mahasiswa;
    nodeBaru->NIM = nim;
    
    int i = 0;
    while (nama[i] != '\0' && i < 49) { 
        nodeBaru->Nama[i] = nama[i];
        i++;
    }
    nodeBaru->Nama[i] = '\0'; 
    
    nodeBaru->Nilai = nilai;
    nodeBaru->next = NULL;

    if (head == NULL) {
        head = nodeBaru;
    } else {
        Mahasiswa* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nodeBaru;
    }
}

void tampilkanDataMahasiswa() {
    Mahasiswa* temp = head;

    cout << "--- DATA SELURUH MAHASISWA ---" << endl;

    if (head == NULL) cout << "Data kosong!\n";
    
    while (temp != NULL) {
        cout << "NIM   : " << temp->NIM << endl;
        cout << "Nama  : " << temp->Nama << endl;
        cout << "Nilai : " << temp->Nilai << endl;
        cout << endl;
        temp = temp->next;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void linearSearchNIM(string targetNIM) {
    Mahasiswa* temp = head;
    bool ketemu = false;
    
    while (temp != NULL) {
        if (temp->NIM == targetNIM) {
            cout << "HASIL PENCARIAN NIM Mahasiswa Ditemukan: " << endl;
            cout << "NIM   : " << temp->NIM << endl;
            cout << "Nama  : " << temp->Nama << endl;
            cout << "Nilai : " << temp->Nilai << endl;
            ketemu = true;
            break;
        }
        temp = temp->next;
    }
    
    if (!ketemu) {
        cout << "HASIL PENCARIAN NIM Mahasiswa dengan NIM " << targetNIM << " TIDAK DITEMUKAN" << endl;
    }
}

void binarySearchNilai(int arr[], int n, int targetNilai) {
    int left = 0;
    int right = n - 1;
    bool ketemu = false;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == targetNilai) {
            cout << "HASIL PENCARIAN NILAI " << targetNilai << " DITEMUKAN dalam daftar nilai" << endl;
            ketemu = true;
            break;
        }
        
        if (arr[mid] < targetNilai) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    if (!ketemu) {
        cout << "HASIL PENCARIAN NILAI " << targetNilai << " TIDAK DITEMUKAN dalam daftar nilai" << endl;
    }
}

int main() {
    int jumlahMahasiswa;
    
    cout << "Masukkan Jumlah Mahasiswa : ";
    cin >> jumlahMahasiswa;
    
    int* arrayNilai = new int[jumlahMahasiswa];

    for (int i = 0; i < jumlahMahasiswa; i++) {
        string nim;
        char nama[50];
        int nilai;
        
        cout << "Input Data Mahasiswa Ke-" << i + 1 << endl;
        cout << "Masukkan NIM   : ";
        cin >> nim;
        
        cin.ignore(); 
        
        cout << "Masukkan Nama  : ";
        cin.getline(nama, 50); 
        
        cout << "Masukkan Nilai : ";
        cin >> nilai;
        
        tambahMahasiswa(nim, nama, nilai);
        
        arrayNilai[i] = nilai;
    }

    tampilkanDataMahasiswa();

    insertionSort(arrayNilai, jumlahMahasiswa);
    
    cout << "KUMPULAN NILAI (SETELAH INSERTION SORT)" << endl;
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << arrayNilai[i] << " ";
    }
    cout << endl;

    string cariNIM;
    cout << "Masukkan NIM yang ingin dicari (Linear Search): ";
    cin >> cariNIM;
    linearSearchNIM(cariNIM);

    int cariNilai;
    cout << "Masukkan Nilai yang ingin dicari (Binary Search): ";
    cin >> cariNilai;
    binarySearchNilai(arrayNilai, jumlahMahasiswa, cariNilai);

    delete[] arrayNilai;
    
    return 0;
}