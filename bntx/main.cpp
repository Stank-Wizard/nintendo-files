#include <iostream>
#include <fstream>
#include <iomanip>
#include "../utils/utils.hpp"

#define bntx 1112429656
#define nx 1314398240
#define str 1599296594
#define brti 1112691785
#define brtd 1111691780
#define rlt 1599299012
#define dic 1598310723

using namespace std;

int copy_section(char* src_buffer, int src_buffer_pos, char* dest_buffer, int dest_buffer_size) {

    // Iterate through each item in src_buffer and assign value to dest_buffer
    for(int i = 0; src_buffer_pos+i < (src_buffer_pos+dest_buffer_size); i++) {
        dest_buffer[i] = src_buffer[src_buffer_pos+i];
    }

    return 0;
}

int print_bntx_header(char* src_buffer) {

    unsigned int bntx_magic_number = be_cast_int(src_buffer, 0x0);

    if(bntx_magic_number != bntx) {
        cerr << "[!] Error not a bntx file! " << endl;

        return 1;
    }

    // Extract important data from headers
    long version = le_cast_long(src_buffer, 0x4);
    short byte_order_mark = le_cast_short(src_buffer, 0xC);
    short alignment_exponent = le_cast_short(src_buffer, 0xE);
    int file_name_offset = le_cast_int(src_buffer, 0x10);
    short is_relocated = le_cast_short(src_buffer, 0x14);
    short str_table_offset = le_cast_short(src_buffer, 0x16);
    int rlt_table_offset = le_cast_int(src_buffer, 0x18);
    int file_size = le_cast_int(src_buffer, 0x1C);

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

int print_nx_header(char* src_buffer) {

    unsigned int nx_magic_number = be_cast_int(src_buffer, 0x0);

    if(nx_magic_number != nx) {
        cerr << "[!] Error doesnt contain a nx texture container! " << endl;

        return 1;
    }

    // Extract important data from headers
    int nx_number_of_files = le_cast_int(src_buffer, 0x4);
    long brti_address_table_offset = le_cast_long(src_buffer, 0x8);
    long brtd_table_offset = le_cast_long(src_buffer, 0x10);
    long dic_table_offset = le_cast_long(src_buffer, 0x18);

    cout << "NX : Number of files: " << nx_number_of_files << endl;
    cout << "NX : BRTI Address table offset: 0x" << hex << brti_address_table_offset << dec << endl;
    cout << "NX : BRTD Table offset: 0x" << hex << brtd_table_offset << dec << endl;
    cout << "NX : _DIC Table offset: 0x" << hex << dic_table_offset << dec << endl;

    return 0;
}

int print_str_header(char* src_buffer) {

    // Extract magic number from header
    unsigned int str_magic_number = be_cast_int(src_buffer, 0x0);

    // Magic number check
    if(str_magic_number != str) {
        cerr << "[!] Error doesnt contain a str table! " << endl;

        return 1;
    }

    // Extract important data from headers
    long str_next_section_offset = le_cast_long(src_buffer, 0x8);
    long str_number_of_files = le_cast_long(src_buffer, 0x10);
    
    cout << "STR : Next section offset: 0x" << hex << str_next_section_offset << endl;
    cout << "STR : Number of files: " << dec << str_number_of_files << endl;

    return 0;
}

int print_dic_header(char* src_buffer) {

    unsigned int dic_magic_number = be_cast_int(src_buffer, 0x0);

    // Magic number check
    if(dic_magic_number != dic) {
        cerr << "[!] Error doesnt contain a dir table! " << endl;

        return 1;
    }

    // Extract important data from headers
    int dic_number_of_files = le_cast_int(src_buffer, 0x4);

    cout << "DIC : Number of files: " << dec << dic_number_of_files << endl;

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

    // Allocate array in memory for file contents
    char *bntx_data = new char[bntx_data_size];

    // Go back to begining of file
    input_stream.seekg(0, ios::beg);

    // Read contents of file into memory
    input_stream.read(bntx_data, bntx_data_size);

    // Close file stream
    input_stream.close();

    cout << file_path_in << endl;

    // Print out each header
    unsigned int bntx_header_size = 0x20;
    char *bntx_header = new char[bntx_header_size];
    copy_section(bntx_data, 0x0, bntx_header, bntx_header_size);
    short str_table_offset = le_cast_short(bntx_header, 0x16);
    int rlt_table_offset = le_cast_int(bntx_header, 0x18);
    print_bntx_header(bntx_header);
    delete[] bntx_header;
    bntx_header = nullptr;

    unsigned int nx_header_size = 0x20;
    char *nx_header = new char[nx_header_size];
    copy_section(bntx_data, 0x20, nx_header, nx_header_size);
    long brti_address_table_offset = le_cast_long(nx_header, 0x8);
    long brtd_table_offset = le_cast_long(nx_header, 0x10);
    long dic_table_offset = le_cast_long(nx_header, 0x18);
    print_nx_header(nx_header);
    delete[] nx_header;
    nx_header = nullptr;

    unsigned int str_header_size = 0x18;
    char *str_header = new char[str_header_size];
    copy_section(bntx_data, str_table_offset, str_header, str_header_size);
    print_str_header(str_header);
    delete[] str_header;
    str_header = nullptr;

    unsigned int dic_header_size = 0x14;
    char *dic_header = new char[dic_header_size];
    copy_section(bntx_data, dic_table_offset, dic_header, dic_header_size);
    print_dic_header(dic_header);
    delete[] dic_header;
    dic_header = nullptr;
    
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

    return 0;
}
