#include <iostream>
using namespace std;

#define MAX 50

struct BSTNode {
    int idBuku;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* insertBST(BSTNode* root, int id) {
    if (root == NULL) {
        BSTNode* newNode = new BSTNode;
        newNode->idBuku = id;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    
    if (id < root->idBuku) 
        root->left = insertBST(root->left, id);
    else if (id > root->idBuku) 
        root->right = insertBST(root->right, id);
    return root;
}

bool searchBST(BSTNode* root, int id) {
    if (root == NULL) 
        return false;
    if (root->idBuku == id) 
        return true;
    if (root->idBuku < id) 
        return searchBST(root->right, id);
    return searchBST(root->left, id);
}

void preOrder(BSTNode* root) {
    if (root != NULL) {
        cout << root->idBuku << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(BSTNode* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->idBuku << " ";
        inOrder(root->right);
    }
}

void postOrder(BSTNode* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->idBuku << " ";
    }
}

int main(){
    char queue[MAX][50]; 
    int front = 0;
    int rear = -1;
    int stack[MAX];
    int top = -1;

    BSTNode* rootBST = NULL;

    int jumlah;

    cout << "--- ANTREAN PEMINJAMAN (QUEUE) ---" << endl;
    cout << "Berapa mahasiswa yang antre: ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        cout << "Nama mahasiswa ke-" << i + 1 << ": ";
        rear++;
        cin.getline(queue[rear], 50); 
    }

    cout << "\nIsi Queue Antrean: ";
    for (int i = front; i <= rear; i++) {
        cout << "[" << queue[i] << "] ";
    }
    cout << endl;

    if (front <= rear) {
        cout << "Dequeue: '" << queue[front] << "' maju meminjam buku." << endl;
        front++; 
    }

    cout << "Isi Queue sisa: ";
    for (int i = front; i <= rear; i++) {
        cout << "[" << queue[i] << "] ";
    }
    cout << "\n\n";

    cout << "--- DATA BUKU (BST) ---" << endl;
    cout << "Berapa buku yang ingin diinput: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; i++) {
        cout << "ID Buku ke-" << i + 1 << ": ";
        int idBuku;
        cin >> idBuku;
        rootBST = insertBST(rootBST, idBuku);
    }

    cout << "\nInformasi Data Buku (BST):" << endl;
    cout << "Pre-Order  : "; preOrder(rootBST); cout << endl;
    cout << "In-Order   : "; inOrder(rootBST); cout << endl;
    cout << "Post-Order : "; postOrder(rootBST); cout << endl;

    int cariID;
    cout << "\nMasukkan ID buku yang dicari: ";
    cin >> cariID;
    if (searchBST(rootBST, cariID)) {
        cout << "Kondisi: Buku DITEMUKAN" << endl;
    } else {
        cout << "Kondisi: Buku TIDAK DITEMUKAN" << endl;
    }
    cout << "\n";

    cout << "--- RIWAYAT PENGEMBALIAN (STACK) ---" << endl;
    cout << "Berapa buku yang ingin dikembalikan: ";
    cin >> jumlah;


    for (int i = 0; i < jumlah; i++) {
        cout << "ID Buku yang dikembalikan ke-" << i + 1 << ": ";
        int idKembali;
        cin >> idKembali;
        top++;
        stack[top] = idKembali;
    }

    cout << "\nSize Stack Riwayat: " << top + 1 << " buku" << endl;
    cout << "Riwayat dari yang paling baru dikembalikan:" << endl;

    while (top >= 0) {
        cout << "ID: " << stack[top] << endl;
        top--;
    }

    cout << "Size Stack setelah di-POP semua: " << top + 1 << endl;

    return 0;
}