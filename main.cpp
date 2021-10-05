#include <iostream>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>

using namespace std;
unsigned short i;

fstream file_in("randomStreamList.txt");
ofstream file_out("littleEndianList.txt");
ofstream file_out2("middleBits.txt");

void makeStartList(){
    ofstream Myfile("randomStreamList.txt");
    unsigned short min = 1;
    unsigned short max = 65535;
    srand(time(NULL));
    while(i++ < 100){ ///Antal valda entries.
        unsigned short value = min + (rand() % static_cast<unsigned short>(max - min + 1));
        Myfile << value << "\n";
    }
    Myfile.close();
}

string binary_string16bits(unsigned short n){
    bitset<16> bs(n);
    return bs.to_string();
}

string binary_string8bits(unsigned char n){
    bitset<8> bs(n);
    return bs.to_string();
}

string to_hex(unsigned short val, size_t width=sizeof(unsigned short)*2)
{
    std::stringstream ss;
    ss << "0x" << setfill('0') << setw(width) << hex << (val);
    return ss.str();
}

unsigned short swap_uint16(unsigned short val )
{
    return (val << 8) | (val >> 8 );
}

unsigned char extractToChar(unsigned short value, int begin, int end){
    unsigned short mask = (1 << (end - begin)) - 1;
    return (value >> begin) & mask;
}


int main() {
    makeStartList();

    if (file_in.is_open()) {
        string value;
        while (!file_in.eof()) {
            getline(file_in, value);
            if (!file_in.eof()) {

                binary_string16bits(stoi(value, nullptr,10));
                to_hex((stoi(value, nullptr,10)));
                auto temp = swap_uint16(stoi(value, nullptr,10));
                auto c = to_hex(temp);
                binary_string16bits(temp);
                unsigned char cc = extractToChar(temp,4,12);

                cout << "Decimal Value: " << value << " | " << "Binary: " << binary_string16bits(stoi(value, nullptr,10))
                << " | " << "Big Endian: " << to_hex(stoi(value, nullptr,10))<< " | "<< "Little Endian: " << c
                << " | " <<"Middle 8 bits: " << binary_string8bits(cc) << " --> "  << "Size: "<<sizeof (cc) << " | " << "Data Type: "
                << typeid(cc).name() << "\n" << "-------" << "\n" << endl;


                file_out << c << "\n";
                file_out2 << binary_string8bits(cc)<< "\n";
            } else {
                cout << "\n" <<"-x- Program successfully ended -x-" << endl;
            }
        }
        file_in.close();
        file_out.close();
        file_out2.close();
    }
    return 0;
}

