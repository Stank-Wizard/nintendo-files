#include <iostream>
#include <fstream>
#include <filesystem>
#include "../utils/utils.hpp"

#define BNTX 1112429656
#define BRTI 1112691785
#define BRTD 1112691780
#define STR 1599296594
#define RLT 1599229012
#define DIC 1598310723
#define NX 1314398240

using namespace std;

int print_bntx_header(char* buffer, int offset) {

    // Extract important data from headers
    long version = le_cast_long(buffer, 0x4 + offset);
    short byte_order_mark = le_cast_short(buffer, 0xC + offset);
    short alignment_exponent = le_cast_short(buffer, 0xE + offset);
    int file_name_offset = le_cast_int(buffer, 0x10 + offset);
    short is_relocated = le_cast_short(buffer, 0x14 + offset);
    short str_table_offset = le_cast_short(buffer, 0x16 + offset);
    int rlt_table_offset = le_cast_int(buffer, 0x18 + offset);
    int file_size = le_cast_int(buffer, 0x1C + offset);

    cout << "BNTX : Version : 0x" << hex << version << endl;
    cout << "BNTX : BOM : 0x" << hex << byte_order_mark << endl;
    cout << "BNTX : Alignment Exponent : 0x" << hex << alignment_exponent << endl;
    cout << "BNTX : File name offset : 0x" << hex << file_name_offset << endl;
    cout << "BNTX : Is relocated : 0x" << dec << is_relocated << endl;
    cout << "BNTX : _STR Table offset : 0x" << hex << str_table_offset << endl;
    cout << "BNTX : _RLT Table offset : 0x" << hex << rlt_table_offset << endl;
    cout << "BNTX : File size : " << dec << file_size << endl;
    cout << endl;

    return 0;    
}

int print_nx_header(char* buffer, int offset) {

    // Extract important data from headers
    int nx_number_of_files = le_cast_int(buffer, 0x4 + offset);
    long brti_address_table_offset = le_cast_long(buffer, 0x8 + offset);
    long brtd_table_offset = le_cast_long(buffer, 0x10 + offset);
    long dic_table_offset = le_cast_long(buffer, 0x18 + offset);

    cout << "NX : Number of files: " << nx_number_of_files << endl;
    cout << "NX : BRTI Address table offset: 0x" << hex << brti_address_table_offset << dec << endl;
    cout << "NX : BRTD Table offset: 0x" << hex << brtd_table_offset << dec << endl;
    cout << "NX : _DIC Table offset: 0x" << hex << dic_table_offset << dec << endl;
    cout << endl;

    return 0;
}

int print_str_header(char* buffer, int offset) {

    // Extract important data from headers
    long str_next_section_offset = le_cast_long(buffer, 0x8 + offset);
    long str_number_of_files = le_cast_long(buffer, 0x10 + offset);
    int str_entries_offset = 0x18 + offset;

    cout << "STR : Next section offset: 0x" << hex << str_next_section_offset << endl;
    cout << "STR : Number of files: " << dec << str_number_of_files << endl;
    cout << endl;

    return 0;
}

int print_dic_header(char* buffer, int offset) {

    // Extract important data from headers
    int dic_number_of_files = le_cast_int(buffer, 0x4 + offset);

    cout << "DIC : Number of files: " << dec << dic_number_of_files << endl;
    cout << endl;

    dic_number_of_files ++;

    for(int i = 1; i < dic_number_of_files; i++) {

        string file_name;

        int reference_bit = le_cast_int(buffer, 0x8 + i*0x10 + offset);
        short left_node_index = le_cast_short(buffer, 0xC + i*0x10 +  offset);
        short right_node_index = le_cast_short(buffer, 0xE + i*0x10 +  offset);
        long dic_str_entry_offset = le_cast_long(buffer, 0x10 + i*0x10 + offset);

        for(int j = 2; buffer[j + dic_str_entry_offset] != '\0'; j++) {
            file_name += buffer[j + dic_str_entry_offset];
        }

        cout << "DIC : Entry number : " << dec << i << endl;
        cout << "DIC : Reference Bit: 0x" << hex << reference_bit << endl;
        cout << "DIC : Left Node Index: 0x" << hex << left_node_index << endl;
        cout << "DIC : Right Node Index: 0x" << hex << right_node_index << endl;
        cout << "DIC : STR Entry offset : 0x" << hex << dic_str_entry_offset << endl;
        cout << "DIC : File name : " << file_name << endl;
        cout << endl;

    }

    return 0;
}

int print_brti_header(char* buffer, int offset) {

    string file_name;
    int brti_next_section_offset = le_cast_int(buffer, 0x4 + offset);
    long brti_header_size = le_cast_long(buffer, 0x8 + offset);
    char brti_flags = buffer[0x10 + offset];
    char brti_dimensions = buffer[0x11 + offset];
    short brti_tile_mode = le_cast_short(buffer, 0x12 + offset);
    short brti_swizzle_size = le_cast_short(buffer, 0x14 + offset);
    short brti_mip_map_count = le_cast_short(buffer, 0x16 + offset);
    short brti_multi_sample_count = le_cast_short(buffer, 0x18 + offset);
    short brti_reverse_1a = le_cast_short(buffer, 0x1C + offset);
    unsigned int brti_format = le_cast_int(buffer, 0x20 + offset);
    unsigned int brti_access_flags = le_cast_int(buffer, 0x24 + offset);
    int brti_width = le_cast_int(buffer, 0x28 + offset);
    int brti_height = le_cast_int(buffer, 0x2C + offset);
    int brti_array_count = le_cast_int(buffer, 0x30 + offset);
    int brti_block_height_log_2 = le_cast_int(buffer, 0x34 + offset);
    int brti_reserved_38 = le_cast_int(buffer, 0x38 + offset);
    int brti_reserved_3C = le_cast_int(buffer, 0x3C + offset);
    int brti_reserved_40 = le_cast_int(buffer, 0x40 + offset);
    int brti_reserved_44 = le_cast_int(buffer, 0x44 + offset);
    int brti_reserved_48 = le_cast_int(buffer, 0x48 + offset);
    int brti_reserved_4C = le_cast_int(buffer, 0x4C + offset);
    int brti_data_length = le_cast_int(buffer, 0x50 + offset);
    int brti_alignment = le_cast_int(buffer, 0x54 + offset);
    int brti_channel_type = le_cast_int(buffer, 0x58 + offset);
    int brti_texture_type = le_cast_int(buffer, 0x5C + offset);
    long brti_name_address = le_cast_long(buffer, 0x60 + offset);
    long brti_parent_address = le_cast_long(buffer, 0x68 + offset);
    long brti_ptrs_address = le_cast_long(buffer, 0x70 + offset);

    for(int j = 2; buffer[j + brti_name_address] != '\0'; j++) {
        file_name += buffer[j + brti_name_address];
    }

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
    cout << "DIC : File Name : " << file_name << endl;
    //cout << "BRTD : Ptrs Address Start : 0x" << +brti_ptrs_address+0x1ff8 << endl; 
    //cout << "BRTD : Ptrs Address End : 0x" << +brti_ptrs_address+brti_data_length+0x1ff8 << endl; 
    cout << endl;

    return 0;
}

int print_brtd_header(char* buffer, int offset) {
    return 0;
}

int print_rlt_header(char* buffer, int offset) {
    return 0;
}

int extract_bntx(string file_path_in, string folder_path_out) {

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

    //print_bntx_header(bntx_data, bntx_header_offset);

    short str_header_offset = le_cast_short(bntx_data, 0x16 + bntx_header_offset);
    int rlt_header_offset = le_cast_int(bntx_data, 0x18 + bntx_header_offset);

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

    //print_nx_header(bntx_data, nx_header_offset);

    long brti_address_table_offset = le_cast_long(bntx_data, 0x8 + nx_header_offset);
    long brtd_header_offset = le_cast_long(bntx_data, 0x10 + nx_header_offset);
    long dic_header_offset = le_cast_long(bntx_data, 0x18 + nx_header_offset);

    // --------------- _STR HEADER -------------------

    unsigned int str_header_size = 0x18;
    unsigned int str_table_offset = str_header_offset + str_header_size;
    unsigned int str_magic_number = be_cast_int(bntx_data, str_header_offset);

    if(str_magic_number != STR) {
        cerr << "[!] Error, Doesn't contain valid STR section! " << file_path_in << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;

    }

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

    int dic_number_of_files = le_cast_int(bntx_data, 0x4 + dic_header_offset);

    // --------------- BRTI HEADERS -------------------

    for(int i = 0; i < dic_number_of_files; i++) {
        unsigned int brti_pointer_offset = i * 0x8 + brti_address_table_offset;
        unsigned int brti_header_offset = le_cast_int(bntx_data, brti_pointer_offset);
        unsigned int brti_magic_number = be_cast_int(bntx_data, brti_header_offset);

        if(brti_magic_number != BRTI) {
            cerr << "[!] Error, Doesn't contain valid BRTI section! " << file_path_in << endl;

            delete[] bntx_data;
            bntx_data = nullptr;

            return 1;
        }

        //print_brti_header(bntx_data, brti_header_offset);

    }

    // --------------- BRTD HEADER -------------------

    unsigned int brtd_magic_number = be_cast_int(bntx_data, brtd_header_offset);

    if(brtd_magic_number != BRTD) {
        cerr << "[!] Error, Doesn't contain valid BRTD section! " << file_path_in << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;
    }

    // --------------- _RLT HEADER -------------------

    unsigned int rlt_magic_number = be_cast_int(bntx_data, rlt_header_offset);

    if(rlt_magic_number != RLT) {
        cerr << "[!] Error, Doesn't contain valid RLT section! " << file_path_in << endl;

        cerr << rlt_magic_number << endl;

        delete[] bntx_data;
        bntx_data = nullptr;

        return 1;
    }

    // ---------------- UNPACKING --------------------

    for(int i = 0; i < dic_number_of_files; i++) {

        string file_name, file_path_out;
        unsigned int brti_pointer_offset = i * 0x8 + brti_address_table_offset;
        unsigned int brti_header_offset = le_cast_int(bntx_data, brti_pointer_offset);

        unsigned int brti_data_length = le_cast_int(bntx_data, 0x50 + brti_header_offset);
        unsigned long brti_name_address = le_cast_long(bntx_data, 0x60 + brti_header_offset);
        unsigned long brti_ptrs_address = le_cast_long(bntx_data, 0x70 + brti_header_offset);
        unsigned long brtd_file_data_offset = brti_ptrs_address + brtd_header_offset + 0x8;

        for(int j = 2; bntx_data[j + brti_name_address] != '\0'; j++) {
            file_name += bntx_data[j + brti_name_address];
        }
        
        file_path_out = folder_path_out + file_name;

        // Create file path for files
        filesystem::path nested_path = folder_path_out;
        filesystem::create_directories(nested_path);

        // Create file stream for compressed data
        ofstream output_stream(file_path_out, ios::out | ios::binary);

        // If the file stream isnt open
        if(!output_stream.is_open()) {
            cerr << "[!] Error writing to file: " << file_path_out << endl;

            delete[] bntx_data;
            bntx_data = nullptr;

            return 1;
        }

        // Write portion from brtd into its own file
        output_stream.write(&bntx_data[brtd_file_data_offset], brti_data_length);
        output_stream.close();

        cout << file_path_in << " -> " << file_path_out << endl;

    }

    delete[] bntx_data;
    bntx_data = nullptr;

    return 0;
}

int main() {

    extract_bntx("systemDataUnpacked/common/timg/__Combined.bntx", "systemDataExtracted/common/");
    extract_bntx("systemDataUnpacked/Entrance/timg/__Combined.bntx", "systemDataExtracted/Entrance/");
    extract_bntx("systemDataUnpacked/Eula/timg/__Combined.bntx", "systemDataExtracted/Eula/");
    extract_bntx("systemDataUnpacked/Flaunch/timg/__Combined.bntx", "systemDataExtracted/Flaunch/");
    extract_bntx("systemDataUnpacked/Gift/timg/__Combined.bntx", "systemDataExtracted/Gift/");
    extract_bntx("systemDataUnpacked/Interrupt/timg/__Combined.bntx", "systemDataExtracted/Interrupt/");
    extract_bntx("systemDataUnpacked/Migration/timg/__Combined.bntx", "systemDataExtracted/Migration/");
    extract_bntx("systemDataUnpacked/MyPage/timg/__Combined.bntx", "systemDataExtracted/MyPage/");
    extract_bntx("systemDataUnpacked/Notification/timg/__Combined.bntx", "systemDataExtracted/Notification/");
    extract_bntx("systemDataUnpacked/Option/timg/__Combined.bntx", "systemDataExtracted/Option/");
    extract_bntx("systemDataUnpacked/Psl/timg/__Combined.bntx", "systemDataExtracted/Psl/");
    extract_bntx("systemDataUnpacked/ResidentMenu/timg/__Combined.bntx", "systemDataExtracted/ResidentMenu/");
    extract_bntx("systemDataUnpacked/SaveMove/timg/__Combined.bntx", "systemDataExtracted/SaveMove/");
    extract_bntx("systemDataUnpacked/Set/timg/__Combined.bntx", "systemDataExtracted/Set/");

    return 0;
}
