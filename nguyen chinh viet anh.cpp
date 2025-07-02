#include <iostream>
#include <string>
#include <iomanip>
#include <cstdint>

using namespace std;

// Mã hóa XOR mô ph?ng TripleDES
void maHoa3DES(const string& banRo, const string& khoa, string& banMa) {
    banMa.clear();
    if (khoa.empty()) {
        cerr << "L?i: Khóa r?ng!\n";
        return;
    }

    for (size_t i = 0; i < banRo.size(); ++i) {
        char k = khoa[i % khoa.size()];
        banMa += banRo[i] ^ k ^ 0x5A;
    }
}

// Gi?i mã
void giaiMa3DES(const string& banMa, const string& khoa, string& banRo) {
    banRo.clear();
    if (khoa.empty()) {
        cerr << "L?i: Khóa r?ng!\n";
        return;
    }

    for (size_t i = 0; i < banMa.size(); ++i) {
        char k = khoa[i % khoa.size()];
        banRo += banMa[i] ^ k ^ 0x5A;
    }
}

// Hàm bam mô ph?ng don gi?n
unsigned int bamGiaLap(const string& duLieu) {
    const uint64_t P = 31;
    const uint64_t MOD = 1000000007;
    uint64_t bam = 0;

    for (char c : duLieu) {
        bam = (bam * P + static_cast<unsigned char>(c)) % MOD;
    }

    return static_cast<unsigned int>(bam);
}

// Ký d? li?u
unsigned int kyGiaLap(const string& duLieu, const string& khoaRieng) {
    return bamGiaLap(duLieu + khoaRieng);
}

// Xác th?c ch? ký
bool xacThucChuKy(const string& duLieu, unsigned int chuKy, const string& khoaCongKhai) {
    return chuKy == bamGiaLap(duLieu + khoaCongKhai);
}

// In d? li?u ? d?ng hex
void inHex(const string& duLieu) {
    for (unsigned char c : duLieu) {
        cout << hex << setw(2) << setfill('0') << (int)c << " ";
    }
    cout << dec << endl;
}

// Chuong trình chính
int main() {
    string tinNhan;
    cout << "Nh?p tin nh?n: ";
    getline(cin, tinNhan);

    string khoa3DES = "123456789012345678901234";  // 24 ký t?
    string khoaRieng = "khoa_rieng_gia";
    string khoaCongKhai = "khoa_rieng_gia"; // Gi? l?p: dùng cùng giá tr?

    string banMa, banRo;

    // Mã hóa
    maHoa3DES(tinNhan, khoa3DES, banMa);
    cout << "B?n mã (hex): ";
    inHex(banMa);

    // Ký ch? ký
    unsigned int chuKy = kyGiaLap(banMa, khoaRieng);
    cout << "Ðã ký ch? ký.\n";

    // Xác th?c ch? ký
    if (xacThucChuKy(banMa, chuKy, khoaCongKhai)) {
        cout << "Xác th?c ch? ký: H?p l? ?\n";

        // Gi?i mã n?u h?p l?
        giaiMa3DES(banMa, khoa3DES, banRo);
        cout << "Tin nh?n sau gi?i mã: " << banRo << endl;
    } else {
        cout << "Xác th?c ch? ký: Không h?p l? ?\n";
    }

    return 0;
}
