#include <iostream>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;
unsigned short i;



fstream file_in("randomStreamList.txt");
ofstream file_out("littleEndianList.txt");
ofstream file_out2("middleBits.txt");

void makeStartList(){
    int numberOfEntries;
    cout << "Welcome to Endian-school assignment \n" << endl;
    cout << "Enter the number of entries you would like to have in your dataset (int): " << endl;
    cin >> numberOfEntries;
    cout << "You've choosen: " << numberOfEntries <<" "<< "entries. " << endl;
    cout << "Processing data ... " << endl;
    cout << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    ofstream Myfile("randomStreamList.txt");
    unsigned short min = 1;
    unsigned short max = 65535;
    srand(time(NULL));
    while(i++ < numberOfEntries ){
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

                cout    << "Decimal Value: " << setw(28) << value <<"\n"
                        << "Binary: " << setw(46) << binary_string16bits(stoi(value, nullptr,10)) << "\n"
                        << "Big Endian: " << setw(32) << to_hex(stoi(value, nullptr,10)) << "\n"
                        << "Little Endian: " << setw(29) << c << "\n"
                        << "Middle 8 bits: " << setw(31)  << binary_string8bits(cc) << "\n"
                        << "Size of 'middle 8 bits': " << setw(14) << sizeof (cc) << " byte(s)" << "\n"
                        << "Data Type: " << setw(40) << typeid(cc).name() << "\n"
                        << "\n" << setw(25) << "----------" << "\n" << endl;


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

