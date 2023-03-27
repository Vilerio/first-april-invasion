#include <iostream>
#include <curl/curl.h>
#include "json.hpp"

int main()
{
    std::string webhook_url = "https://discord.com/api/webhooks/1089850495771889735/zWTKPYGHCgOSjtr15c2OdWANYEPO_yjQohm5p_vFeBF0CYgo5QxYUApgM4VliMQSa7s9";

    std::string new_username = "My New Webhook Username";
    std::string new_avatar_url = "https://static.vecteezy.com/system/resources/previews/019/493/370/original/chatgpt-logo-openai-logo-ai-chatbot-chatgpt-copy-space-text-editorial-illustration-free-vector.jpg";

    // Créer un objet JSON avec les nouvelles informations du webhook
    nlohmann::json json_data;
    json_data["name"] = new_username;
    json_data["avatar_url"] = new_avatar_url;

    // Convertir l'objet JSON en chaîne de caractères
    std::string json_str = json_data.dump();

    // Initialiser cURL
    CURL* curl = curl_easy_init();
    if (curl)
    {
        // Configurer les options de la requête POST
        curl_easy_setopt(curl, CURLOPT_URL, webhook_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_str.size());

        // Exécuter la requête POST
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "Erreur lors de la mise à jour des informations du webhook : " << curl_easy_strerror(res) << std::endl;
        }

        // Nettoyer cURL
        curl_easy_cleanup(curl);
    }

    return 0;
}
