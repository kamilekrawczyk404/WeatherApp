//
// Created by Kamil Krawczyk on 22/05/2024.
//

#include "TranslationAPI.h"

TranslationAPI::TranslationAPI(nlohmann::json &values, std::string targetLanguage) : FetchAPI() {
    std::string  
        url = "https://api-free.deepl.com/v2/translate",
        postFields = "{\"text\": ";
    
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: DeepL-Auth-Key " + DEEPL_API_KEY).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    postFields += to_string(values);
    postFields += (", \"target_lang\": \"" + targetLanguage + "\"}");

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());
    
    fetchData();
    
    // catch only translated words
    nlohmann::json partial;
    for(auto &[key, value] : fetchedData["translations"].items()) {
        // spaces need to be replaced by the new line character
        std::string  text = value["text"];
        std::replace(text.begin(), text.end(), ' ', '\n');
        
        partial.push_back(text);
    }
    
    fetchedData = partial;
}
