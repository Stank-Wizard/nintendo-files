#include <iostream>
#include <fstream>
#include <filesystem>
#include "../utils/utils.hpp"

#define sarc 1396789827
#define sfat 1397113172
#define sfnt 1397116500

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
    unsigned int sarc_data_size = input_stream.tellg();

    // Go back to the begining of data
    input_stream.seekg(0, ios::beg);

    // Get file size and allocate memory for contents
    unsigned int sarc_header_size = 0x14;
    char *sarc_header = new char[sarc_header_size];
    input_stream.read(sarc_header, sarc_header_size);

    // Get file size and allocate memory for contents
    unsigned int sfat_header_size = 0xC;
    char *sfat_header = new char[sfat_header_size];
    input_stream.read(sfat_header, sfat_header_size);

    // Get file size and allocate memory for contents
    unsigned short number_of_files = le_cast_short(sfat_header, 0x6);
    unsigned int sfat_entries_size = number_of_files * 0x10;
    char *sfat_entries = new char[sfat_entries_size];
    input_stream.read(sfat_entries, sfat_entries_size);

    // Get file size and allocate memory for contents
    unsigned int sfnt_header_size = 0x8;
    char *sfnt_header = new char[sfnt_header_size];
    input_stream.read(sfnt_header, sfnt_header_size);

    // Get file size and allocate memory for contents
    unsigned int sfnt_entries_size = le_cast_int(sarc_header, 0xC);
    sfnt_entries_size -= sarc_header_size;
    sfnt_entries_size -= sfat_header_size;
    sfnt_entries_size -= sfat_entries_size;
    sfnt_entries_size -= sfnt_header_size;
    char *sfnt_entries = new char[sfnt_entries_size];
    input_stream.read(sfnt_entries, sfnt_entries_size);
    
    // Get file size and allocate memory for contents
    sarc_data_size -= sarc_header_size;
    sarc_data_size -= sfat_header_size;
    sarc_data_size -= sfat_entries_size;
    sarc_data_size -= sfnt_header_size;
    sarc_data_size -= sfnt_entries_size;
    char *sarc_data = new char[sarc_data_size];
    input_stream.read(sarc_data, sarc_data_size);

    // Close file stream
    input_stream.close();

    // Get magic number from header
    unsigned int sarc_magic_number = be_cast_int(sarc_header, 0x0);
    
    // Magic number check
    if(sarc_magic_number != sarc) {
        cerr << "[!] Error not a sarc archive file! " << file_path_in << endl;

        // Clean up un needed variables
        delete[] sarc_data;
        delete[] sarc_header;
        delete[] sfnt_entries;
        delete[] sfnt_header;
        delete[] sfat_entries;
        delete[] sfat_header;

        // Prevent dangling pointer
        sarc_data = nullptr;
        sarc_header = nullptr;
        sfnt_entries = nullptr;
        sfnt_header = nullptr;
        sfat_entries = nullptr;
        sfat_header = nullptr;
        
        return 1;
    }

    // Get magic number from header
    unsigned int sfat_magic_number = be_cast_int(sfat_header, 0x0);

    // Magic number check
    if(sfat_magic_number != sfat) {
        cerr << "[!] Error doesnt contain SFAT section! " << file_path_in << endl;

        // Clean up un needed variables
        delete[] sarc_data;
        delete[] sarc_header;
        delete[] sfnt_entries;
        delete[] sfnt_header;
        delete[] sfat_entries;
        delete[] sfat_header;

        // Prevent dangling pointer
        sarc_data = nullptr;
        sarc_header = nullptr;
        sfnt_entries = nullptr;
        sfnt_header = nullptr;
        sfat_entries = nullptr;
        sfat_header = nullptr;

        return 1;
    }

    // Get magic number from header
    unsigned int sfnt_magic_number = be_cast_int(sfnt_header, 0x0);

    // Magic number check
    if(sfnt_magic_number != sfnt) {
        cerr << "[!] Error doesnt contain SFNT section! " << file_path_in << endl;

        // Clean up un needed variables
        delete[] sarc_data;
        delete[] sarc_header;
        delete[] sfnt_entries;
        delete[] sfnt_header;
        delete[] sfat_entries;
        delete[] sfat_header;

        // Prevent dangling pointer
        sarc_data = nullptr;
        sarc_header = nullptr;
        sfnt_entries = nullptr;
        sfnt_header = nullptr;
        sfat_entries = nullptr;
        sfat_header = nullptr;

        return 1;
    }

    // Start iterating through each entry in sfat
    for(int sfat_pos = 0; sfat_pos < sfat_entries_size; sfat_pos += 0x10) {

        // Interpret data from entry and setup necessary variables
        unsigned int file_name_position = le_cast_short(sfat_entries, 0x4 + sfat_pos);
        file_name_position *= 4;

        unsigned int start_of_file = le_cast_int(sfat_entries, 0x8 + sfat_pos);
        unsigned int end_of_file = le_cast_int(sfat_entries, 0xC + sfat_pos);
        unsigned int file_size = end_of_file - start_of_file;

        string file_name, file_path;

        // Get whole file name
        for(int sfnt_pos = 0; sfnt_entries[file_name_position + sfnt_pos] != '\0'; sfnt_pos++) {
            file_name += sfnt_entries[file_name_position + sfnt_pos];
        }

        // Get file dir path
        for(int sfnt_pos = 0; sfnt_entries[file_name_position + sfnt_pos] != '/'; sfnt_pos++) {
            file_path += sfnt_entries[file_name_position + sfnt_pos];
        }

        // Create file path for files
        filesystem::path nested_path = folder_path_out + file_path + "/";
        filesystem::create_directories(nested_path);

        char *file = new char[file_size];

        // Read from raw data into file memory
        for(int sarc_pos = 0; sarc_pos < file_size; sarc_pos++) {
            file[sarc_pos] = sarc_data[start_of_file + sarc_pos];
        }

        // Open output stream for file
        ofstream output_stream(folder_path_out + file_name, ios::out | ios::binary);

        // If stream isnt open
        if(!output_stream.is_open()) {
            cerr << "[!] Error opening file: " << folder_path_out + file_name << endl;

            // Clean up un needed variables
            delete[] sarc_data;
            delete[] sarc_header;
            delete[] sfnt_entries;
            delete[] sfnt_header;
            delete[] sfat_entries;
            delete[] sfat_header;
            delete[] file;

            // Prevent dangling pointer
            sarc_data = nullptr;
            sarc_header = nullptr;
            sfnt_entries = nullptr;
            sfnt_header = nullptr;
            sfat_entries = nullptr;
            sfat_header = nullptr;
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

    // Clean up un needed variables
    delete[] sarc_data;
    delete[] sarc_header;
    delete[] sfnt_entries;
    delete[] sfnt_header;
    delete[] sfat_entries;
    delete[] sfat_header;

    // Prevent dangling pointer
    sarc_data = nullptr;
    sarc_header = nullptr;
    sfnt_entries = nullptr;
    sfnt_header = nullptr;
    sfat_entries = nullptr;
    sfat_header = nullptr;

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
