#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char kode[10];
    char nama[50];
    int stok;
    float harga;
} Barang;

Barang inventory[MAX];
int total = 0;

void loadFile();
void saveFile();
void inputBarang();
void tampilBarang();
void updateBarang();
void deleteBarang();
void sortByNama();
void sortByHarga();
void searchByHarga();
int validasiKode(char kode[]);
int kodeDuplikat(char kode[]);

void header(const char *title) {
    system("cls");
    printf("+----------------------------------------------+\n");
    printf("| %-44s |\n", title);
    printf("+----------------------------------------------+\n");
}

int main() {
    int pilihan;

    loadFile();

menu_ulang:
    system("cls");
    printf("+----------------------------------------------+\n");
    printf("|           SISTEM INVENTORY TOKO              |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Input Barang                              |\n");
    printf("| 2. Tampilkan Barang                          |\n");
    printf("| 3. Update Barang                             |\n");
    printf("| 4. Hapus Barang                              |\n");
    printf("| 5. Cari Barang (Kategori Harga)              |\n");
    printf("| 6. Sort Nama                                 |\n");
    printf("| 7. Sort Harga                                |\n");
    printf("| 8. Save & Exit                               |\n");
    printf("+----------------------------------------------+\n");
    printf("Pilih menu: ");
    scanf("%d", &pilihan);
    getchar();

    switch (pilihan) {
        case 1: inputBarang(); break;
        case 2: tampilBarang(); break;
        case 3: updateBarang(); break;
        case 4: deleteBarang(); break;
        case 5: searchByHarga(); break;
        case 6: sortByNama(); saveFile(); break;
        case 7: sortByHarga(); saveFile(); break;
        case 8: saveFile(); return 0;
        default:
            printf("Pilihan tidak valid.\n");
    }

    printf("\nTekan Enter untuk kembali ke menu...");
    getchar();
    goto menu_ulang;
}

int validasiKode(char kode[]) {
    if (strlen(kode) != 6) return 0;
    if (kode[0] != 'P' || kode[1] != 'R' || kode[2] != 'D') return 0;
    if (!isdigit(kode[3]) || !isdigit(kode[4]) || !isdigit(kode[5])) return 0;
    return 1;
}

int kodeDuplikat(char kode[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(inventory[i].kode, kode) == 0)
            return 1;
    }
    return 0;
}

void inputBarang() {
    header("INPUT BARANG");

    Barang b;

    while (1) {
        printf("Kode (PRDxxx): ");
        scanf(" %9s", b.kode);

        // cek format
        if (!validasiKode(b.kode)) {
            system("cls");
            header("INPUT BARANG");
            printf("Format kode salah! Contoh: PRD123\n\n");
            continue;
        }

        // cek duplikat
        if (kodeDuplikat(b.kode)) {
            system("cls");
            header("INPUT BARANG");
            printf("Kode '%s' sudah dipakai!\n\n", b.kode);
            continue;
        }

        break;
    }

    printf("Nama Barang  : ");
    scanf(" %49[^\n]", b.nama);

    printf("Stok         : ");
    scanf("%d", &b.stok);

    printf("Harga (Rp)   : ");
    scanf("%f", &b.harga);

    inventory[total++] = b;
    saveFile();

    printf("\nBarang berhasil ditambah!\n");
}

void tampilBarang() {
    header("DAFTAR BARANG");

    if (total == 0) {
        printf("Tidak ada data.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("[%s] %s | Stok: %d | Harga: Rp.%.0f\n",
            inventory[i].kode,
            inventory[i].nama,
            inventory[i].stok,
            inventory[i].harga
        );
    }
}

void updateBarang() {
    header("UPDATE BARANG");

    char kode[10];
    printf("Masukkan kode barang: ");
    scanf(" %9s", kode);

    for (int i = 0; i < total; i++) {
        if (strcmp(inventory[i].kode, kode) == 0) {
            printf("Stok baru  : ");
            scanf("%d", &inventory[i].stok);

            printf("Harga baru : ");
            scanf("%f", &inventory[i].harga);

            saveFile();
            printf("\nBerhasil update!\n");
            return;
        }
    }

    printf("Kode tidak ditemukan.\n");
}

void deleteBarang() {
    header("HAPUS BARANG");

    char kode[10];
    printf("Masukkan kode barang: ");
    scanf(" %9s", kode);

    for (int i = 0; i < total; i++) {
        if (strcmp(inventory[i].kode, kode) == 0) {
            for (int j = i; j < total - 1; j++)
                inventory[j] = inventory[j + 1];

            total--;
            saveFile();

            printf("\nBarang berhasil dihapus!\n");
            return;
        }
    }

    printf("Kode tidak ditemukan.\n");
}

void sortByNama() {
    header("SORT NAMA");

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (strcmp(inventory[i].nama, inventory[j].nama) > 0) {
                Barang tmp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = tmp;
            }
        }
    }

    printf("Berhasil sort berdasarkan Nama.\n");
}

void sortByHarga() {
    header("SORT HARGA");

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (inventory[j].harga < inventory[i].harga) {
                Barang tmp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = tmp;
            }
        }
    }

    printf("Berhasil sort berdasarkan Harga.\n");
}

void searchByHarga() {
    header("CARI BARANG (KATEGORI HARGA)");

    int kategori;
    // Hapus getchar() di sini karena sudah ditangani di main

    printf("0. Tampil Semua\n");
    printf("1. Murah (< 100000)\n");
    printf("2. Tengah (100000 - 500000)\n");
    printf("3. Mahal (> 500000)\n");
    printf("Pilih kategori: ");

    // Pastikan input adalah angka
    if (scanf("%d", &kategori) != 1) {
        printf("\nInput harus berupa angka!\n");
        while(getchar() != '\n'); // Bersihkan sisa buffer jika user input huruf
        return;
    }
    getchar(); // Membersihkan newline agar tidak mengganggu menu utama nantinya

    if (kategori < 0 || kategori > 3) {
        printf("\nKategori tidak valid!\n");
        return;
    }

    int found = 0;
    printf("\n=== HASIL PENCARIAN ===\n");

    for (int i = 0; i < total; i++) {
        float h = inventory[i].harga;
        int cocok = 0;

        if (kategori == 0) cocok = 1;
        else if (kategori == 1 && h < 100000) cocok = 1;
        else if (kategori == 2 && h >= 100000 && h <= 500000) cocok = 1;
        else if (kategori == 3 && h > 500000) cocok = 1;

        if (cocok) {
            printf("[%s] %s | Stok: %d | Harga: Rp.%.0f\n",
                   inventory[i].kode, inventory[i].nama, 
                   inventory[i].stok, inventory[i].harga);
            found = 1;
        }
    }

    if (!found) {
        printf("Tidak ada barang dalam kategori tersebut.\n");
    }
}

void saveFile() {
    FILE *fp = fopen("inventory.txt", "w");

    for (int i = 0; i < total; i++) {
        fprintf(fp, "%s || %s || %d || %.0f\n",
            inventory[i].kode,
            inventory[i].nama,
            inventory[i].stok,
            inventory[i].harga
        );
    }

    fclose(fp);
}

void loadFile() {
    FILE *fp = fopen("inventory.txt", "r");
    if (!fp) return;

    Barang b;
    char line[200];

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%9[^|] || %49[^|] || %d || %f",
                   b.kode, b.nama, &b.stok, &b.harga) == 4) {
            inventory[total++] = b;
        }
    }

    fclose(fp);
}

