#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <string>

Napi::String CheckPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return Napi::String::New(env, "");
    }

    std::string username = info[0].As<Napi::String>().Utf8Value();
    LPUSER_INFO_1 ui = NULL;
    DWORD dwLevel = 1;
    NET_API_STATUS nStatus;

    // Convert std::string to LPCWSTR
    std::wstring wUsername(username.begin(), username.end());
    LPCWSTR lwUsername = wUsername.c_str();

    nStatus = NetUserGetInfo(NULL, lwUsername, dwLevel, (LPBYTE*)&ui);

    if (nStatus == NERR_Success) {
        std::wstring privilege;

        switch (ui->usri1_priv) {
            case USER_PRIV_ADMIN:
                privilege = L"Administrator";
                break;
            case USER_PRIV_USER:
                privilege = L"User";
                break;
            case USER_PRIV_GUEST:
                privilege = L"Guest";
                break;
            default:
                privilege = L"Unknown";
        }

        if (ui != NULL) {
            NetApiBufferFree(ui);
        }

        return Napi::String::New(env, std::string(privilege.begin(), privilege.end()));
    } else {
        return Napi::String::New(env, "Unknown");
    }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("checkPrivilege", Napi::Function::New(env, CheckPrivilege));
    return exports;
}

NODE_API_MODULE(addon, Init)
