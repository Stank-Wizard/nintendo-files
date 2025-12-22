#include <iostream>
#include <fstream>
#include <iomanip>
#include "../utils/utils.hpp"

#define BNTX 1112429656
#define NX 1314398240
#define STR 1599296594
#define BRTI 1112691785
#define BRTD 1111691780
#define RLT 1599299012
#define DIC 1598310723

using namespace std;

int print_bntx_header(char* src_buffer, int bntx_offset) {

    // Extract important data from headers
    long version = le_cast_long(src_buffer, bntx_offset + 0x4);
    short byte_order_mark = le_cast_short(src_buffer, bntx_offset + 0xC);
    short alignment_exponent = le_cast_short(src_buffer, bntx_offset + 0xE);
    int file_name_offset = le_cast_int(src_buffer, bntx_offset + 0x10);
    short is_relocated = le_cast_short(src_buffer, bntx_offset + 0x14);
    short str_table_offset = le_cast_short(src_buffer, bntx_offset + 0x16);
    int rlt_table_offset = le_cast_int(src_buffer, bntx_offset + 0x18);
    int file_size = le_cast_int(src_buffer, bntx_offset + 0x1C);

    cout << "BNTX : Version : 0x" << hex << version << endl;
    cout << "BNTX : BOM : 0x" << hex << byte_order_mark << endl;
    cout << "BNTX : Alignment Exponent : 0x" << hex << alignment_exponent << endl;
    cout << "BNTX : File name offset : 0x" << hex << file_name_offset << endl;
    cout << "BNTX : Is relocated : 0x" << dec << is_relocated << endl;
    cout << "BNTX : _STR Table offset : 0x" << hex << str_table_offset << endl;
    cout << "BNTX : _RLT Table offset : 0x" << hex << rlt_table_offset << endl;
    cout << "BNTX : File size : " << dec << file_size << endl;

    return 0;    
}

int print_nx_header(char* src_buffer, int nx_offset) {

    // Extract important data from headers
    int nx_number_of_files = le_cast_int(src_buffer, nx_offset + 0x4);
    long brti_address_table_offset = le_cast_long(src_buffer, nx_offset + 0x8);
    long brtd_table_offset = le_cast_long(src_buffer, nx_offset + 0x10);
    long dic_table_offset = le_cast_long(src_buffer, nx_offset + 0x18);

    cout << "NX : Number of files: " << nx_number_of_files << endl;
    cout << "NX : BRTI Address table offset: 0x" << hex << brti_address_table_offset << dec << endl;
    cout << "NX : BRTD Table offset: 0x" << hex << brtd_table_offset << dec << endl;
    cout << "NX : _DIC Table offset: 0x" << hex << dic_table_offset << dec << endl;

    return 0;
}

int print_str_header(char* src_buffer, int str_offset) {

    // Extract important data from headers
    long str_next_section_offset = le_cast_long(src_buffer, str_offset + 0x8);
    long str_number_of_files = le_cast_long(src_buffer, str_offset + 0x10);
    
    cout << "STR : Next section offset: 0x" << hex << str_next_section_offset << endl;
    cout << "STR : Number of files: " << dec << str_number_of_files << endl;

    return 0;
}

int print_str_table(char* src_buffer, int str_offset) {
    return 0;
}

int print_dic_header(char* src_buffer, int dic_offset) {

    // Extract important data from headers
    int dic_number_of_files = le_cast_int(src_buffer, dic_offset + 0x4);

    cout << "DIC : Number of files: " << dec << dic_number_of_files << endl;

    return 0;
}

int print_dic_table(char* src_buffer, int dic_offset) {
    return 0;
}

int print_brti_header(char* src_buffer) {
    return 0;
}

int print_brtd_header(char* src_buffer) {
    return 0;
}

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
    char *bntx_data = new char[bntx_data_size];

    // Go back to begining of file and read into buffer
    input_stream.seekg(0, ios::beg);
    input_stream.read(bntx_data, bntx_data_size);
    input_stream.close();

    cout << file_path_in << endl;

    // Print out each header

    // --------------- BNTX HEADER -------------------
    unsigned int bntx_header_size = 0x20;
    unsigned int bntx_header_offset = 0x0;
    unsigned int bntx_magic_number = be_cast_int(bntx_data, bntx_header_offset);

    if(bntx_magic_number != BNTX) {
        cerr << "[!] Error, Doesn't contain valid BNTX section! " << file_path_in << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;
    }

    print_bntx_header(bntx_data, bntx_header_offset);

    short str_header_offset = le_cast_short(bntx_data, bntx_header_offset + 0x16);
    int rlt_header_offset = le_cast_int(bntx_data, bntx_header_offset + 0x18);

    // --------------- NX HEADER -------------------
    unsigned int nx_header_size = 0x20;
    unsigned int nx_header_offset = bntx_header_offset + bntx_header_size;
    unsigned int nx_magic_number = be_cast_int(bntx_data, nx_header_offset);

    if(nx_magic_number != NX) {
        cerr << "[!] Error, Doesn't contain valid NX section! " << file_path_in << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;

    }

    print_nx_header(bntx_data, nx_header_offset);

    long brti_header_offset = le_cast_long(bntx_data, nx_header_offset + 0x8);
    long brtd_header_offset = le_cast_long(bntx_data, nx_header_offset + 0x10);
    long dic_header_offset = le_cast_long(bntx_data, nx_header_offset + 0x18);
    /*
    long brti_address_table_offset = le_cast_long(nx_header, nx_header_offset + 0x8);
    long brtd_table_offset = le_cast_long(nx_header, nx_header_offset + 0x10);
    long dic_table_offset = le_cast_long(nx_header, nx_header_offset + 0x18);
     */
    
     // --------------- _STR HEADER -------------------
    unsigned int str_header_size = 0x18;
    unsigned int str_table_offset = str_header_offset + str_header_size;
    unsigned int str_magic_number = be_cast_int(bntx_data, str_header_offset);

    if(str_magic_number != STR) {
        cerr << "[!] Error, Doesn't contain valid _STR section! " << file_path_in << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;

    }

    print_str_header(bntx_data, str_header_offset);
    print_str_table(bntx_data, str_table_offset);

    // --------------- _DIC HEADER -------------------
    unsigned int dic_header_size = 0x14;
    unsigned int dic_table_offset = dic_header_offset + dic_header_size;
    unsigned int dic_magic_number = be_cast_int(bntx_data, dic_header_offset);

    if(dic_magic_number != DIC) {
        cerr << "[!] Error, Doesn't contain valid DIC section! " << file_path_in << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;
    }

    print_dic_header(bntx_data, dic_header_offset);
    print_dic_table(bntx_data, dic_table_offset);
    
    // --------------- BRTI HEADER -------------------
    // --------------- BRTD HEADER -------------------
    // --------------- _RLT HEADER -------------------

    delete[] bntx_data;
    bntx_data = nullptr;

    cout << endl;

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
