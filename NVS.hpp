#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

/**
 * @brief NVS (Non-Volatile Storage) class for managing key-value pairs in ESP32's NVS.
 * note: call NVS::initialize() before using this class to ensure NVS is initialized.
 */

struct NVS_entry_info {
    std::string key;
    nvs_type_t type;
};

class NVS
{
private:
    nvs_handle_t handle;
    NVS();
    ~NVS();

public:
    static void initialize();
    static NVS &getInstance();

    void setInt32(const std::string &key, int32_t value);
    int32_t getInt32(const std::string &key);

    void eraseKey(const std::string &key);
    void eraseAll();

    bool keyExists(const std::string &key);
    std::vector<NVS_entry_info> getAllEntriesInfo();
    
    int32_t operator[](const std::string &key);
    NVS(const NVS &) = delete;
    void operator=(const NVS &) = delete;
};
