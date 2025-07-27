#include <filesystem>
#include <string>
#include <codecvt>
#include <locale>  

class Copy {
public:
    Copy(std::filesystem::path source, std::filesystem::path destination)
        : source_(std::move(source)), destination_(std::move(destination)) {}
    
    Copy& materialize() const {
        Text source_file(source_);
        Directory dest_dir(destination_.parent_path());
        WritableText dest_file(destination_);
        if (!source_file.exists()) {
            throw std::runtime_error("Source file does not exist: " + source_.string());
        }
        dest_dir.ensure();
        dest_file.write(source_file.content());
        
        return *const_cast<Copy*>(this);
    }

    Copy to(std::filesystem::path new_destination) const {
        return Copy(source_, std::move(new_destination));
    }
    
    Copy from(std::filesystem::path new_source) const {
        return Copy(std::move(new_source), destination_);
    }

private:
    const std::filesystem::path source_;
    const std::filesystem::path destination_;
};
