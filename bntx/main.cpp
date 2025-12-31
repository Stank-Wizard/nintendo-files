#include <iostream>
#include <fstream>
#include <iomanip>
#include "../utils/utils.hpp"

#define BNTX 1112429656
#define BRTI 1112691785
#define BRTD 1111691780
#define STR 1599296594
#define RLT 1599299012
#define DIC 1598310723
#define NX 1314398240

using namespace std;

int print_bntx_header(char* buffer, int offset) {

    // Extract important data from headers
    long version = le_cast_long(buffer, offset + 0x4);
    short byte_order_mark = le_cast_short(buffer, offset + 0xC);
    short alignment_exponent = le_cast_short(buffer, offset + 0xE);
    int file_name_offset = le_cast_int(buffer, offset + 0x10);
    short is_relocated = le_cast_short(buffer, offset + 0x14);
    short str_table_offset = le_cast_short(buffer, offset + 0x16);
    int rlt_table_offset = le_cast_int(buffer, offset + 0x18);
    int file_size = le_cast_int(buffer, offset + 0x1C);

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

int print_nx_header(char* buffer, int offset) {

    // Extract important data from headers
    int nx_number_of_files = le_cast_int(buffer, offset + 0x4);
    long brti_address_table_offset = le_cast_long(buffer, offset + 0x8);
    long brtd_table_offset = le_cast_long(buffer, offset + 0x10);
    long dic_table_offset = le_cast_long(buffer, offset + 0x18);

    cout << "NX : Number of files: " << nx_number_of_files << endl;
    cout << "NX : BRTI Address table offset: 0x" << hex << brti_address_table_offset << dec << endl;
    cout << "NX : BRTD Table offset: 0x" << hex << brtd_table_offset << dec << endl;
    cout << "NX : _DIC Table offset: 0x" << hex << dic_table_offset << dec << endl;

    return 0;
}

int print_str_header(char* buffer, int offset) {

    // Extract important data from headers
    long str_next_section_offset = le_cast_long(buffer, offset + 0x8);
    long str_number_of_files = le_cast_long(buffer, offset + 0x10);
    int str_entries_offset = offset + 0x18;

    cout << "STR : Next section offset: 0x" << hex << str_next_section_offset << endl;
    cout << "STR : Number of files: " << dec << str_number_of_files << endl;

    /* DAMN THIS IS A HORRIBLE WAY TO DO THIS
    while(str_number_of_files != 0) {

        string str_entry;

        if(buffer[str_entries_offset] == '\0')
            str_entries_offset += 1;

        char size = buffer[str_entries_offset];
        char i = 0;
        str_entries_offset += 2;

        while(i != size) {

            str_entry += buffer[str_entries_offset + i];

            i += 1;
        }
        
        cout << "STR : " << str_entry << endl;

        str_entries_offset += size;
        str_entries_offset += 1;
        str_number_of_files -= 1;
    }
    */

    return 0;
}

int print_dic_header(char* buffer, int offset) {

    // Extract important data from headers
    int dic_number_of_files = le_cast_int(buffer, offset + 0x4);

    cout << "DIC : Number of files: " << dec << dic_number_of_files << endl;
    cout << endl;

    dic_number_of_files ++;

    for(int i = 1; i < dic_number_of_files; i++) {

        string file_name;

        int reference_bit = le_cast_int(buffer, offset + i*0x10 + 0x8);
        short left_node_index = le_cast_short(buffer, offset + i*0x10 + 0xC);
        short right_node_index = le_cast_short(buffer, offset + i*0x10 + 0xE);
        long dic_str_entry_offset = le_cast_long(buffer, offset + i*0x10 + 0x10);

        for(int j = 2; buffer[dic_str_entry_offset + j] != '\0'; j++) {
            file_name += buffer[dic_str_entry_offset + j];
        }

        cout << "DIC : Entry number : " << dec << i << endl;
        cout << "DIC : File name : " << file_name << endl;
        cout << "DIC : Reference Bit: 0x" << hex << reference_bit << endl;
        cout << "DIC : Left Node Index: 0x" << hex << left_node_index << endl;
        cout << "DIC : Right Node Index: 0x" << hex << right_node_index << endl;
        cout << "DIC : STR Entry offset : 0x" << hex << dic_str_entry_offset << endl;
        cout << endl;

    }

    return 0;
}

int print_brti_pointers(char* buffer, int offset) {

    for( int i = 0; i < 9; i++) {
        unsigned int brti_header_offset = le_cast_int(buffer, offset + i*0x8);

        cout << "BRTI : Header at 0x" << hex << brti_header_offset << endl;
    }

    return 0;
}

int print_brti_header(char* buffer, int offset) {

    int brti_next_section_offset = le_cast_int(buffer, offset + 0x4);
    long brti_header_size = le_cast_long(buffer, offset + 0x8);
    char brti_flags = buffer[offset + 0x10];
    char brti_dimensions = buffer[offset + 0x11];
    short brti_tile_mode = le_cast_short(buffer, offset + 0x12);
    short brti_swizzle_size = le_cast_short(buffer, offset + 0x14);
    short brti_mip_map_count = le_cast_short(buffer, offset + 0x16);
    short brti_multi_sample_count = le_cast_short(buffer, offset + 0x18);
    short brti_reverse_1a = le_cast_short(buffer, offset + 0x1C);
    unsigned int brti_format = le_cast_int(buffer, offset + 0x20);
    unsigned int brti_access_flags = le_cast_int(buffer, offset + 0x24);
    int brti_width = le_cast_int(buffer, offset + 0x28);
    int brti_height = le_cast_int(buffer, offset + 0x2C);
    int brti_array_count = le_cast_int(buffer, offset + 0x30);
    int brti_block_height_log_2 = le_cast_int(buffer, offset + 0x34);
    int brti_reserved_38 = le_cast_int(buffer, offset + 0x38);
    int brti_reserved_3C = le_cast_int(buffer, offset + 0x3C);
    int brti_reserved_40 = le_cast_int(buffer, offset + 0x40);
    int brti_reserved_44 = le_cast_int(buffer, offset + 0x44);
    int brti_reserved_48 = le_cast_int(buffer, offset + 0x48);
    int brti_reserved_4C = le_cast_int(buffer, offset + 0x4C);
    int brti_data_length = le_cast_int(buffer, offset + 0x50);
    int brti_alignment = le_cast_int(buffer, offset + 0x54);
    int brti_channel_type = le_cast_int(buffer, offset + 0x58);
    int brti_texture_type = le_cast_int(buffer, offset + 0x5C);
    long brti_name_address = le_cast_long(buffer, offset + 0x64);
    long brti_parent_address = le_cast_long(buffer, offset + 0x6C);
    long brti_ptrs_address = le_cast_long(buffer, offset + 0x74);

    cout << "BRTI : Next section offset : " << brti_next_section_offset << endl;
    cout << "BRTI : Header size : " << brti_header_size << endl;
    cout << "BRTI : Flags : 0x" << hex << +brti_flags << endl;
    cout << "BRTI : Dimensions : 0x" << hex << +brti_dimensions << endl;
    cout << "BRTI : Tile Mode : 0x" << hex << +brti_tile_mode << endl;
    cout << "BRTI : Swizzle Size : 0x" << hex << +brti_swizzle_size << endl;
    cout << "BRTI : Mip Map Count : 0x" << hex << +brti_mip_map_count << endl;
    cout << "BRTI : Multi Sample Count : 0x" << hex << +brti_multi_sample_count << endl;
    cout << "BRTI : Reverse 1a : 0x" << hex << +brti_reverse_1a << endl;
    cout << "BRTI : Format : 0x" << hex << +brti_format << endl;
    cout << "BRTI : Access Flags : 0x" << hex << +brti_access_flags << endl;
    cout << "BRTI : Width : 0x" << hex << +brti_width << endl;
    cout << "BRTI : Height : 0x" << hex << +brti_height << endl;
    cout << "BRTI : Array Count : 0x" << hex << +brti_array_count << endl;
    cout << "BRTI : Block Height Log 2 : 0x" << hex << +brti_block_height_log_2 << endl;
    cout << "BRTI : Reserved 38 : 0x" << hex << +brti_reserved_38 << endl;
    cout << "BRTI : Reserved 3C : 0x" << hex << +brti_reserved_3C << endl;
    cout << "BRTI : Reserved 40 : 0x" << hex << +brti_reserved_40 << endl;
    cout << "BRTI : Reserved 44 : 0x" << hex << +brti_reserved_44 << endl;
    cout << "BRTI : Reserved 48 : 0x" << hex << +brti_reserved_48 << endl;
    cout << "BRTI : Reserved 4C : 0x" << hex << +brti_reserved_4C << endl;
    cout << "BRTI : Data Length : 0x" << hex << +brti_data_length << endl;
    cout << "BRTI : Alignment : 0x" << hex << +brti_alignment << endl;
    cout << "BRTI : Channel Type : 0x" << hex << +brti_channel_type << endl;
    cout << "BRTI : Texture Type : 0x" << hex << +brti_texture_type << endl;
    cout << "BRTI : Name Address : 0x" << hex << +brti_name_address << endl;
    cout << "BRTI : Parent Address : 0x" << hex << +brti_parent_address << endl;
    cout << "BRTI : Ptrs Address : 0x" << hex << +brti_ptrs_address << endl;
    cout << endl;

    return 0;
}

int print_brtd_header(char* buffer, int offset) {
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

    long brti_address_table_offset = le_cast_long(bntx_data, nx_header_offset + 0x8);
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

    int dic_number_of_files = le_cast_int(bntx_data, dic_header_offset + 0x4);

    print_dic_header(bntx_data, dic_header_offset);
    
    // --------------- BRTI HEADERS -------------------

    for(int i = 0; i < dic_number_of_files; i++) {
        unsigned int brti_pointer_offset = brti_address_table_offset + i * 0x8;
        unsigned int brti_header_offset = le_cast_int(bntx_data, brti_pointer_offset);
        unsigned int brti_magic_number = be_cast_int(bntx_data, brti_header_offset);

        cout << "BRTI : Pointer table offset : 0x" << hex <<  brti_pointer_offset << endl;
        cout << "BRTI : Header offset : 0x" << hex << brti_header_offset << endl;

        if(brti_magic_number != BRTI) {
            cerr << "[!] Error, Doesn't contain valid BRTI section! " << file_path_in << endl;

            delete[] bntx_data;
            bntx_data = nullptr;

            return 1;
        }

        print_brti_header(bntx_data, brti_header_offset);

    }

    // --------------- BRTD HEADER -------------------
    // --------------- _RLT HEADER -------------------

    delete[] bntx_data;
    bntx_data = nullptr;

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
