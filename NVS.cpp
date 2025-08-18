#include "NVS.hpp"


void NVS::initialize()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

NVS::NVS()
{
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &handle));
    ESP_LOGI("NVS", "NVS initialized successfully.");
}

NVS::~NVS()
{
    nvs_close(handle);
    ESP_LOGI("NVS", "NVS closed successfully.");
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
    nvs_iterator_t it = nullptr;
    esp_err_t res = nvs_entry_find_in_handle(handle, NVS_TYPE_ANY, &it);

    while (res == ESP_OK) {
        nvs_entry_info_t info;
        if (nvs_entry_info(it, &info) == ESP_OK) {
            if (key == info.key) {
                nvs_release_iterator(it);
                return true;
            }
        }
        res = nvs_entry_next(&it);
    }
    nvs_release_iterator(it);
    return false;
}

int32_t NVS::operator[](const std::string &key)
{
    return getInt32(key);
}