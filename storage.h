#ifndef STORAGE_H
#define STORAGE_h

#include <vector>
#include <string>

struct Record
{
    std::string key;
    std::string value;
    bool is_deleted;
};

class Storage
{
public:
    Storage(const std::string &filename);

    long append(const std::string &key, const std::string &value);
    std::vector<std::pair<long, Record>> scan_all();

private:
    std::string filename;
};

#endif