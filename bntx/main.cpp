#include <iostream>
#include <fstream>
#include <iomanip>
#include "../utils/utils.h"

#define bntx 1112429656
#define nx 1314398240
#define str 1599296594
#define brti 1112691785
#define brtd 1111691780
#define rlt 1599299012
#define dic 1598310723

using namespace std;

int read_bntx(string file_path_in) {

    // Create file stream for compressed data
    ifstream input_stream(file_path_in, ios::in | ios::ate | ios::binary);

    // If the file stream isnt open
    if(!input_stream.is_open()) {
        cerr << "[!] Error reading from file: " << file_path_in << endl;
        return 1;
    }

    // Get file size and allocate memory for contents
    unsigned int bntx_data_size = input_stream.tellg();
    unsigned int bntx_header_size = 0x20;
    unsigned int nx_header_size = 0x38;
    bntx_data_size -= bntx_header_size;
    bntx_data_size -= nx_header_size;

    // Allocate array in memory for file contents
    char *bntx_data = new char[bntx_data_size];
    char *nx_header = new char[nx_header_size];
    char *bntx_header = new char[bntx_header_size];

    // Go back to begining of file
    input_stream.seekg(0, ios::beg);

    // Read contents of file into memory
    input_stream.read(bntx_header, bntx_header_size);
    input_stream.read(nx_header, nx_header_size);
    input_stream.read(bntx_data, bntx_data_size);

    // Close file stream
    input_stream.close();

    cout << file_path_in << endl;

    unsigned int bntx_magic_number = be_cast_int(bntx_header, 0x0);

    if(bntx_magic_number != bntx) {
        cerr << "[!] Error not a bntx file! " << file_path_in << endl;

        delete[] bntx_data;
        delete[] bntx_header;
        delete[] nx_header;

        bntx_data = nullptr;
        bntx_header = nullptr;
        nx_header = nullptr;

        return 1;
    }

    unsigned int nx_magic_number = be_cast_int(nx_header, 0x0);

    if(nx_magic_number != nx) {
        cerr << "[!] Error doesnt contain a nx texture container! " << file_path_in << endl;

        delete[] bntx_data;
        delete[] bntx_header;
        delete[] nx_header;

        bntx_data = nullptr;
        bntx_header = nullptr;
        nx_header = nullptr;

        return 1;
    }

    int texture_count = le_cast_int(nx_header, 0x4);
    long texture_info_array = le_cast_long(nx_header, 0x8);
    long texture_data_region = le_cast_long(nx_header, 0x10);
    long texture_info_dictionary = le_cast_long(nx_header, 0x18);

    cout << "Texture count in file: " << texture_count << endl;
    cout << "Texture info array: 0x" << hex << texture_info_array << dec << endl;
    cout << "Texture data region: 0x" << hex << texture_data_region << dec << endl;
    cout << "Texture info dic: 0x" << hex << texture_info_dictionary << dec << endl;
    cout << endl;

    delete[] bntx_data;
    delete[] bntx_header;
    delete[] nx_header;

    bntx_data = nullptr;
    bntx_header = nullptr;
    nx_header = nullptr;

    return 0;
}

int main() {

    /*
    read_bntx("systemDataUnpacked/common/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Entrance/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Eula/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Flaunch/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Gift/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Interrupt/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Migration/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/MyPage/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Notification/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Option/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Psl/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/ResidentMenu/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/SaveMove/timg/__Combined.bntx");
    read_bntx("systemDataUnpacked/Set/timg/__Combined.bntx");
    */

    read_bntx("systemDataUnpacked/Eula/timg/__Combined.bntx");

    return 0;
}