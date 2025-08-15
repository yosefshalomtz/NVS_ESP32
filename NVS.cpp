#include "NVS.hpp"


NVS::NVS()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &handle));
    std::cout << "NVS::NVS(): NVS initialized." << std::endl;
}

NVS::~NVS()
{
    nvs_close(handle);
    std::cout << "NVS::~NVS(): NVS closed." << std::endl;
}

NVS& NVS::getInstance()
{
    static NVS instance;
    return instance;
}

void NVS::setInt32(const std::string &key, int32_t value)
{
    ESP_ERROR_CHECK(nvs_set_i32(handle, key.c_str(), value));
    ESP_ERROR_CHECK(nvs_commit(handle));
}

int32_t NVS::getInt32(const std::string &key)
{
    int32_t value = 0;
    nvs_get_i32(handle, key.c_str(), &value);
    return value;
}

void NVS::eraseKey(const std::string &key)
{
    ESP_ERROR_CHECK(nvs_erase_key(handle, key.c_str()));
    ESP_ERROR_CHECK(nvs_commit(handle));
}

void NVS::eraseAll()
{
    ESP_ERROR_CHECK(nvs_erase_all(handle));
    ESP_ERROR_CHECK(nvs_commit(handle));
}

bool NVS::keyExists(const std::string &key)
{
    nvs_type_t type;
    esp_err_t err = nvs_get_type(handle, key.c_str(), &type);
    return err == ESP_OK;
}

int32_t NVS::operator[](const std::string &key)
{
    return getInt32(key);
}