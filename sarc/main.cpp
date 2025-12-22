#include <iostream>
#include <fstream>
#include <filesystem>
#include "../utils/utils.hpp"

#define SARC 1396789827
#define SFAT 1397113172
#define SFNT 1397116500

using namespace std;

int unpack_sarc(string file_path_in, string folder_path_out) {

    // Open input file stream for archived data
    ifstream input_stream(file_path_in, ios::in | ios::ate | ios::binary);

    // If the file stream isnt open
    if(!input_stream.is_open()) {
        cerr << "[!] Error opening file: " << file_path_in << endl;
        return 1;
    }

    // Get total size of data
    unsigned int raw_data_size = input_stream.tellg();
    char *raw_data = new char[raw_data_size];

    // Go back to the begining of data and transfer contents to memory
    input_stream.seekg(0, ios::beg);
    input_stream.read(raw_data, raw_data_size);
    input_stream.close();

    unsigned int sarc_header_offset = 0x0;
    unsigned int sarc_header_size = 0x14;

    // sarc magic number check
    unsigned int sarc_magic_number = be_cast_int(raw_data, sarc_header_offset);
    if(sarc_magic_number != SARC) {
        cerr << "[!] Error not a sarc archive file! " << file_path_in << endl;

        delete[] raw_data;
        raw_data = nullptr;

        return 1;
    }

    unsigned int sfat_header_offset = sarc_header_offset + sarc_header_size;
    unsigned int sfat_header_size = 0xC;

    // sfat magic number check
    unsigned int sfat_magic_number = be_cast_int(raw_data, sfat_header_offset);
    if(sfat_magic_number != SFAT) {
        cerr << "[!] Error, doesnt contain sfat section! " << file_path_in << endl;

        delete[] raw_data;
        raw_data = nullptr;

        return 1;
    }

    unsigned short number_of_files = le_cast_short(raw_data, sfat_header_offset + 0x6);
    unsigned int sfat_entries_offset = sfat_header_offset + sfat_header_size;
    unsigned int sfat_entries_size = number_of_files * 0x10;

    unsigned int sfnt_header_offset = sfat_entries_offset + sfat_entries_size;
    unsigned int sfnt_header_size = 0x8;

    // sfnt magic number check
    unsigned int sfnt_magic_number = be_cast_int(raw_data, sfnt_header_offset);
    if(sfnt_magic_number != SFNT) {
        cerr << "[!] Error, doesnt contain sfnt section! " << file_path_in << endl;

        delete[] raw_data;
        raw_data = nullptr;

        return 1;
    }

    unsigned int sfnt_entries_offset = sfnt_header_offset + sfnt_header_size;
    unsigned int sarc_entries_offset = le_cast_int(raw_data, sarc_header_offset + 0xC);
    unsigned int sfnt_entries_size = sfnt_entries_offset - sarc_entries_offset;
    unsigned int sarc_entries_size = raw_data_size - sarc_entries_offset;

    // Start iterating through each entry in sfat
    for(int sfat_pos = 0; sfat_pos < sfat_entries_size; sfat_pos += 0x10) {

        // Interpret data from each entry and setup the necessary variables
        unsigned int file_name_position = le_cast_short(raw_data, sfat_entries_offset + sfat_pos + 0x4);
        
        file_name_position *= 4;

        unsigned int start_of_file = le_cast_int(raw_data, sfat_entries_offset + sfat_pos + 0x8);
        unsigned int end_of_file = le_cast_int(raw_data, sfat_entries_offset + sfat_pos + 0xC);
        unsigned int file_size = end_of_file - start_of_file;

        string file_name, folder_name;

        // Get whole file name 
        for(int sfnt_pos = 0; raw_data[sfnt_entries_offset + sfnt_pos + file_name_position] != '\0'; sfnt_pos++) {
            file_name += raw_data[sfnt_entries_offset + sfnt_pos + file_name_position];
        }

        // Bit of a hack to get folder paths
        folder_name = file_name.substr(0, file_name.rfind('/'));

        // Create file path for files
        filesystem::path nested_path = folder_path_out + folder_name + "/";
        filesystem::create_directories(nested_path);

        char *file = new char[file_size];

        // Read from raw data into file memory
        for(int sarc_pos = 0; sarc_pos < file_size; sarc_pos++) {
            file[sarc_pos] = raw_data[sarc_entries_offset + sarc_pos + start_of_file];
        }

        // Open output stream for file
        ofstream output_stream(folder_path_out + file_name, ios::out | ios::binary);

        // If stream isnt open
        if(!output_stream.is_open()) {
            cerr << "[!] Error opening file: " << folder_path_out + file_name << endl;

            delete[] raw_data;
            delete[] file;
            raw_data = nullptr;
            file = nullptr;

            return 1;
        }

        // Write data and close stream
        output_stream.write(file, file_size);
        output_stream.close();

        // Clean up variables
        delete[] file;

        // Prevent dangling pointer
        file = nullptr;
    }


    // Clean up un needed variables and prevent dangling pointer
    delete[] raw_data;
    raw_data = nullptr;

    cout << file_path_in << " -> " << folder_path_out << endl;

    return 0;
}

int main() {

    unpack_sarc("systemDataDecompressed/common.arc","systemDataUnpacked/common/");
    unpack_sarc("systemDataDecompressed/Entrance.arc","systemDataUnpacked/Entrance/");
    unpack_sarc("systemDataDecompressed/Eula.arc","systemDataUnpacked/Eula/");
    unpack_sarc("systemDataDecompressed/Flaunch.arc","systemDataUnpacked/Flaunch/");
    unpack_sarc("systemDataDecompressed/Gift.arc","systemDataUnpacked/Gift/");
    unpack_sarc("systemDataDecompressed/Interrupt.arc","systemDataUnpacked/Interrupt/");
    unpack_sarc("systemDataDecompressed/Migration.arc","systemDataUnpacked/Migration/");
    unpack_sarc("systemDataDecompressed/MyPage.arc","systemDataUnpacked/MyPage/");
    unpack_sarc("systemDataDecompressed/Notification.arc","systemDataUnpacked/Notification/");
    unpack_sarc("systemDataDecompressed/Option.arc","systemDataUnpacked/Option/");
    unpack_sarc("systemDataDecompressed/Psl.arc","systemDataUnpacked/Psl/");
    unpack_sarc("systemDataDecompressed/ResidentMenu.arc","systemDataUnpacked/ResidentMenu/");
    unpack_sarc("systemDataDecompressed/SaveMove.arc","systemDataUnpacked/SaveMove/");
    unpack_sarc("systemDataDecompressed/Set.arc","systemDataUnpacked/Set/");

    return 0;
}