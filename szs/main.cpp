#include <iostream>
#include <fstream>
#include <filesystem>
#include "../utils/utils.hpp"

#define szs 1499560496

using namespace std;

int decompress_szs(string file_path_in, string file_path_out) {

    // Create file stream for compressed data
    ifstream input_stream(file_path_in, ios::in | ios::ate | ios::binary);

    // If the file stream isnt open
    if(!input_stream.is_open()) {
        cerr << "[!] Error reading from file: " << file_path_in << endl;
        return 1;
    }

    // Get file size and allocate memory for contents
    unsigned int szs_header_size = 16; 
    unsigned int szs_data_size =  input_stream.tellg();
    szs_data_size -= szs_header_size;

    // Allocate array in memory for file contents
    char *szs_header = new char[szs_header_size];
    char *szs_data = new char[szs_data_size];

    // Go back to begining of file
    input_stream.seekg(0, ios::beg);

    // Read contents of file header and contents into memory
    input_stream.read(szs_header, szs_header_size);
    input_stream.read(szs_data, szs_data_size);

    // Close file stream
    input_stream.close();

    // Interpret header data
    unsigned int szs_magic_number = be_cast_int(szs_header, 0x0);
    unsigned int sarc_data_size = be_cast_int(szs_header, 0x4);

    // Magic number check
    if(szs_magic_number != szs) {
        cerr << "[!] Error not a szs encoded file! " << file_path_in << endl;

        // Clean up variables
        delete[] szs_header;
        delete[] szs_data;

        // Prevent dangling pointer
        szs_header = nullptr;
        szs_data = nullptr;

        return 1;
    }

    // Create buffer for destination file
    char *sarc_data = new char[sarc_data_size];

    // Create variables needed for decompression
    unsigned int valid_bits_left = 0;
    unsigned int sarc_data_pos = 0;
    unsigned int szs_data_pos = 0;
    unsigned char current_code_byte;

    // Start Decompressing the data
    while(sarc_data_pos < sarc_data_size) {

        // If there are no more valid bits, read next byte in uncompressed data and update valid bits
        if(valid_bits_left == 0) {
            current_code_byte = szs_data[szs_data_pos];
            ++szs_data_pos;
            valid_bits_left = 8;
        }

        // If current code byte has a data copy bit set to one, copy data from source to destination
        if((current_code_byte & 0x80) != 0) {
            sarc_data[sarc_data_pos] = szs_data[szs_data_pos];
            sarc_data_pos++;
            szs_data_pos++;
        }

        // Run Length Encoding Part
        else {
            unsigned int pair_part_one = (unsigned int)(unsigned char) szs_data[szs_data_pos];
            unsigned int pair_part_two = (unsigned int)(unsigned char) szs_data[szs_data_pos + 1];
            szs_data_pos += 2;

            unsigned int distance = ((pair_part_one & 0xF) << 8) | pair_part_two;
            unsigned int sarc_data_copy_pos = sarc_data_pos - (distance + 1);
            unsigned int number_of_bytes = pair_part_one >> 4;

            // If number of bytes is zero, read next byte and add 0x12 to fix count
            if(number_of_bytes == 0) {
                number_of_bytes = (unsigned int)(unsigned char) szs_data[szs_data_pos];
                number_of_bytes += 0x12;
                szs_data_pos++;
            } else {
                number_of_bytes += 2;
            }

            // Start reading from source to destination for i number of bytes
            for(int i = 0; i < number_of_bytes; ++i) {
                sarc_data[sarc_data_pos] = sarc_data[sarc_data_copy_pos];
                sarc_data_copy_pos++;
                sarc_data_pos++;
            }
        }
        
        // Move to next code byte and decrement the ammount of valid bits
        current_code_byte <<= 1;
        valid_bits_left -= 1;
    }

    // Bit of a hack to get folder paths
    string folder_path_out = file_path_out.substr(0, file_path_out.rfind('/'));

    // Create file path for file
    filesystem::path nested_path = folder_path_out;
    filesystem::create_directory(nested_path);

    // Open output file stream to file
    ofstream output_stream(file_path_out, ios::out | ios::binary);

    // If files tream isnt open
    if(!output_stream.is_open()) {
        cerr << "[!] Error writing to file: " << file_path_out << endl;

        // Clean up variables
        delete[] szs_header;
        delete[] szs_data;
        delete[] sarc_data;

        // Prevent dangling pointer
        szs_header = nullptr;
        szs_data = nullptr;
        sarc_data = nullptr;

        return 1;
    }

    // Write out decompressed data and close stream
    output_stream.write(sarc_data, sarc_data_size);
    output_stream.close();

    // Clean up variables
    delete[] szs_header;
    delete[] szs_data;
    delete[] sarc_data;

    // Prevent dangling pointer
    szs_header = nullptr;
    szs_data = nullptr;
    sarc_data = nullptr;

    cout << file_path_in << " -> " << file_path_out << endl;

    return 0;
}

int main() {

    decompress_szs("systemData/common.szs","systemDataDecompressed/common.arc");
    decompress_szs("systemData/Entrance.szs","systemDataDecompressed/Entrance.arc");
    decompress_szs("systemData/Eula.szs","systemDataDecompressed/Eula.arc");
    decompress_szs("systemData/Flaunch.szs","systemDataDecompressed/Flaunch.arc");
    decompress_szs("systemData/Gift.szs","systemDataDecompressed/Gift.arc");
    decompress_szs("systemData/Interrupt.szs","systemDataDecompressed/Interrupt.arc");
    decompress_szs("systemData/Migration.szs","systemDataDecompressed/Migration.arc");
    decompress_szs("systemData/MyPage.szs","systemDataDecompressed/MyPage.arc");
    decompress_szs("systemData/Notification.szs","systemDataDecompressed/Notification.arc");
    decompress_szs("systemData/Option.szs","systemDataDecompressed/Option.arc");
    decompress_szs("systemData/Psl.szs","systemDataDecompressed/Psl.arc");
    decompress_szs("systemData/ResidentMenu.szs","systemDataDecompressed/ResidentMenu.arc");
    decompress_szs("systemData/SaveMove.szs","systemDataDecompressed/SaveMove.arc");
    decompress_szs("systemData/Set.szs","systemDataDecompressed/Set.arc");

    return 0;
}
