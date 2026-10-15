#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Game {
    int score;
	int kondisi;
    string pemain; 
    char ulangi;
};


struct DataSkor {
    string nama;
    int skor;
};

// Membandingkan skor dari tertinggi ke terendah
bool BandingkanSkor(DataSkor a, DataSkor b) {
    return a.skor > b.skor;
}

// Membaca data leaderboard dari file
vector<DataSkor> BacaLeaderboard() {
    vector<DataSkor> data;
    ifstream file("top.txt");

    if (!file.is_open()) {
        return data;
    }

    string isi(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    file.close();

    // Format baru: skor|nama
    if (isi.find('|') != string::npos) {
        stringstream ss(isi);
        string baris;

        while (getline(ss, baris)) {
            size_t pemisah = baris.find('|');

            if (pemisah == string::npos) {
                continue;
            }

            string teksSkor = baris.substr(0, pemisah);
            string nama = baris.substr(pemisah + 1);

            if (nama.empty()) {
                continue;
            }

            stringstream konversi(teksSkor);
            int skor;

            if (konversi >> skor) {
                DataSkor pemain;
                pemain.nama = nama;
                pemain.skor = skor;
                data.push_back(pemain);
            }
        }
    }
    // Format lama: nama skor nama skor ...
    else {
        stringstream ss(isi);
        string nama;
        int skor;

        while (ss >> nama >> skor) {
            DataSkor pemain;
            pemain.nama = nama;
            pemain.skor = skor;
            data.push_back(pemain);
        }
    }

    return data;
}


// Mengurutkan dan menyimpan tiga skor terbaik
void SimpanSkor(string nama, int skorBaru) {
    vector<DataSkor> data = BacaLeaderboard();

    bool ditemukan = false;

    // Jika pemain sudah terdaftar, simpan skor terbaiknya saja
    for (int i = 0; i < (int)data.size(); i++) {
        if (data[i].nama == nama) {
            if (skorBaru > data[i].skor) {
                data[i].skor = skorBaru;
            }

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        DataSkor pemain;
        pemain.nama = nama;
        pemain.skor = skorBaru;
        data.push_back(pemain);
    }

    
    // Urutkan dari skor tertinggi ke terendah
	sort(data.begin(), data.end(), BandingkanSkor);

    // Batasi hanya tiga pemain terbaik
    if (data.size() > 3) {
        data.resize(3);
    }

    // Simpan dengan format skor|nama
    ofstream file("top.txt");

    for (int i = 0; i < (int)data.size(); i++) {
        file << data[i].skor << "|" << data[i].nama << "\n";
    }

    file.close();
}


// Menampilkan leaderboard
void TampilkanLeaderboard() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    vector<DataSkor> data = BacaLeaderboard();

    system("cls");

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\n";
    cout << "========================================================\n";
    cout << "                     LEADERBOARD\n";
    cout << "                 MATH QUIZ GAME\n";
    cout << "========================================================\n\n";

    if (data.empty()) {
        SetConsoleTextAttribute(hConsole, 11);
        cout << "              Belum ada skor pemain.\n";
        cout << "           Ayo bermain dan catat skor!\n\n";
    } 
    else {
        SetConsoleTextAttribute(hConsole, 11);

        cout << "   RANK       PLAYER NAME                  SCORE\n";
        cout << "   ----------------------------------------------------\n";

        for (int i = 0; i < (int)data.size(); i++) {
            // Warna khusus untuk peringkat 1, 2, dan 3
            if (i == 0) {
                SetConsoleTextAttribute(hConsole, 14); // Kuning
            } 
            else if (i == 1) {
                SetConsoleTextAttribute(hConsole, 11); // Biru muda
            } 
            else {
                SetConsoleTextAttribute(hConsole, 11);  // Emas gelap
            }

            string peringkat;

            if (i == 0) {
                peringkat = "#1";
            } 
            else if (i == 1) {
                peringkat = "#2";
            } 
            else {
                peringkat = "#3";
            }

            cout << "   " << left << setw(10) << peringkat
                 << setw(30) << data[i].nama
                 << right << setw(5) << data[i].skor
                 << "\n";
        }

        cout << "\n";
    }

    SetConsoleTextAttribute(hConsole, 11);
    cout << "========================================================\n";

    SetConsoleTextAttribute(hConsole, 11);
}


int *GetChoice(){
	int *choice = new int(1); char button; system("cls");
	    cout<<"   =========================\n";
	    cout << ((*choice == 1) ? "      [  PLAY AGAIN  ]" : "         PLAY AGAIN  ") << endl;
	    cout << ((*choice == 2) ? "      [     BACK     ]" : "            BACK     ") << endl;
	    cout<<"   =========================\n";
		while (true) { button = getch();
		    if (button == 13) {  return choice; }// Tombol enter 
		    else if (button == 72) { *choice = (*choice == 1) ? 2 : *choice - 1;}// Tombol panah atas 
		    else if (button == 80) { *choice = (*choice == 2) ? 1 : *choice + 1;}system("cls");// Tombol panah bawah
			    cout<<"   =========================\n";
			    cout << ((*choice == 1) ? "      [  PLAY AGAIN  ]" : "         PLAY AGAIN  ") << endl;
			    cout << ((*choice == 2) ? "      [     BACK     ]" : "            BACK     ") << endl;
			    cout<<"   =========================\n";
		}
			 delete choice;
}



int* MenuPilihan() {
    int* pilihan = new int(1);
    char key;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    const int PUTIH = 15;
    const int BIRU = 11;
    const int KUNING = 14;

    const int JUMLAH_MENU = 4;
    const int LEBAR_MENU = 50;

    const string menu[] = {
        "START GAME",
        "LEADERBOARD",
        "HELP",
        "QUIT"
    };

    while (true) {
        system("cls");

        // Judul menu utama
        SetConsoleTextAttribute(hConsole, BIRU);
        cout << "\n";
        cout << "========================================================\n";
        cout << "                  MATH QUIZ GAME\n";
        cout << "             Challenge Your Math Skills!\n";
        cout << "========================================================\n\n";

        // Menampilkan semua menu
        for (int i = 1; i <= JUMLAH_MENU; i++) {

            string label = menu[i - 1];

            int kiri = (LEBAR_MENU - (int)label.length()) / 2;
            int kanan = LEBAR_MENU - (int)label.length() - kiri;

            // Jika dipilih: kuning.
            // Jika tidak dipilih: kotak putih, tulisan biru.
            int warnaKotak = (i == *pilihan) ? KUNING : PUTIH;
            int warnaTulisan = (i == *pilihan) ? KUNING : BIRU;

            // Bingkai atas
            SetConsoleTextAttribute(hConsole, warnaKotak);
            cout << "  +" << string(LEBAR_MENU, '-') << "+\n";

            // Tulisan menu
            SetConsoleTextAttribute(hConsole, warnaKotak);
            cout << "  |";

            SetConsoleTextAttribute(hConsole, warnaTulisan);
            cout << string(kiri, ' ')
                 << label
                 << string(kanan, ' ');

            SetConsoleTextAttribute(hConsole, warnaKotak);
            cout << "|\n";

            // Bingkai bawah
            cout << "  +" << string(LEBAR_MENU, '-') << "+\n\n";
        }

        // Petunjuk navigasi
        SetConsoleTextAttribute(hConsole, BIRU);
        cout << "       Gunakan PANAH ATAS / BAWAH untuk memilih\n";
        cout << "                    ENTER: Pilih\n";

        // Membaca input keyboard
        key = getch();

        if (key == 0 || key == -32) {
            key = getch();

            if (key == 72) {
                // Panah atas
                (*pilihan)--;

                if (*pilihan < 1) {
                    *pilihan = JUMLAH_MENU;
                }
            }
            else if (key == 80) {
                // Panah bawah
                (*pilihan)++;

                if (*pilihan > JUMLAH_MENU) {
                    *pilihan = 1;
                }
            }
        }
        else if (key == 13) {
            SetConsoleTextAttribute(hConsole, 7);
            return pilihan;
        }
    }
}


int MenuModeGame() {
    int pilihan = 1;
    char tombol;

    const int JUMLAH_MENU = 3;

    while (true) {
        system("cls");

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, 11);
        cout << "\n";
        cout << "============================================================\n";
        cout << "                       MATH QUIZ GAME\n";
        cout << "============================================================\n\n";

        SetConsoleTextAttribute(hConsole, 11);
        cout << "                      CHOOSE YOUR QUIZ\n\n";

        // Menu horizontal berbentuk kartu
        const char* namaMenu[] = {
            "SOAL ISIAN",
            "PILIHAN GANDA",
            "GABUNGAN"
        };

        const int WARNA_BIRU = 9;
        const int WARNA_ORANYE = 6;
        const int WARNA_NORMAL = 7;

        // Baris atas kartu
        cout << "  ";
        for (int i = 1; i <= JUMLAH_MENU; i++) {
            SetConsoleTextAttribute(
                hConsole,
                (i == pilihan) ? WARNA_ORANYE : WARNA_BIRU
            );

            cout << "+----------------+";
            if (i < JUMLAH_MENU) cout << " ";
        }

        // Baris kosong di dalam kartu
        cout << "\n  ";
        for (int i = 1; i <= JUMLAH_MENU; i++) {
            SetConsoleTextAttribute(
                hConsole,
                (i == pilihan) ? WARNA_ORANYE : WARNA_BIRU
            );

            cout << "|                |";
            if (i < JUMLAH_MENU) cout << " ";
        }

        // Nama menu
        cout << "\n  ";
        for (int i = 1; i <= JUMLAH_MENU; i++) {
            SetConsoleTextAttribute(
                hConsole,
                (i == pilihan) ? WARNA_ORANYE : WARNA_BIRU
            );

            int panjang = 16;
            int spasiKiri = (panjang - (int)strlen(namaMenu[i - 1])) / 2;
            int spasiKanan = panjang
                - (int)strlen(namaMenu[i - 1])
                - spasiKiri;

            cout << "|"
                 << string(spasiKiri, ' ')
                 << namaMenu[i - 1]
                 << string(spasiKanan, ' ')
                 << "|";

            if (i < JUMLAH_MENU) cout << " ";
        }

        // Baris kosong di dalam kartu
        cout << "\n  ";
        for (int i = 1; i <= JUMLAH_MENU; i++) {
            SetConsoleTextAttribute(
                hConsole,
                (i == pilihan) ? WARNA_ORANYE : WARNA_BIRU
            );

            cout << "|                |";
            if (i < JUMLAH_MENU) cout << " ";
        }

        // Baris bawah kartu
        cout << "\n  ";
        for (int i = 1; i <= JUMLAH_MENU; i++) {
            SetConsoleTextAttribute(
                hConsole,
                (i == pilihan) ? WARNA_ORANYE : WARNA_BIRU
            );

            cout << "+----------------+";
            if (i < JUMLAH_MENU) cout << " ";
        }

        SetConsoleTextAttribute(hConsole, WARNA_BIRU);

        cout << "\n\n";
        cout << "        Gunakan PANAH KIRI / KANAN untuk memilih\n";
        cout << "               ENTER: Pilih    ESC: Kembali\n\n";
        cout << "============================================================\n";

        tombol = getch();

        // Tombol panah pada Windows biasanya diawali 0 atau 224
        if (tombol == 0 || tombol == -32) {
            tombol = getch();

            if (tombol == 75) {
                pilihan--;
                if (pilihan < 1) pilihan = JUMLAH_MENU;
            } else if (tombol == 77) {
                pilihan++;
                if (pilihan > JUMLAH_MENU) pilihan = 1;
            }
        } else if (tombol == 13) {
            SetConsoleTextAttribute(hConsole, 7);
            return pilihan;
        } else if (tombol == 27) {
            SetConsoleTextAttribute(hConsole, 7);
            return 0;
        }
    }
}

string AngkaKeString(int angka) {
    stringstream ss;
    ss << angka;
    return ss.str();
}

const int WARNA_SOAL  = 11; // Biru muda saat menjawab
const int WARNA_BENAR = 10; // Hijau
const int WARNA_SALAH = 12; // Merah
const int WARNA_WAKTU = 14; // Kuning
const int WARNA_PUTIH = 15;

void GarisSoal(int warna) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, warna);

    cout << "+---------------------------------------------------------------------+\n";
}

void BarisSoal(string teks, int warna) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, warna);

    cout << "| " << left << setw(67) << teks << " |\n";
}


void TampilkanSoal(
    int level,
    string namaLevel,
    int nomor,
    string pertanyaan,
    int skor,
    int batasWaktu,
    int warna,
    string status = "",
    string jawabanBenar = "",
    int waktuTersisa = -1
) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");

    GarisSoal(warna);

    BarisSoal(
        "LEVEL " + AngkaKeString(level) + " : " + namaLevel,
        warna
    );

    // Tetap menampilkan waktu awal, bukan sisa waktu.
    BarisSoal(
        "Waktu menjawab: " + AngkaKeString(batasWaktu) + " detik",
        warna
    );

    GarisSoal(warna);
    BarisSoal("", warna);

    BarisSoal(
        "QUESTION " + AngkaKeString(nomor) + " : " + pertanyaan,
        warna
    );

    BarisSoal("", warna);

    // Jika waktuTersisa belum diberikan, gunakan batasWaktu.
    int waktuTampil = batasWaktu;

    if (waktuTersisa >= 0) {
        waktuTampil = waktuTersisa;
    }

    BarisSoal(
        "SCORE : " + AngkaKeString(skor) +
        "                         TIME : " +
        AngkaKeString(waktuTampil) + " SECONDS",
        warna
    );

    BarisSoal("", warna);

    if (status != "") {
        GarisSoal(warna);
        BarisSoal("", warna);
        BarisSoal(status, warna);

        if (jawabanBenar != "") {
            BarisSoal(
                "Correct Answer : " + jawabanBenar,
                warna
            );
        }

        BarisSoal("", warna);
    }

    GarisSoal(warna);

    SetConsoleTextAttribute(hConsole, 11);

    if (status != "") {
        cout << "\n";
        cout << "                 Press any key to continue . . .";
        getch();
    }
}



bool SoalDenganHitungMundur(
    int level,
    string namaLevel,
    int nomor,
    string pertanyaan,
    int skor,
    int batasWaktu,
    int warna,
    int &numInput,
    int &sisaWaktuAkhir
) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Ambil teks soal sampai tanda "=".
    size_t posisiSamaDengan = pertanyaan.find('=');

    string soal = pertanyaan;

    if (posisiSamaDengan != string::npos) {
        soal = pertanyaan.substr(0, posisiSamaDengan + 1) + " ";
    }

    string teksSoal =
        "QUESTION " + AngkaKeString(nomor) + " : " + soal;

    int posisiInputX = 2 + (int)teksSoal.length();
    int posisiInputY = 5;

    string input = "";

    system("cls");

    // Tampilkan kerangka soal.
    GarisSoal(warna);
    BarisSoal(
        "LEVEL " + AngkaKeString(level) + " : " + namaLevel,
        warna
    );
    BarisSoal(
        "Waktu menjawab: " + AngkaKeString(batasWaktu) + " detik",
        warna
    );
    GarisSoal(warna);

    BarisSoal("", warna);

    SetConsoleTextAttribute(hConsole, warna);
    cout << "| " << left << setw(67) << teksSoal << " |\n";

    BarisSoal("", warna);

    string teksSkor =
        "SCORE : " + AngkaKeString(skor) +
        "                         TIME : " +
        AngkaKeString(batasWaktu) + " SECONDS";

    BarisSoal(teksSkor, warna);
    BarisSoal("", warna);
    GarisSoal(warna);

    // Mulai hitung waktu setelah soal ditampilkan.
    DWORD mulai = GetTickCount();
    int sisaSebelumnya = batasWaktu;
    sisaWaktuAkhir = batasWaktu;

    // Posisikan kursor tepat setelah tanda "=".
    COORD posisi;
    posisi.X = (SHORT)posisiInputX;
    posisi.Y = (SHORT)posisiInputY;
    SetConsoleCursorPosition(hConsole, posisi);

    while (true) {
        DWORD berlalu = GetTickCount() - mulai;

        // Waktu habis: segera hentikan input.
        if (berlalu >= (DWORD)(batasWaktu * 1000)) {
        	sisaWaktuAkhir = 0;
            return false;
        }

        int sisaWaktu =
            batasWaktu - (int)(berlalu / 1000);

        // Perbarui tulisan TIME LIMIT setiap detik.
        
        // Perbarui tulisan TIME setiap detik.
        if (sisaWaktu != sisaSebelumnya) {
            sisaSebelumnya = sisaWaktu;

            string teksWaktu =
                "SCORE : " + AngkaKeString(skor) +
                "                         TIME : " +
                AngkaKeString(sisaWaktu) + " SECONDS";

            posisi.X = 0;
            posisi.Y = 7;
            SetConsoleCursorPosition(hConsole, posisi);

            // Warna kuning saat waktu tersisa 3 detik atau kurang.
            int warnaWaktu = (sisaWaktu <= 3)
                             ? 14
                             : warna;

            BarisSoal(teksWaktu, warnaWaktu);

            // Kembalikan kursor ke posisi input jawaban.
            posisi.X = (SHORT)(
                posisiInputX + (int)input.length()
            );
            posisi.Y = (SHORT)posisiInputY;
            SetConsoleCursorPosition(hConsole, posisi);
        }


        if (kbhit()) {
            char tombol = getch();

            // ENTER untuk mengirim jawaban.
            if (tombol == 13) {
                if (input.empty()) {
                    continue;
                }

                stringstream ss(input);

                if (ss >> numInput) {
                	DWORD waktuSekarang = GetTickCount() - mulai;

				    sisaWaktuAkhir =
				        batasWaktu - (int)(waktuSekarang / 1000);
				
				    if (sisaWaktuAkhir < 0) {
				        sisaWaktuAkhir = 0;
				    }
                    return true;
                }
            }

            // BACKSPACE untuk menghapus angka.
            else if (tombol == 8) {
                if (!input.empty()) {
                    input.erase(input.length() - 1);

                    posisi.X = (SHORT)(
                        posisiInputX + (int)input.length()
                    );
                    posisi.Y = (SHORT)posisiInputY;

                    SetConsoleCursorPosition(hConsole, posisi);
                    cout << ' ';

                    SetConsoleCursorPosition(hConsole, posisi);
                }
            }

            // Hanya menerima angka.
            else if (tombol >= '0' && tombol <= '9') {
                // Cegah input melewati batas kotak.
                if (posisiInputX + (int)input.length() < 68) {
                    input += tombol;
                    cout << tombol;
                }
            }
        }
    }
}



/*
    Membaca jawaban dengan batas waktu.
    Mengembalikan true jika pemain menekan ENTER.
    Mengembalikan false jika waktu habis.
*/
bool InputJawaban(int batasWaktu, int &jawaban) {
    DWORD mulai = GetTickCount();
    string input = "";

    while (true) {
        // Periksa waktu terlebih dahulu.
        if (GetTickCount() - mulai >=
            (DWORD)(batasWaktu * 1000)) {
            return false;
        }

        // Baca tombol jika ada input dari pemain.
        if (kbhit()) {
            char tombol = getch();

            // ENTER: jawaban selesai dimasukkan.
            if (tombol == 13) {
                if (input.empty()) {
                    continue;
                }

                stringstream ss(input);
                ss >> jawaban;

                return true;
            }

            // BACKSPACE: hapus angka terakhir.
            else if (tombol == 8) {
                if (!input.empty()) {
                    input.erase(input.length() - 1);
                    cout << "\b \b";
                }
            }

            // Terima angka 0 sampai 9 saja.
            else if (tombol >= '0' && tombol <= '9') {
                input += tombol;
                cout << tombol;
            }
        }
    }
}



void TampilkanGameOver(string nama, int skor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");

    const int MERAH = 12;
    const int KUNING = 14;
    const int BIRU = 11;
    const int PUTIH = 15;

    // Lebar isi kotak dibuat tetap
    const int LEBAR = 50;

    SetConsoleTextAttribute(hConsole, MERAH);

    cout << "\n\n";
    cout << "  +--------------------------------------------------+\n";
    cout << "  |                                                  |\n";
    cout << "  |                    GAME OVER                     |\n";
    cout << "  |                                                  |\n";
    cout << "  +--------------------------------------------------+\n";

    // Baris nama pemain
    SetConsoleTextAttribute(hConsole, MERAH);
    cout << "  |  Player       : ";

    SetConsoleTextAttribute(hConsole, KUNING);

    // Nama maksimal 31 karakter agar tidak melewati kotak
    if (nama.length() > 31) {
        nama = nama.substr(0, 28) + "...";
    }

    cout << left << setw(33) << nama;

    SetConsoleTextAttribute(hConsole, MERAH);
    cout << "|\n";

    // Baris skor
    cout << "  |  Final Score  : ";

    SetConsoleTextAttribute(hConsole, KUNING);
    cout << left << setw(33) << skor;

    SetConsoleTextAttribute(hConsole, MERAH);
    cout << "|\n";

    // Penutup kotak
    cout << "  +--------------------------------------------------+\n";

    SetConsoleTextAttribute(hConsole, BIRU);
    cout << "\n            KEEP PRACTICING AND TRY AGAIN!\n";
    cout << "              Better luck next time!\n\n";

    SetConsoleTextAttribute(hConsole, MERAH);

    Beep(2000, 200);
    Beep(1600, 200);
    Beep(1200, 400);
}


/* =========================================
   MODE PILIHAN GANDA
   ========================================= */

// Membuat empat opsi dengan satu jawaban benar.
void BuatOpsiPG(int jawaban, int opsi[]) {
    opsi[0] = jawaban;

    for (int i = 1; i < 4; i++) {
        bool unik = false;
        int kandidat;

        while (!unik) {
            int selisih = rand() % 20 + 1;

            if (rand() % 2 == 0) {
                kandidat = jawaban + selisih;
            } else {
                kandidat = jawaban - selisih;
            }

            unik = true;

            for (int j = 0; j < i; j++) {
                if (opsi[j] == kandidat) {
                    unik = false;
                    break;
                }
            }
        }

        opsi[i] = kandidat;
    }

    // Acak posisi semua opsi.
    for (int i = 3; i > 0; i--) {
        int j = rand() % (i + 1);

        int sementara = opsi[i];
        opsi[i] = opsi[j];
        opsi[j] = sementara;
    }
}


// Membuat soal sesuai level.
void BuatSoalPG(
    int level,
    string &namaLevel,
    string &pertanyaan,
    int &jawaban
) {
    int A, B, C, D;

    switch (level) {
        case 1:
            namaLevel = "ADDING QUIZ";
            A = rand() % 20 + 1;
            B = rand() % 20 + 1;

            pertanyaan = AngkaKeString(A) + " + "
                       + AngkaKeString(B) + " = ?";
            jawaban = A + B;
            break;

        case 2:
            namaLevel = "SUBTRACTING QUIZ";
            A = rand() % 100 + 1;
            B = rand() % 100 + 1;

            if (A < B) {
                int sementara = A;
                A = B;
                B = sementara;
            }

            pertanyaan = AngkaKeString(A) + " - "
                       + AngkaKeString(B) + " = ?";
            jawaban = A - B;
            break;

        case 3:
            namaLevel = "DIVISION QUIZ";
            B = rand() % 8 + 1;
            jawaban = rand() % 8 + 1;
            A = B * jawaban;

            pertanyaan = AngkaKeString(A) + " / "
                       + AngkaKeString(B) + " = ?";
            break;

        case 4:
            namaLevel = "MULTIPLICATION QUIZ";
            A = rand() % 8 + 1;
            B = rand() % 8 + 1;

            pertanyaan = AngkaKeString(A) + " x "
                       + AngkaKeString(B) + " = ?";
            jawaban = A * B;
            break;

        case 5:
            namaLevel = "FINAL QUIZ";

            A = rand() % 10 + 6;
            B = rand() % 10 + 6;
            C = rand() % 10 + 6;
            D = rand() % 10 + 6;

            pertanyaan = AngkaKeString(D) + " + "
                       + AngkaKeString(C) + " x "
                       + AngkaKeString(A) + " / "
                       + AngkaKeString(B) + " = ?";

            // Mengikuti urutan perhitungan pada mode soal isian.
            jawaban = D + (C * A) / B;
            break;
    }
}


// Menampilkan layar soal pilihan ganda.
void TampilkanLayarPG(
    int level,
    string namaLevel,
    string pertanyaan,
    int skor,
    int batasWaktu,
    int sisaWaktu,
    int opsi[],
    int pilihan
) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");

    GarisSoal(WARNA_SOAL);

    BarisSoal(
        "LEVEL " + AngkaKeString(level) + " : " + namaLevel,
        WARNA_SOAL
    );

    BarisSoal(
        "Waktu menjawab: " + AngkaKeString(batasWaktu) + " detik",
        WARNA_SOAL
    );

    GarisSoal(WARNA_SOAL);
    BarisSoal("", WARNA_SOAL);

    BarisSoal(
        "QUESTION " + AngkaKeString(level) + " : " + pertanyaan,
        WARNA_SOAL
    );

    BarisSoal("", WARNA_SOAL);

    // Opsi A
    BarisSoal(
        "A. " + AngkaKeString(opsi[0]),
        pilihan == 0 ? 14 : WARNA_SOAL
    );

    // Opsi B
    BarisSoal(
        "B. " + AngkaKeString(opsi[1]),
        pilihan == 1 ? 14 : WARNA_SOAL
    );

    // Opsi C
    BarisSoal(
        "C. " + AngkaKeString(opsi[2]),
        pilihan == 2 ? 14 : WARNA_SOAL
    );

    // Opsi D
    BarisSoal(
        "D. " + AngkaKeString(opsi[3]),
        pilihan == 3 ? 14 : WARNA_SOAL
    );

    BarisSoal("", WARNA_SOAL);

    BarisSoal(
        "SCORE : " + AngkaKeString(skor) +
        "                         TIME : " +
        AngkaKeString(sisaWaktu) + " SECONDS",
        sisaWaktu <= 3 ? WARNA_WAKTU : WARNA_SOAL
    );

    BarisSoal("", WARNA_SOAL);
    GarisSoal(WARNA_SOAL);

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\n";
    cout << "          UP / DOWN: SELECT ANSWER\n";
    cout << "                 ENTER: CONFIRM\n";
}


/* Memperbarui baris TIME saja tanpa menghapus layar. */
void PerbaruiWaktuPG(int skor, int sisaWaktu) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD posisi;
    posisi.X = 0;
    posisi.Y = 12; // Posisi baris SCORE dan TIME

    SetConsoleCursorPosition(hConsole, posisi);

    string teks =
        "SCORE : " + AngkaKeString(skor) +
        "                         TIME : " +
        AngkaKeString(sisaWaktu) + " SECONDS";

    int warna = (sisaWaktu <= 3)
                ? WARNA_WAKTU
                : WARNA_SOAL;

    BarisSoal(teks, warna);
}


/* Memperbarui empat opsi saja saat tombol panah ditekan. */
void PerbaruiPilihanPG(int opsi[], int pilihan) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 4; i++) {
        COORD posisi;
        posisi.X = 0;
        posisi.Y = (SHORT)(7 + i); // Baris opsi A sampai D

        SetConsoleCursorPosition(hConsole, posisi);

        string huruf;

        if (i == 0) {
            huruf = "A. ";
        } else if (i == 1) {
            huruf = "B. ";
        } else if (i == 2) {
            huruf = "C. ";
        } else {
            huruf = "D. ";
        }

        int warna = (i == pilihan)
                    ? 14
                    : WARNA_SOAL;

        BarisSoal(
            huruf + AngkaKeString(opsi[i]),
            warna
        );
    }
}


// Memilih jawaban dengan panah atas/bawah dan Enter.
// Mengembalikan false jika waktu habis.

bool PilihJawabanPG(
    int level,
    string namaLevel,
    string pertanyaan,
    int skor,
    int batasWaktu,
    int opsi[],
    int &indeksDipilih,
    int &sisaWaktuAkhir
) {
    int pilihan = 0;
    indeksDipilih = -1;
    sisaWaktuAkhir = batasWaktu;

    // Tampilkan seluruh layar satu kali saja.
    TampilkanLayarPG(
        level,
        namaLevel,
        pertanyaan,
        skor,
        batasWaktu,
        batasWaktu,
        opsi,
        pilihan
    );

    // Mulai menghitung waktu setelah layar tampil.
    DWORD mulai = GetTickCount();
    int sisaSebelumnya = batasWaktu;

    while (true) {
        DWORD berlalu = GetTickCount() - mulai;

        // Periksa apakah waktu sudah habis.
        if (berlalu >= (DWORD)(batasWaktu * 1000)) {
            sisaWaktuAkhir = 0;
            return false;
        }

        int sisaWaktu =
            batasWaktu - (int)(berlalu / 1000);

        // Perbarui hanya baris waktu ketika detik berubah.
        if (sisaWaktu != sisaSebelumnya) {
            sisaSebelumnya = sisaWaktu;

            PerbaruiWaktuPG(skor, sisaWaktu);
        }

        // Periksa tombol yang ditekan pemain.
        if (kbhit()) {
            char tombol = getch();

            // Tombol panah pada keyboard Windows.
            if (tombol == 0 || tombol == -32) {
                tombol = getch();

                if (tombol == 72) {
                    // Panah atas.
                    pilihan--;

                    if (pilihan < 0) {
                        pilihan = 3;
                    }

                    PerbaruiPilihanPG(opsi, pilihan);
                }
                else if (tombol == 80) {
                    // Panah bawah.
                    pilihan++;

                    if (pilihan > 3) {
                        pilihan = 0;
                    }

                    PerbaruiPilihanPG(opsi, pilihan);
                }
            }
            else if (tombol == 13) {
                // Periksa waktu kembali sebelum menerima jawaban.
                DWORD waktuSekarang = GetTickCount() - mulai;

                if (waktuSekarang >=
                    (DWORD)(batasWaktu * 1000)) {
                    sisaWaktuAkhir = 0;
                    return false;
                }

                indeksDipilih = pilihan;

                sisaWaktuAkhir =
                    batasWaktu - (int)(waktuSekarang / 1000);

                if (sisaWaktuAkhir < 0) {
                    sisaWaktuAkhir = 0;
                }

                return true;
            }
        }
    }
}



// Menampilkan hasil soal pilihan ganda.
void TampilkanHasilPG(
    int level,
    string namaLevel,
    string pertanyaan,
    int skor,
    int batasWaktu,
    int sisaWaktu,
    int opsi[],
    int indeksDipilih,
    int jawaban,
    int warna,
    string status
) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");

    GarisSoal(warna);

    BarisSoal(
        "LEVEL " + AngkaKeString(level) + " : " + namaLevel,
        warna
    );

    BarisSoal(
        "Waktu menjawab: " + AngkaKeString(batasWaktu) + " detik",
        warna
    );

    GarisSoal(warna);
    BarisSoal("", warna);

    BarisSoal(
        "QUESTION " + AngkaKeString(level) + " : " + pertanyaan,
        warna
    );

    BarisSoal("", warna);

    for (int i = 0; i < 4; i++) {
        string huruf;

        if (i == 0) huruf = "A. ";
        else if (i == 1) huruf = "B. ";
        else if (i == 2) huruf = "C. ";
        else huruf = "D. ";

        int warnaOpsi = warna;

        if (opsi[i] == jawaban) {
            warnaOpsi = WARNA_BENAR;
        }
        else if (i == indeksDipilih) {
            warnaOpsi = WARNA_SALAH;
        }

        BarisSoal(
            huruf + AngkaKeString(opsi[i]),
            warnaOpsi
        );
    }

    BarisSoal("", warna);

    BarisSoal(
        "SCORE : " + AngkaKeString(skor) +
        "                         TIME : " +
        AngkaKeString(sisaWaktu) + " SECONDS",
        warna
    );

    BarisSoal("", warna);
    GarisSoal(warna);
    BarisSoal("", warna);
    BarisSoal(status, warna);

    BarisSoal(
        "Correct Answer : " + AngkaKeString(jawaban),
        warna
    );

    BarisSoal("", warna);
    GarisSoal(warna);

    SetConsoleTextAttribute(hConsole, 11);
    cout << "\n";
    cout << "                 Press any key to continue . . .";
    getch();
}


// Menjalankan seluruh permainan pilihan ganda.
// Mengembalikan skor akhir untuk disimpan oleh main().

int JalankanPilihanGanda(string namaPemain) {
    srand((unsigned int)time(0));

    int skor = 0;
    bool gagal = false;

    const int JUMLAH_SOAL_PER_LEVEL = 5;

    for (int level = 1; level <= 5; level++) {
        string namaLevel;

        // Menentukan batas waktu berdasarkan level.
        int batasWaktu;

        if (level <= 2) {
            batasWaktu = 5;
        }
        else if (level <= 4) {
            batasWaktu = 8;
        }
        else {
            batasWaktu = 10;
        }

        // Beberapa soal pada setiap level.
        for (int nomorSoal = 1;
             nomorSoal <= JUMLAH_SOAL_PER_LEVEL;
             nomorSoal++) {

            string pertanyaan;
            int jawaban;

            // Membuat soal baru.
            BuatSoalPG(
                level,
                namaLevel,
                pertanyaan,
                jawaban
            );

            // Mengacak empat opsi jawaban.
            int opsi[4];
            BuatOpsiPG(jawaban, opsi);

            int indeksDipilih = -1;
            int sisaWaktuAkhir = batasWaktu;

            // Menampilkan soal dan menerima jawaban.
            bool jawabanMasuk = PilihJawabanPG(
                nomorSoal,
                namaLevel,
                pertanyaan,
                skor,
                batasWaktu,
                opsi,
                indeksDipilih,
                sisaWaktuAkhir
            );

            // Jika waktu habis.
            if (!jawabanMasuk) {
                TampilkanHasilPG(
                    nomorSoal,
                    namaLevel,
                    pertanyaan,
                    skor,
                    batasWaktu,
                    0,
                    opsi,
                    -1,
                    jawaban,
                    WARNA_WAKTU,
                    "TIME'S UP! Oh, no! (T_T)"
                );

                gagal = true;
                break;
            }

            // Jika jawaban benar.
            if (opsi[indeksDipilih] == jawaban) {
                skor += 10;

                TampilkanHasilPG(
                    nomorSoal,
                    namaLevel,
                    pertanyaan,
                    skor,
                    batasWaktu,
                    sisaWaktuAkhir,
                    opsi,
                    indeksDipilih,
                    jawaban,
                    WARNA_BENAR,
                    "GOOD! Jawaban kamu benar!"
                );

                Beep(1000, 150);
            }
            // Jika jawaban salah.
            else {
                TampilkanHasilPG(
                    nomorSoal,
                    namaLevel,
                    pertanyaan,
                    skor,
                    batasWaktu,
                    sisaWaktuAkhir,
                    opsi,
                    indeksDipilih,
                    jawaban,
                    WARNA_SALAH,
                    "ANSWER WRONG! Jawaban kamu salah!"
                );

                gagal = true;
                break;
            }
        }

        // Jika gagal, hentikan seluruh level.
        if (gagal) {
            break;
        }

        // Informasi setelah satu level selesai.
        if (level < 5) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            system("cls");
            SetConsoleTextAttribute(hConsole, WARNA_BENAR);

            cout << "\n";
            cout << "====================================================\n";
            cout << "                LEVEL COMPLETED!\n";
            cout << "====================================================\n\n";

            cout << " Level             : " << level << "\n";
            cout << " Correct Questions : "
                 << JUMLAH_SOAL_PER_LEVEL << "\n";
            cout << " Current Score     : " << skor << "\n\n";

            cout << "        GET READY FOR THE NEXT LEVEL!\n\n";
            cout << "====================================================\n";

            SetConsoleTextAttribute(hConsole, WARNA_PUTIH);
            system("pause");
        }
    }

    // Layar akhir permainan.
    if (gagal) {
        TampilkanGameOver(namaPemain, skor);
    }
    else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        system("cls");
        SetConsoleTextAttribute(hConsole, WARNA_BENAR);

        cout << "\n";
        cout << "====================================================\n";
        cout << "              CONGRATULATIONS!\n";
        cout << "====================================================\n\n";

        cout << "           YOU HAVE FINISHED THE GAME!\n\n";
        cout << "               Player : " << namaPemain << "\n";
        cout << "               Score  : " << skor << " / 250\n\n";

        cout << "          ALL 25 QUESTIONS COMPLETED!\n\n";
        cout << "====================================================\n";

        SetConsoleTextAttribute(hConsole, WARNA_PUTIH);
        system("pause");
    }

    return skor;
}



int JalankanSoalGabungan(string namaPemain) {
    srand((unsigned int)time(0));

    int skor = 0;
    int nomorGlobal = 0;
    bool gagal = false;

    const int JUMLAH_SOAL_PER_LEVEL = 5;

    for (int level = 1; level <= 5 && !gagal; level++) {
        string namaLevel;

        // Menentukan waktu berdasarkan level.
        int batasWaktu;

        if (level <= 2) {
            batasWaktu = 5;
        }
        else if (level <= 4) {
            batasWaktu = 8;
        }
        else {
            batasWaktu = 10;
        }

        for (int nomorSoal = 1;
             nomorSoal <= JUMLAH_SOAL_PER_LEVEL;
             nomorSoal++) {

            nomorGlobal++;

            string pertanyaan;
            int jawaban = 0;

            // Membuat soal sesuai level.
            BuatSoalPG(
                level,
                namaLevel,
                pertanyaan,
                jawaban
            );

            // Soal ganjil = isian.
            // Soal genap = pilihan ganda.
            bool modeIsian = (nomorGlobal % 2 == 1);

            if (modeIsian) {
                int jawabanPemain = 0;
                int sisaWaktuAkhir = batasWaktu;

                bool jawabanMasuk = SoalDenganHitungMundur(
                    level,
                    namaLevel,
                    nomorGlobal,
                    pertanyaan,
                    skor,
                    batasWaktu,
                    WARNA_SOAL,
                    jawabanPemain,
                    sisaWaktuAkhir
                );

                // Waktu habis.
                if (!jawabanMasuk) {
                    TampilkanSoal(
                        level,
                        namaLevel,
                        nomorGlobal,
                        pertanyaan,
                        skor,
                        batasWaktu,
                        WARNA_WAKTU,
                        "TIME'S UP! Waktu kamu habis!",
                        AngkaKeString(jawaban),
                        0
                    );

                    gagal = true;
                    break;
                }

                // Jawaban benar.
                if (jawabanPemain == jawaban) {
                    skor += 10;

                    TampilkanSoal(
                        level,
                        namaLevel,
                        nomorGlobal,
                        pertanyaan,
                        skor,
                        batasWaktu,
                        WARNA_BENAR,
                        "GOOD! Jawaban kamu benar!",
                        AngkaKeString(jawaban),
                        sisaWaktuAkhir
                    );

                    Beep(1000, 150);
                }
                // Jawaban salah.
                else {
                    TampilkanSoal(
                        level,
                        namaLevel,
                        nomorGlobal,
                        pertanyaan,
                        skor,
                        batasWaktu,
                        WARNA_SALAH,
                        "ANSWER WRONG! Jawaban kamu salah!",
                        AngkaKeString(jawaban),
                        sisaWaktuAkhir
                    );

                    gagal = true;
                    break;
                }
            }
            else {
                // MODE PILIHAN GANDA
                int opsi[4];
                BuatOpsiPG(jawaban, opsi);

                int indeksDipilih = -1;
                int sisaWaktuAkhir = batasWaktu;

                bool jawabanMasuk = PilihJawabanPG(
                    level,
                    namaLevel,
                    pertanyaan,
                    skor,
                    batasWaktu,
                    opsi,
                    indeksDipilih,
                    sisaWaktuAkhir
                );

                // Waktu habis.
                if (!jawabanMasuk) {
                    TampilkanHasilPG(
                        level,
                        namaLevel,
                        pertanyaan,
                        skor,
                        batasWaktu,
                        0,
                        opsi,
                        -1,
                        jawaban,
                        WARNA_WAKTU,
                        "TIME'S UP! Waktu kamu habis!"
                    );

                    gagal = true;
                    break;
                }

                // Jawaban benar.
                if (opsi[indeksDipilih] == jawaban) {
                    skor += 10;

                    TampilkanHasilPG(
                        level,
                        namaLevel,
                        pertanyaan,
                        skor,
                        batasWaktu,
                        sisaWaktuAkhir,
                        opsi,
                        indeksDipilih,
                        jawaban,
                        WARNA_BENAR,
                        "GOOD! Jawaban kamu benar!"
                    );

                    Beep(1000, 150);
                }
                // Jawaban salah.
                else {
                    TampilkanHasilPG(
                        level,
                        namaLevel,
                        pertanyaan,
                        skor,
                        batasWaktu,
                        sisaWaktuAkhir,
                        opsi,
                        indeksDipilih,
                        jawaban,
                        WARNA_SALAH,
                        "ANSWER WRONG! Jawaban kamu salah!"
                    );

                    gagal = true;
                    break;
                }
            }
        }

        // Jika gagal, hentikan permainan.
        if (gagal) {
            break;
        }

        // Informasi ketika satu level selesai.
        if (level < 5) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            system("cls");
            SetConsoleTextAttribute(hConsole, WARNA_BENAR);

            cout << "\n";
            cout << "====================================================\n";
            cout << "                LEVEL COMPLETED!\n";
            cout << "====================================================\n\n";

            cout << " Level             : " << level << "\n";
            cout << " Questions Done    : "
                 << JUMLAH_SOAL_PER_LEVEL << "\n";
            cout << " Current Score     : " << skor << "\n\n";

            cout << "        GET READY FOR THE NEXT LEVEL!\n\n";
            cout << "====================================================\n";

            SetConsoleTextAttribute(hConsole, WARNA_PUTIH);
            system("pause");
        }
    }

    // Tampilan akhir permainan.
    if (gagal) {
        TampilkanGameOver(namaPemain, skor);
    }
    else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        system("cls");
        SetConsoleTextAttribute(hConsole, WARNA_BENAR);

        cout << "\n";
        cout << "====================================================\n";
        cout << "              CONGRATULATIONS!\n";
        cout << "====================================================\n\n";

        cout << "       YOU HAVE FINISHED THE COMBINED GAME!\n\n";
        cout << "               Player : " << namaPemain << "\n";
        cout << "               Score  : " << skor << " / 250\n\n";

        cout << "          ALL 25 QUESTIONS COMPLETED!\n\n";
        cout << "====================================================\n";

        SetConsoleTextAttribute(hConsole, WARNA_PUTIH);
        system("pause");
    }

    return skor;
}


void TampilkanSambutan(string &nama, bool &namaSudahDiisi) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    SetConsoleTextAttribute(hConsole, 11);

    cout << "\n";
    cout << "====================================================\n";
    cout << "                   WELCOME TO\n";
    cout << "                MATH QUIZ GAME!\n";
    cout << "====================================================\n\n";

    if (!namaSudahDiisi) {
        SetConsoleTextAttribute(hConsole, 11);
        cout << "             PLEASE ENTER YOUR NAME : ";
        getline(cin >> ws, nama);

        namaSudahDiisi = true;
    } else {
        SetConsoleTextAttribute(hConsole, 11);
        cout << "             WELCOME BACK, " << nama << "!\n";
        Sleep(1000);
    }

    // Tulisan HALLO berukuran besar.
    const char* hallo[] = {
        "*   *   *****   *       *       *****",
        "*   *   *   *   *       *       *   *",
        "*****   *****   *       *       *   *",
        "*   *   *   *   *       *       *   *",
        "*   *   *   *   *****   *****   *****"
    };

    // Warna animasi.
    int warna[] = {11, 12, 13, 14, 8};

    for (int detik = 0; detik < 5; detik++) {
        system("cls");

        SetConsoleTextAttribute(hConsole, warna[detik]);

        cout << "\n\n";
        cout << "        =====================================\n";
        cout << "        ";

        for (int i = 0; i < 5; i++) {
            cout << hallo[i] << "\n        ";
        }

        cout << "\n";

        SetConsoleTextAttribute(hConsole, 11);
        cout << "                    " << nama << "\n";

        SetConsoleTextAttribute(hConsole, warna[detik]);
        cout << "\n             *** GET READY TO PLAY! ***\n";
        cout << "        =====================================\n";

        Sleep(700);
        system("cls");
        Sleep(300);
    }

    // Kembalikan warna konsol.
    SetConsoleTextAttribute(hConsole, 7);
    system("cls");
}


int main() 
	{ 
		system("color f5"); 
		int COne, CTwo; 
		Game a;
		bool namaSudahDiisi = false;
		// Meminta input dari user hingga user memilih opsi "QUIT"
		while (true) { 
			login: COne = *MenuPilihan();
	    	switch (COne) {// Mengolah pilihan user
	        	case 1: { // pilihan pertama
	        		pilih_mode:
					int mode = MenuModeGame();
			        // Kembali ke menu utama
			        if (mode == 0) {
			            break;
			        }
			
			        // Mode pilihan ganda masih dalam pengembangan
			        if (mode == 2) {
					    // Meminta nama pemain jika belum diisi.
					    TampilkanSambutan(a.pemain, namaSudahDiisi);
					
					    // Jalankan permainan pilihan ganda.
					    a.score = JalankanPilihanGanda(a.pemain);
					
					    // Simpan skor menggunakan leaderboard yang sudah ada.
					    SimpanSkor(a.pemain, a.score);
					
					    // Tampilkan leaderboard.
					    TampilkanLeaderboard();
					    system("pause");
					
					    // Pilihan setelah permainan selesai.
					    while (true) {
					        CTwo = *GetChoice();
					
					        switch (CTwo) {
					            case 1:
					                // Memilih mode permainan kembali.
					                goto pilih_mode;
					
					            case 2:
					                // Kembali ke menu utama.
					                goto login;
					        }
					    }
					}
			
			        // Mode soal gabungan masih dalam pengembangan
					if (mode == 3) {
					    // Meminta nama jika belum diisi.
					    TampilkanSambutan(a.pemain, namaSudahDiisi);
					
					    // Jalankan permainan Soal Gabungan.
					    a.score = JalankanSoalGabungan(a.pemain);
					
					    // Simpan skor ke leaderboard.
					    SimpanSkor(a.pemain, a.score);
					
					    // Tampilkan leaderboard.
					    TampilkanLeaderboard();
					    system("pause");
					
					    // Pilihan setelah permainan selesai.
					    while (true) {
					        CTwo = *GetChoice();
					
					        switch (CTwo) {
					            case 1:
					                // Main kembali dan pilih mode.
					                goto pilih_mode;
					
					            case 2:
					                // Kembali ke menu utama.
					                goto login;
					        }
					    }
					}

			
			        // Mode 1: jalankan game lama
			        start:
	        		while (true) {  
							
						TampilkanSambutan(a.pemain, namaSudahDiisi);
						
						/* Level 1 */
						a.kondisi = 0;
						a.score = 0;
						
						srand((unsigned int)time(0));
						
						for (int i = 1; i <= 5; i++) {
						    int A = rand() % 10 + 1 + 10 * (i - 1);
						    int B = rand() % 10 + 1 + 10 * (i - 1);
						    int jawaban = A + B;
						    int numInput = 0;
						    int sisaWaktuAkhir = 0;
						
						    // Tampilkan soal awal dengan warna biru
							
							bool jawabanMasuk = SoalDenganHitungMundur(
							    1,
							    "ADDING QUIZ",
							    i,
							    AngkaKeString(A) + " + " + AngkaKeString(B) + " = ?",
							    a.score,
							    5,
							    WARNA_SOAL,
							    numInput,
							    sisaWaktuAkhir
							);
							
							bool waktuHabis = !jawabanMasuk;

						    // Kondisi 1: Waktu habis
						    if (waktuHabis) {
						        a.kondisi = 2;
						
						        TampilkanSoal(
						            1, "ADDING QUIZ", i,
						            AngkaKeString(A) + " + " + AngkaKeString(B) + " = ?",
						            a.score, 5, WARNA_WAKTU,
						            "TIME'S UP!  Oh, no! (T_T)",
						            AngkaKeString(jawaban), 0
						        );
						
						        break;
						    }
						
						    // Kondisi 2: Jawaban benar
						    if (numInput == jawaban) {
						        a.score += 10;
						
						        TampilkanSoal(
						            1, "ADDING QUIZ", i,
						            AngkaKeString(A) + " + " + AngkaKeString(B) +
						                " = " + AngkaKeString(numInput),
						            a.score, 5, WARNA_BENAR,
						            "GOOD!  Jawaban kamu benar!", "", sisaWaktuAkhir
						        );
						
						        Beep(1000, 150);
						    }
						    // Kondisi 3: Jawaban salah
						    else {
						        a.kondisi = 2;
						
						        TampilkanSoal(
						            1, "ADDING QUIZ", i,
						            AngkaKeString(A) + " + " + AngkaKeString(B) +
						                " = " + AngkaKeString(numInput),
						            a.score, 5, WARNA_SALAH,
						            "ANSWER WRONG!  Jawaban kamu salah!",
						            AngkaKeString(jawaban),sisaWaktuAkhir
						        );
						
						        break;
						    }
						}
		

						/* Level 2 : Subtracting Quiz */
						for (int Y = 1; a.kondisi != 2 && Y != 2; Y++) {
						
						    Beep(0, 2000);
						
						    for (int i = 1; i <= 1; i++) {
						
						        int A, B;
						        int H = rand() % 100 + 1;
						        int K = rand() % 100 + 1;
						
						        // Pastikan hasil pengurangan tidak negatif
						        if (H >= K) {
						            A = H;
						            B = K;
						        } else {
						            A = K;
						            B = H;
						        }
						
						        int jawaban = A - B;
						        int numInput = 0;
						        int sisaWaktuAkhir = 0;
						
						        // Tampilkan soal dengan bingkai biru
								
								bool jawabanMasuk = SoalDenganHitungMundur(
								    2,
								    "SUBTRACTING QUIZ",
								    i,
								    AngkaKeString(A) + " - " + AngkaKeString(B) + " = ?",
								    a.score,
								    5,
								    WARNA_SOAL,
								    numInput,
								    sisaWaktuAkhir
								);
								
								bool waktuHabis = !jawabanMasuk;

						
						        // Jika waktu habis
						        if (waktuHabis) {
						            a.kondisi = 2;
						
						            TampilkanSoal(
						                2,
						                "SUBTRACTING QUIZ",
						                i,
						                AngkaKeString(A) + " - " + AngkaKeString(B) + " = ?",
						                a.score,
						                5,
						                WARNA_WAKTU,
						                "TIME'S UP!  Oh, no! (T_T)",
						                AngkaKeString(jawaban), 0
						            );
						
						            break;
						        }
						
						        // Jika jawaban benar
						        if (numInput == jawaban) {
						            a.score += 10;
						
						            TampilkanSoal(
						                2,
						                "SUBTRACTING QUIZ",
						                i,
						                AngkaKeString(A) + " - " + AngkaKeString(B) +
						                    " = " + AngkaKeString(numInput),
						                a.score,
						                5,
						                WARNA_BENAR,
						                "GOOD!  Jawaban kamu benar!", "", sisaWaktuAkhir
						            );
						
						            Beep(1000, 150);
						        }
						
						        // Jika jawaban salah
						        else {
						            a.kondisi = 2;
						
						            TampilkanSoal(
						                2,
						                "SUBTRACTING QUIZ",
						                i,
						                AngkaKeString(A) + " - " + AngkaKeString(B) +
						                    " = " + AngkaKeString(numInput),
						                a.score,
						                5,
						                WARNA_SALAH,
						                "ANSWER WRONG!  Jawaban kamu salah!",
						                AngkaKeString(jawaban), sisaWaktuAkhir
						            );
						
						            break;
						        }
						    }
						}

	    
						
						/* Level 3 : Division Quiz */
						for (int Y = 1; a.kondisi != 2 && Y != 2; Y++) {
						
						    Beep(0, 4000);
						
						    for (int i = 1; i <= 1; i++) {
						
						        int A = rand() % (8 * i) + 1;
						        int B = rand() % (8 * i) + 1;
						
						        // Pastikan hasil pembagian berupa bilangan bulat
						        // dan tidak menghasilkan pembagian dengan nol.
						        A = A * B;
						
						        int jawaban = A / B;
						        int numInput = 0;
						        int sisaWaktuAkhir = 0;
						
						        // Tampilkan soal dengan bingkai biru
						        bool jawabanMasuk = SoalDenganHitungMundur(
								    3,
								    "DIVISION QUIZ",
								    i,
								    AngkaKeString(A) + " / " + AngkaKeString(B) + " = ?",
								    a.score,
								    8,
								    WARNA_SOAL,
								    numInput,
								    sisaWaktuAkhir
								);
								
								bool waktuHabis = !jawabanMasuk;
						
						        // Jika waktu habis
						        if (waktuHabis) {
						            a.kondisi = 2;
						
						            TampilkanSoal(
						                3,
						                "DIVISION QUIZ",
						                i,
						                AngkaKeString(A) + " / " + AngkaKeString(B) + " = ?",
						                a.score,
						                8,
						                WARNA_WAKTU,
						                "TIME'S UP!  Oh, no! (T_T)",
						                AngkaKeString(jawaban), 0
						            );
						
						            break;
						        }
						
						        // Jika jawaban benar
						        if (numInput == jawaban) {
						            a.score += 10;
						
						            TampilkanSoal(
						                3,
						                "DIVISION QUIZ",
						                i,
						                AngkaKeString(A) + " / " + AngkaKeString(B) +
						                    " = " + AngkaKeString(numInput),
						                a.score,
						                8,
						                WARNA_BENAR,
						                "GOOD!  Jawaban kamu benar!", "", sisaWaktuAkhir
						            );
						
						            Beep(1000, 150);
						        }
						
						        // Jika jawaban salah
						        else {
						            a.kondisi = 2;
						
						            TampilkanSoal(
						                3,
						                "DIVISION QUIZ",
						                i,
						                AngkaKeString(A) + " / " + AngkaKeString(B) +
						                    " = " + AngkaKeString(numInput),
						                a.score,
						                8,
						                WARNA_SALAH,
						                "ANSWER WRONG!  Jawaban kamu salah!",
						                AngkaKeString(jawaban), sisaWaktuAkhir
						            );
						
						            break;
						        }
						    }
						}

						
						/* Level 4 : Multiplication Quiz */
						for (int Y = 1; a.kondisi != 2 && Y != 2; Y++) {
						
						    Beep(0, 4000);
						
						    for (int i = 1; i <= 1; i++) {
						
						        int A = rand() % (8 * i) + 1;
						        int B = rand() % (8 * i) + 1;
						        int jawaban = A * B;
						        int numInput = 0;
						        int sisaWaktuAkhir = 0;
						
						        // Tampilkan soal dengan bingkai biru
						        bool jawabanMasuk = SoalDenganHitungMundur(
								    4,
								    "MULTIPLICATION QUIZ",
								    i,
								    AngkaKeString(A) + " x " + AngkaKeString(B) + " = ?",
								    a.score,
								    8,
								    WARNA_SOAL,
								    numInput,
								    sisaWaktuAkhir
								);
								
								bool waktuHabis = !jawabanMasuk;
						
						        // Jika waktu habis
						        if (waktuHabis) {
						            a.kondisi = 2;
						
						            TampilkanSoal(
						                4,
						                "MULTIPLICATION QUIZ",
						                i,
						                AngkaKeString(A) + " x " + AngkaKeString(B) + " = ?",
						                a.score,
						                8,
						                WARNA_WAKTU,
						                "TIME'S UP!  Oh, no! (T_T)",
						                AngkaKeString(jawaban), 0
						            );
						
						            break;
						        }
						
						        // Jika jawaban benar
						        if (numInput == jawaban) {
						            a.score += 10;
						
						            TampilkanSoal(
						                4,
						                "MULTIPLICATION QUIZ",
						                i,
						                AngkaKeString(A) + " x " + AngkaKeString(B) +
						                    " = " + AngkaKeString(numInput),
						                a.score,
						                8,
						                WARNA_BENAR,
						                "GOOD!  Jawaban kamu benar!", "", sisaWaktuAkhir
						            );
						
						            Beep(1000, 150);
						        }
						
						        // Jika jawaban salah
						        else {
						            a.kondisi = 2;
						
						            TampilkanSoal(
						                4,
						                "MULTIPLICATION QUIZ",
						                i,
						                AngkaKeString(A) + " x " + AngkaKeString(B) +
						                    " = " + AngkaKeString(numInput),
						                a.score,
						                8,
						                WARNA_SALAH,
						                "ANSWER WRONG!  Jawaban kamu salah!",
						                AngkaKeString(jawaban), sisaWaktuAkhir
						            );
						
						            break;
						        }
						    }
						}

	
						
						/* Level 5 : Final Quiz */
						for (int Y = 1; a.kondisi != 2 && Y != 2; Y++) {
						
						    Beep(0, 4000);
						
						    srand((unsigned int)time(0));
						
						    int A = rand() % 10 + 6;
						    int B = rand() % 10 + 6;
						    int C = rand() % 10 + 6;
						    int D = rand() % 10 + 6;
						
						    // Mengikuti urutan operasi pada soal asli:
						    // D + C * A / B
						    int X = C * A;
						    int slc = X / B;
						    int jawaban = D + slc;
						    int numInput = 0;
						    int sisaWaktuAkhir = 0;
						
						    // Tampilkan soal final dengan bingkai biru
						    bool jawabanMasuk = SoalDenganHitungMundur(
							    5,
							    "FINAL QUIZ",
							    1,
							    AngkaKeString(D) + " + " + AngkaKeString(C) +
							        " x " + AngkaKeString(A) + " / " +
							        AngkaKeString(B) + " = ?",
							    a.score,
							    10,
							    WARNA_SOAL,
							    numInput,
								sisaWaktuAkhir
							);
							
							bool waktuHabis = !jawabanMasuk;
						
						    // Jika waktu habis
						    if (waktuHabis) {
						        a.kondisi = 2;
						
						        TampilkanSoal(
						            5,
						            "FINAL QUIZ",
						            1,
						            AngkaKeString(D) + " + " + AngkaKeString(C) +
						                " x " + AngkaKeString(A) + " / " +
						                AngkaKeString(B) + " = ?",
						            a.score,
						            10,
						            WARNA_WAKTU,
						            "TIME'S UP!  Oh, no! (T_T)",
						            AngkaKeString(jawaban), 0
						        );
						
						        break;
						    }
						
						    // Jika jawaban benar
						    if (numInput == jawaban) {
						        a.score += 10;
						
						        TampilkanSoal(
						            5,
						            "FINAL QUIZ",
						            1,
						            AngkaKeString(D) + " + " + AngkaKeString(C) +
						                " x " + AngkaKeString(A) + " / " +
						                AngkaKeString(B) + " = " + AngkaKeString(numInput),
						            a.score,
						            0,
						            WARNA_BENAR,
						            "GOOD!  Jawaban kamu benar!", "", sisaWaktuAkhir
						        );
						
						        Beep(1000, 150);
						
						        // Layar kemenangan setelah jawaban benar
						        system("cls");
						
						        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						        SetConsoleTextAttribute(hConsole, WARNA_BENAR);
						
						        cout << "\n";
						        cout << "====================================================\n";
						        cout << "              CONGRATULATIONS!\n";
						        cout << "====================================================\n\n";
						        cout << "           YOU HAVE FINISHED THE GAME!\n\n";
						        cout << "               Player : " << a.pemain << "\n";
						        cout << "               Score  : " << a.score << "\n\n";
						        cout << "====================================================\n";
						
						        SetConsoleTextAttribute(hConsole, WARNA_PUTIH);
						        system("pause");
						    }
						
						    // Jika jawaban salah
						    else {
						        a.kondisi = 2;
						
						        TampilkanSoal(
						            5,
						            "FINAL QUIZ",
						            1,
						            AngkaKeString(D) + " + " + AngkaKeString(C) +
						                " x " + AngkaKeString(A) + " / " +
						                AngkaKeString(B) + " = " + AngkaKeString(numInput),
						            a.score,
						            10,
						            WARNA_SALAH,
						            "ANSWER WRONG!  Jawaban kamu salah!",
						            AngkaKeString(jawaban), sisaWaktuAkhir
						        );
						
						        break;
						    }
						}

		
						
						/* Game Over */
						
						if (a.kondisi == 2) {
						    TampilkanGameOver(a.pemain, a.score);
						} system("pause");

	
						/* Simpan dan tampilkan leaderboard */

						SimpanSkor(a.pemain, a.score);
						
						TampilkanLeaderboard();
						
						system("pause");
						
						while (true) {
						    CTwo = *GetChoice();
						
						    switch (CTwo) {
						        case 1:
						            goto pilih_mode;
						
						        case 2:
						            goto login;
						    }
						}
					} system ("pause");
					
					break;
				}
		        case 2: {
				    TampilkanLeaderboard();
				    system("pause");
				    break;
				}
		        case 3: {
				    system("cls");
				
				    cout << "========================================================\n";
				    cout << "                         HELP\n";
				    cout << "========================================================\n\n";
				
				    cout << "1. Pilih START GAME untuk memulai permainan.\n";
				    cout << "2. Masukkan nama saat pertama kali bermain.\n";
				    cout << "3. Jawab setiap soal sebelum batas waktu berakhir.\n";
				    cout << "4. Jawaban benar memberikan 10 poin.\n";
				    cout << "5. LEADERBOARD menampilkan tiga skor terbaik.\n";
				    cout << "6. Pilih QUIT untuk keluar dari permainan.\n\n";
				
				    cout << "                 HAVE FUN AND GOOD LUCK!\n\n";
				
				    system("pause");
				    break;
				}
				case 4: {
				    system("cls");
				
				    cout << "========================================================\n";
				    cout << "           ARE YOU SURE YOU WANT TO QUIT? (Y/N)\n";
				    cout << "========================================================\n";
				    cout << "Pilihan: ";
				
				    cin >> a.ulangi;
				
				    if (a.ulangi == 'Y' || a.ulangi == 'y') {
				        return 0;
				    }
				
				    break;
				}
			} 
		} 
	}
