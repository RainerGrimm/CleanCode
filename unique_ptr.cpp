// Fahrudin Halilović

#include <fstream>
#include <filesystem>
#include <memory>
#include <cassert>

namespace fs = std::filesystem;

class FileHandle {
public:
    using UPtr = std::unique_ptr<FileHandle>;

    explicit FileHandle(fs::path p)
    {
        // handle differences between WIN and Linux
        // if the file does not exist then std::ios::out on Linux
        // will not create empty file thus we manually check for that
        if ( !fs::exists(p) ) {
            std::ofstream tempStream { p };
        }

        stream = std::fstream { std::move(p), std::ios::in | std::ios::out };

        if ( !stream ) {
            // if stream still could not be created e.g. due to the invalid path
            // or insufficient permissions, we cannot continue 
            throw std::runtime_error { "File could not be opened!" };
        }
    }

    std::string read(size_t length)
    {
        std::string result (length, '\0');
        stream.read(result.data(), length);
        if ( stream.gcount() != length ) {
            result.resize(stream.gcount());
        }
        return result;
    }

    void write(const std::string& content)
    {
        stream.write(content.data(), content.size());
    }

private:
    std::fstream stream;
};

void writeContent(FileHandle::UPtr handle, const std::string& content)
{
    handle->write(content);
}

std::string readContent(FileHandle::UPtr handle, size_t length)
{
    return handle->read(length);
}

int main()
{
    const auto path = fs::temp_directory_path() / "test.txt";

    {
        auto writeFileHandle = std::make_unique<FileHandle>(path);
        writeContent(std::move(fileHandle), "test1234");
    }

    {
        auto readFileHandle = std::make_unique<FileHandle>(path);
        const auto content = readContent(std::move(fileHandle), 8u);
        assert(content == "test1234");
    }

    return 0;
}