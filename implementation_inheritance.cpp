// Fahrudin Halilovic 

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cassert>


class FileHandler {

protected:
    // protected and non-virtual destructor for implementation inheritance
    ~FileHandler() = default;

public:

    std::string readFromFile(const std::filesystem::path& srcPath)
    {
        auto fs = open(srcPath, std::ios::in);
        if ( !fs ) {
            std::cout << "Something went wrong while opening the file!" << std::endl;
            return std::string { };
        }

        auto content = read(fs);
        close(fs);
        return content;
    }

    void writeToFile(const std::filesystem::path& destPath, const std::string& content)
    {
        auto fs = open(destPath, std::ios::out);
        if ( !fs ) {
            std::cout << "Something went wrong while opening the file!" << std::endl;
            return;
        }
        write(fs, content);
        close(fs);
    }

protected:

    virtual std::fstream open(const std::filesystem::path& src, std::ios_base::openmode mode)
    {
        return std::fstream { src, mode };
    }

    virtual std::string read(std::fstream& fs)
    {
        std::ostringstream content { };
        content << fs.rdbuf();
        return content.str();
    }

    virtual void write(std::fstream& fs, const std::string& content)
    {
        fs << content;
    }

    // mostly for demonstration purposes here
    virtual void close(std::fstream& fs)
    {
        fs.close();
    }
};

class RegularFileHandler : public FileHandler { };

class EncryptedFileHandler : public FileHandler  {

public:

    static std::string encrypt(const std::string& src)
    {
        std::string encrypted { };
        for( const auto& c : src ) {
            encrypted.push_back(c + 1);
        }
        return encrypted;
    }

    static std::string decrypt(const std::string& src)
    {
        std::string decrypted { };
        for( const auto& c : src ) {
            decrypted.push_back(c - 1);
        }
        return decrypted;
    }

protected:

    std::string read(std::fstream& fs) override
    {
        auto content = FileHandler::read(fs);
        return EncryptedFileHandler::decrypt(content);
    }

    void write(std::fstream& fs, const std::string& content) override
    {
        auto encrypted = EncryptedFileHandler::encrypt(content);
        FileHandler::write(fs, encrypted);
    }
};

class BinaryFileHandler : public FileHandler {

public:

    // 10MB
    static constexpr size_t MAX_SIZE = 10 * 1024 * 1024;

protected:

    std::fstream open(const std::filesystem::path& src, std::ios_base::openmode mode) override
    {
        // append binary flag here
        return std::fstream { src, mode | std::ios_base::binary };
    }

    void write(std::fstream& fs, const std::string& content) override
    {
        auto len = content.size();
        fs.write((const char*)&len, sizeof(len));
        fs.write(content.data(), len);
    }

    std::string read(std::fstream& fs) override
    {
        size_t len { 0 };
        if ( !fs.read((char *)&len, sizeof(len)) ) {
            throw std::runtime_error { "Unable to read the size of the string!" };
        }

        if ( len > MAX_SIZE ) {
            throw std::runtime_error { "Size of the string is too large!"};
        }

        std::string content { };
        content.resize(len);
        fs.read(content.data(), len);

        return content;
    }
};

int main()
{
    {
        auto testPath = std::filesystem::temp_directory_path() / "temp_1.txt";
        const std::string testStr { "test_1" };

        auto handler = std::make_shared<RegularFileHandler>();
        handler->writeToFile(testPath, testStr);

        assert(handler->readFromFile(testPath) == testStr);
    }

    {
        auto testPath = std::filesystem::temp_directory_path() / "temp_2.txt";
        const std::string testStr { "test_2" };

        auto handler = std::make_shared<EncryptedFileHandler>();
        handler->writeToFile(testPath, testStr);

        assert(handler->readFromFile(testPath) == testStr);
    }

    {
        auto testPath = std::filesystem::temp_directory_path() / "temp_3.bin";
        const std::string testStr { "test_3" };

        auto handler = std::make_shared<BinaryFileHandler>();
        handler->writeToFile(testPath, testStr);

        assert(handler->readFromFile(testPath) == testStr);
    }

    return 0;
}
