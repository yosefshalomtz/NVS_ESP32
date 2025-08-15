#pragma once
#include <iostream>
#include <string>
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

class NVS
{
private:
    nvs_handle_t handle;
    NVS();
    ~NVS();

public:
    static NVS &getInstance();

    void setInt32(const std::string &key, int32_t value);
    int32_t getInt32(const std::string &key);
    void eraseKey(const std::string &key);
    void eraseAll();
    bool keyExists(const std::string &key);
    int32_t operator[](const std::string &key);
    NVS(const NVS &) = delete;
    void operator=(const NVS &) = delete;
};
