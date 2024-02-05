#include "main.h"

int main() {
  // cout << registerUser();
  cout << loginUser();
  loginToken();
  // cout << showAllUser();
  // cout << showUser();
  cout << updateUser();

  return 0;
}
size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                     std::string *userp) {
  userp->append((char *)contents, size * nmemb);
  return size * nmemb;
}
std::string sendRequest(const std::string &method = "", const std::string &url="",
                        const std::string &postData = "",
                        const std::string &token = "") {
  CURL *curl;
  CURLcode res;
  std::string readBuffer;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(
        headers, "Content-Type: application/json"); // Add this line
    if (!token.empty()) {
      std::string authHeader = "Authorization: Bearer " + token;
      headers = curl_slist_append(headers, authHeader.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    if (!postData.empty()) {
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return readBuffer;
}
const string registerUser() {
  nlohmann::json registerData;
  registerData["name"] = "Andreas";
  registerData["username"] = "Andreas1";
  registerData["email"] = "andreas123@gmail.com";
  registerData["password"] = "password";
  registerData["password_confirmation"] = "password";
  nlohmann::json send_POST;
  send_POST["user"] = registerData;
  auto result =
      sendRequest("POST", "http://localhost:3000/users", send_POST.dump());
  return result;
}
const string loginUser() {
  nlohmann::json loginData;
  loginData["email"] = "andreas123@gmail.com";
  loginData["password"] = "password";
  auto result =
      sendRequest("POST", "http://localhost:3000/auth/login", loginData.dump());
  return result;
}
const string showAllUser() {
  auto all_user =
      sendRequest("GET", "http://localhost:3000/users", "", loginToken());
  return all_user;
}
const string showUser() {
  nlohmann::json show_user;
  show_user["username"] = "Andreas1";
  auto user_result =
      sendRequest("GET", "http://localhost:3000/Andreas1", "", loginToken());
  return user_result;
}
const string loginToken() {
  auto login_token = nlohmann::json::parse(loginUser());
  auto token = login_token["token"];
  return token;
}
const string updateUser() {
  nlohmann::json updateData;
  updateData["name"] = "Andreas";
  updateData["password"] = "password1";
  updateData["email"] = "andreassan@gmail.com";
  nlohmann::json send_PATCH;
  send_PATCH["user"] = updateData;
  auto update_result =
      sendRequest("PATCH", "http://localhost:3000/users/Andreas1",
                  send_PATCH.dump(), loginToken());
  return update_result;
}
