#include <iostream>
#include <bitset>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip> 
using namespace std;

int main(){
//1 задание
	uint64_t a = 0b0000000100100011010001010110011110001001101010111100110111101111;
	cout << "a   " << setw(16) << setfill('0') << hex << a<< endl;
	char S[16] = {0x0C, 0x08, 0x02, 0x01, 0x0D, 0x04, 0x0F, 0x06,
	              0x07, 0x00, 0x0A, 0x05, 0x03, 0x0E, 0x09, 0x0B};
	uint64_t y = 0;
	//cout << bitset<4>(S[7]) << endl;
	
	for(int i = 0; i < 16; i++){
		uint x = (a >> (i*4)) & 0xF; //по 4 с младшего разряда
		//cout << bitset<4>(x) << endl;
		y = y|(uint64_t(S[x]) << (i*4));
	}	
	cout <<"y   " << y << endl;
	
//2 задание
	uint8_t S_u[256]; // так как 2^8 = 256
	for (int j = 0; j < 256; j++){
		uint8_t x1 = (j >> 4) & 0xF; // Старшие 4 бита
        uint8_t x2 = j & 0xF;        // Младшие 4 бита
        S_u[j] = (S[x1] << 4) | S[x2]; // Объединяем
        //cout << j << " " << bitset<8>(S_u[j]) << endl;
	}
	
	uint64_t y_u = 0;
	for(int i = 0; i < 8; i++){
		uint x = (a >> (i*8)) & 0xFF; //по 8 с младшего разряда
		//cout << bitset<8>(x) << endl;
		y_u = y_u|(uint64_t(S_u[x]) << (i*8));
	}	
	cout << "y_2 " << y_u << endl;
	
// 3 задание
	int p = 3;
	uint64_t y_s = 0;
	for(int h = 0; h < 8; h++){
		uint8_t x = (a >> (h*8)) & 0xFF; //по 8 с младшего разряда
		uint8_t stan = (x >> p)|(x << (8 - p));
		y_s = y_s|(uint64_t(stan) << (h*8));
	}
	cout << "y_3 " << y_s << endl;
	
//4 задание
	uint64_t y_k = 0;
	for(int k = 0; k < 8; k++){
		uint8_t x = (a >>(k*8)) & 0xFF;
		uint x1 = (x >> 4) & 0xF;
		uint x2 = x & 0xF;
		//cout << bitset<8>(x) << " " << bitset<4>(x1) << " " << bitset<4>(x2) << endl;
		uint8_t  a1 = (uint64_t(S[x1]) << 4)|uint64_t(S[x2]);
		//cout << bitset<8>(a1) << endl;
		uint8_t b = (a1 >> p)|(a1 << (8 - p));
		//cout << "s "<< bitset<8>(stan) << endl;
		y_k = y_k|(uint64_t(b) << (k*8));
	}
	cout << "y_4 " << y_k << endl;
	
//5 задание
	ifstream in("text.txt", ios::binary);
	in.seekg(0, ios::end);
    uint size = in.tellg(); 
    in.seekg(0, ios::beg);
	vector<uint8_t> data(size);
    in.read(reinterpret_cast<char*>(data.data()), size);
    in.close();
    
   cout << "Текст до: " << endl;
    for (uint8_t byte : data) {
        cout << bitset<8>(byte) << " ";
    }
     cout << endl;
    
	vector<uint8_t> result(size); // Вектор для хранения результата
	
	for(size_t i = 0; i < size; i++){
		uint8_t x = uint8_t(data[i]);
		uint x1 = (x >> 4) & 0xF;
		uint x2 = x & 0xF;
		
		uint8_t a1 = (S[x1] << 4) | S[x2];
		uint8_t b = (a1 >> p) | (a1 << (8 - p));
		result[i] = b;
	}
	
	cout << "Текст после 5: " << endl;
	for (uint8_t byte : result) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;
    
// 6 задание
	uint64_t y_f = 0;
	// Создание эквивалентной подстановки S'
    uint8_t S_prime[256];
    for (int x = 0; x < 256; x++) {
        S_prime[x] = (S_u[x] >> p) | (S_u[x] << (8 - p)); // Циклический сдвиг вправо на p бит
        //cout << x << " " << bitset<8>(S_prime[x]) << endl;
    }
    
	for(int h = 0; h < 8; h++){
		uint8_t x = (a >> (h*8)) & 0xFF; //по 8 с младшего разряда
		y_f = y_f|(uint64_t(S_prime[x]) << (h*8));
	}
	cout << "y_6 " << y_f << endl;
    
    
	
//7 задание
		vector<uint8_t> result1(size); // Вектор для хранения результата
	     
	for(size_t i = 0; i < size; i++){
		uint8_t x = uint8_t(data[i]);
		result1[i] = S_prime[x];
	}
	cout << "Текст после 7: " << endl;
	for (uint8_t byte : result1) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;
	
	
}

