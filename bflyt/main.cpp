#include <iostream>
#include <fstream>
#include <iomanip>
#include "../utils/utils.h"

#define bflyt 1179408724
#define lyt1 1819898929
#define cnt1 1668183089
#define usd1 1970496561
#define txl1 1954049073
#define fnl1 1718512689
#define mat1 1835103281
#define grp1 1735553073
#define grs1 1735553841
#define gre1 1735550257
#define pan1 1885433393
#define pas1 1885434673
#define pae1 1885431089
#define bnd1 1651401777
#define pic1 1885954865
#define prt1 1886549041
#define txt1 1954051121
#define wnd1 2003723313


using namespace std;

int handle_lyt1(char* buffer, int size) {

    bool is_drawn_from_middle = buffer[0x8];

    float layout_width = le_cast_float(buffer, 0xC);
    float layout_height = le_cast_float(buffer, 0x10);
    float maximum_parts_width = le_cast_float(buffer, 0x14);
    float maximum_parts_height = le_cast_float(buffer, 0x18);

    string layout_name = "";
    for(char i=0x1C; buffer[i] != '\0'; i++) {
        layout_name += buffer[i];
    }

    cout << "\tIs Drawn from middle: " << is_drawn_from_middle << endl;
    cout << "\tLayout Width: " << layout_width << endl;
    cout << "\tLayout Height: " << layout_height << endl;
    cout << "\tMaximum Parts Width: " << maximum_parts_width << endl;
    cout << "\tMaximum Parts Height: " << maximum_parts_height << endl;
    cout << "\tLayout name: " << layout_name << endl;
    cout << endl;

    return 0;
}

int handle_pan1(char* buffer, int size) {

    unsigned char flags = buffer[0x8];
    unsigned char bitfield = buffer[0x9];
    unsigned char alpha_value = buffer[0xA];
    unsigned char part_scaling = buffer[0xB];

    string pane_name = "";
    for(char i=0xC; buffer[i] != '\0'; i++) {
        pane_name += buffer[i];
    }

    string user_data = "";
    for(char i = 0x24; i < 0x2C; i++) {
        user_data += buffer[i];
    }
    
    float x_position = le_cast_float(buffer, 0x2C);
    float y_position = le_cast_float(buffer, 0x30);
    float z_position = le_cast_float(buffer, 0x34);
    float x_rotation = le_cast_float(buffer, 0x38);
    float y_rotation = le_cast_float(buffer, 0x3C);
    float z_rotation = le_cast_float(buffer, 0x40);
    float x_scale = le_cast_float(buffer, 0x44);
    float y_scale = le_cast_float(buffer, 0x48);
    float pane_width = le_cast_float(buffer, 0x4C);
    float pane_height = le_cast_float(buffer, 0x50);

    cout << "\tFlags: " << +flags << endl;
    cout << "\tBitfield: " << hex << +bitfield << dec << endl;
    cout << "\tAlpha value: " << hex << +alpha_value << dec << endl;
    cout << "\tPart Scaling: " << hex << +part_scaling << dec << endl;
    cout << "\tPane Name: " << pane_name << endl;
    cout << "\tUser Data: " << hex << user_data << dec << endl;
    cout << "\tX Position: " << x_position << endl;
    cout << "\tY Position: " << y_position << endl;
    cout << "\tZ Position: " << z_position << endl;
    cout << "\tX Rotation: " << x_rotation << endl;
    cout << "\tY Rotation: " << y_rotation << endl;
    cout << "\tZ Rotation: " << z_rotation << endl;
    cout << "\tX Scale: " << x_scale << endl;
    cout << "\tY Scale: " << y_scale << endl;
    cout << "\tPane Width: " << pane_width << endl;
    cout << "\tPane Height: " << pane_height <<endl;
    cout << endl;

    return 0;
}

int handle_prt1(char* buffer, int size) {

    unsigned char flags = buffer[0x8];
    unsigned char bitfield = buffer[0x9];
    unsigned char alpha_value = buffer[0xA];
    unsigned char part_scaling = buffer[0xB];

    string pane_name = "";
    for(char i=0xC; buffer[i] != '\0'; i++) {
        pane_name += buffer[i];
    }

    string user_data = "";
    for(char i = 0x24; i < 0x2C; i++) {
        user_data += buffer[i];
    }
    
    float x_position = le_cast_float(buffer, 0x2C);
    float y_position = le_cast_float(buffer, 0x30);
    float z_position = le_cast_float(buffer, 0x34);
    float x_rotation = le_cast_float(buffer, 0x38);
    float y_rotation = le_cast_float(buffer, 0x3C);
    float z_rotation = le_cast_float(buffer, 0x40);
    float x_scale = le_cast_float(buffer, 0x44);
    float y_scale = le_cast_float(buffer, 0x48);
    float pane_width = le_cast_float(buffer, 0x4C);
    float pane_height = le_cast_float(buffer, 0x50);

    cout << "\tFlags: " << +flags << endl;
    cout << "\tBitfield: " << hex << +bitfield << dec << endl;
    cout << "\tAlpha value: " << hex << +alpha_value << dec << endl;
    cout << "\tPart Scaling: " << hex << +part_scaling << dec << endl;
    cout << "\tPane Name: " << pane_name << endl;
    cout << "\tUser Data: " << hex << user_data << dec << endl;
    cout << "\tX Position: " << x_position << endl;
    cout << "\tY Position: " << y_position << endl;
    cout << "\tZ Position: " << z_position << endl;
    cout << "\tX Rotation: " << x_rotation << endl;
    cout << "\tY Rotation: " << y_rotation << endl;
    cout << "\tZ Rotation: " << z_rotation << endl;
    cout << "\tX Scale: " << x_scale << endl;
    cout << "\tY Scale: " << y_scale << endl;
    cout << "\tPane Width: " << pane_width << endl;
    cout << "\tPane Height: " << pane_height <<endl;
    cout << endl;

    return 0;
}

int handle_mat1(char* buffer, int size) {
    // NOT WORKING AS INTENDED

    unsigned int top_left_color = le_cast_int(buffer, 0x0);
    unsigned int top_right_color = le_cast_int(buffer, 0x4);
    unsigned int bottom_left_color = le_cast_int(buffer, 0x8);
    unsigned int bottom_right_color = le_cast_int(buffer, 0xC);

    short index = le_cast_short(buffer, 0x10);
    short coord_sets_count = le_cast_short(buffer, 0x12);

    cout << "\tTop Left Color: 0x" << hex << setw(8)<< setfill('0') << top_left_color << dec << endl;
    cout << "\tTop Right Color: 0x" << hex << setw(8)<< setfill('0') << top_right_color << dec << endl;
    cout << "\tBottom Left Color: 0x" << hex << setw(8)<< setfill('0') << bottom_left_color << dec << endl;
    cout << "\tBottom Right Color: 0x" << hex << setw(8)<< setfill('0') << bottom_right_color << dec << endl;
    cout << "\tIndex: 0x" << hex << index << dec << endl;
    cout << "\tCoordinates sets count: " << coord_sets_count << endl;
    cout << endl;

    return 0;
}

int handle_section(char* section, int size) {

    // Get section identifier
    int identifier = be_cast_int(section, 0x0);

    switch (identifier){
        case lyt1:
            cout << "lyt1 : Layout" << endl;
            handle_lyt1(section, size);
            break;
        case cnt1:
            cout << "cnt1 : Control data" << endl;
            break;
        case usd1:
            cout << "usd1 : User data" << endl;
            break;
        case txl1:
            cout << "txl1 : Texture list" << endl;
            break;
        case fnl1:
            cout << "fnl1 : Font list" << endl;
            break;
        case mat1:
            cout << "mat1 : Material" << endl;
            handle_mat1(section, size);
            break;
        case grp1:
            cout << "grp1 : Group info" << endl;
            break;
        case grs1:
            cout << "grs1 : Group start" << endl;
            break;
        case gre1:
            cout << "gre1 : Group end" << endl;
            break;
        case pan1:
            cout << "pan1 : Pane info" << endl;
            handle_pan1(section, size);
            break;
        case pas1:
            cout << "pas1 : Pane start" << endl;
            break;
        case pae1:
            cout << "pae1 : Pane end" << endl;
            break;
        case bnd1:
            cout << "bnd1 : Bounding pane" << endl;
            break;
        case pic1:
            cout << "pic1 : Picture pane" << endl;
            break;
        case prt1:
            cout << "prt1 : Parts pane" << endl;
            handle_prt1(section, size);
            break;
        case txt1:
            cout << "txt1 : Textbox pane" << endl;
            break;
        case wnd1:
            cout << "wnd1 : Window pane" << endl;
            break;
        default:
            cout << "unk1 : Unknown" << endl;
            return 1;
            break;
    }

    return 0;
}

int copy_section(char* src_buffer, int src_buffer_pos, char* dest_buffer, int dest_buffer_size) {

    // Iterate through each item in src_buffer and assign value to dest_buffer
    for(int i = 0; src_buffer_pos+i < (src_buffer_pos+dest_buffer_size); i++) {
        dest_buffer[i] = src_buffer[src_buffer_pos+i];
    }

    return 0;
}

int read_bflyt(string file_path_in) {

    // Create file stream for compressed data
    ifstream input_stream(file_path_in, ios::in | ios::ate | ios::binary);

    // If the file stream isnt open
    if(!input_stream.is_open()) {
        cerr << "[!] Error reading from file: " << file_path_in << endl;
        return 1;
    }

    // Get file size and allocate memory for contents
    unsigned int bflyt_header_size = 0x14; 
    unsigned int bflyt_data_size =  input_stream.tellg();
    bflyt_data_size -= bflyt_header_size;

    // Allocate array in memory for file contents
    char *bflyt_data = new char[bflyt_data_size];
    char *bflyt_header = new char[bflyt_header_size];

    // Go back to begining of file
    input_stream.seekg(0, ios::beg);

    // Read contents of file header and contents into memory
    input_stream.read(bflyt_header, bflyt_header_size);
    input_stream.read(bflyt_data, bflyt_data_size);

    // Close file stream
    input_stream.close();

    // Interpret header data
    unsigned int bflyt_magic_number = be_cast_int(bflyt_header, 0x0);

    // Magic number check
    if(bflyt_magic_number != bflyt) {
        cerr << "[!] Error not a bflyt file! " << file_path_in << endl;

        delete[] bflyt_data;
        delete[] bflyt_header;

        bflyt_data = nullptr;
        bflyt_header = nullptr;

        return 1;
    }

    // DO SOMETHING WITH THE DATA PUNK!
    // cout << bflyt_data[0] << bflyt_data[1] << bflyt_data[2] << bflyt_data[3] << endl;

    cout << file_path_in << endl;

    unsigned int bflyt_pos = 0;

    // Start iterating through sections
    while(bflyt_pos < bflyt_data_size) {
        unsigned int section_size = le_cast_int(bflyt_data, bflyt_pos + 0x4);
        char *section = new char[section_size];
    
        // Get section from bflyt buffer into its own buffer and handle data
        copy_section(bflyt_data, bflyt_pos, section, section_size);
        handle_section(section, section_size);

        // Increment by section size
        bflyt_pos += section_size;

        // Clean up variables
        delete[] section;

        // Prevent dangling pointer
        section = nullptr;
    }

    // Clean up variables
    delete[] bflyt_data;
    delete[] bflyt_header;

    // Prevent dangling pointer
    bflyt_data = nullptr;
    bflyt_header = nullptr;

    cout << endl;

    return 0;
}

int main() {

	/*
    read_bflyt("systemDataUnpacked/Eula/blyt/BaseBg.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/BgNml.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/BtnCenterCheck.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/BtnLineNml.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/Cursor3.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/LineHeader_Root.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/SetBaseHeader.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/SetCntTerms.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/TextH1Ex.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/TextHeadCenter.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/Waiticon.bflyt");

    read_bflyt("systemDataUnpacked/ResidentMenu/blyt/RdtBase.bflyt");
    */

	read_bflyt("systemDataUnpacked/Eula/blyt/Cursor3.bflyt");
	read_bflyt("systemDataUnpacked/Eula/blyt/Waiticon.bflyt");

	return 0;
}
