#include <curl/curl.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>


std::string webhook_url = "youwehbookurl";
std::string yoda_avatar = "https://media.anakinworld.com/uploads/entries/original/personnage-yoda.jpg";
std::string storm_avatar = "https://www.pngarts.com/files/6/Star-Wars-Stormtrooper-Helmet-PNG-Image.png";
std::string jedi_avatar = "https://lumiere-a.akamaihd.net/v1/images/ahmed-best-kelleran-beq-featured_404adce1.jpeg?region=0,0,1600,900&width=960";
std::string dark_vador_avatar = "https://www.burnleyexpress.net/images-i.jpimedia.uk/imagefetch/https://jpgreatcontent.co.uk/wp-content/uploads/2019/10/shutterstock_239009761.jpg?width=1200&enable=upscale";
class Yoda {
public:
    std::string repliques[15] = {
        "Fais-le ou ne le fais pas, mais il n'y a pas d'essai.",
        "Le plus grand professeur, l'échec est.",
        "L'aventure, c'est la découverte de soi.",
        "Je ne suis pas jeune, mais la force est toujours avec moi.",
        "Le véritable fardeau est de trop posséder.",
        "La peur est le chemin vers le côté obscur : la peur mène à la colère, la colère mène à la haine, la haine... mène à la souffrance.",
        "L'espoir est la première étape sur la route de la déception.",
        "Une vision vous devez avoir.",
        "Votre arme, vous ne la perdrez pas. Elle est votre vie.",
        "Que la force soit avec toi.",
        "De nombreux éléments, la Force a. Nourriture, énergie, une essence spirituelle...",
        "Il ne faut pas trop penser. Ca n'est jamais bon pour la santé mentale.",
        "Je suis avec vous.",
        "La patience vous devez avoir, jeune Padawan.",
        "Seul le Sith pense en absolus."
    };
};

class Jedi {
public:
    std::string repliques[15] = {
        "Le calme est une vertu que l'on doit cultiver.",
        "Un Jedi doit toujours faire ce qui est juste, même si cela signifie le sacrifice de sa propre vie.",
        "La patience est le chemin qui mène à la sagesse.",
        "Le pouvoir de la Force est une arme dangereuse, il doit être utilisé avec prudence.",
        "La Force est un cadeau, et nous devons l'utiliser pour aider les autres.",
        "Un Jedi doit écouter sa conscience, même si cela signifie aller à l'encontre des ordres.",
        "La Force est avec nous, mais elle ne peut pas faire le travail à notre place.",
        "La peur est notre ennemie, nous devons la surmonter.",
        "Le doute est naturel, mais nous ne devons pas le laisser nous submerger.",
        "La Force est notre alliée, nous ne devons pas l'utiliser à des fins égoïstes.",
        "La connaissance est la clé qui ouvre toutes les portes.",
        "Nous devons être prêts à sacrifier notre propre bonheur pour aider les autres.",
        "La Force nous guide, mais nous devons faire nos propres choix.",
        "Un Jedi ne doit jamais abandonner.",
        "La guerre est un fléau, nous devons faire tout notre possible pour la prévenir."
    };
};

class Stormtrooper {
public:
    std::string repliques[15] = {
        "Recherche terminée, monsieur.",
        "Dans l'Empire, nous n'avons pas de place pour les faibles.",
        "Je dois vous emmener devant le commandant.",
        "Bientôt, l'Empire régnera sur cette galaxie.",
        "Je suis désolé, monsieur, il ne peut pas venir.",
        "L'Empire offre la sécurité et la stabilité.",
        "Je vais répéter : libérez-les.",
        "Je n'ai pas de nom. Je suis un numéro de série.",
        "Ce sont les droïdes que nous recherchons.",
        "J'ai ordre de ne pas blesser les prisonniers.",
        "Vous ne pouvez pas nous échapper.",
        "Vous avez mal choisi votre camp.",
        "Vous êtes de plus en plus audacieux.",
        "Je vais vous donner une dernière chance de vous rendre.",
        "Nous controlons le Discord."
    };
};

class DarkVador {
public:
    std::string repliques[15] = {
        "Je suis ton père.",
        "La peur est une arme puissante.",
        "Le pouvoir de la Force est inégalé.",
        "Tu n'as pas encore réalisé ton plein potentiel.",
        "La Force est forte en toi, mais tu as besoin d'un peu plus de formation.",
        "Tu es faible, comme ton père l'était.",
        "La loyauté est essentielle à la survie.",
        "Le sacrifice est parfois nécessaire pour obtenir ce que nous voulons.",
        "La rébellion ne peut être tolérée.",
        "La galaxie doit être soumise à l'Empire.",
        "La Force est notre alliée, mais elle doit être contrôlée.",
        "Les faibles doivent être éliminés pour que les forts puissent prospérer.",
        "La colère est notre alliée, elle nous donne la force de vaincre nos ennemis.",
        "La mort est une partie naturelle de la vie.",
        "Seul le plus fort peut survivre dans cette galaxie impitoyable."
    };
};



void send_message(std::string username, std::string avatar, std::string message)
{
    CURL *curl;
    CURLcode res;

    // Définir les variables


    // Initialiser cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        // Définir l'URL de votre webhook
        curl_easy_setopt(curl, CURLOPT_URL, webhook_url.c_str());
        // Définir que nous effectuons une requête POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Définir les en-têtes de la requête
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Définir le contenu de la requête
        std::string json_data = "{\"content\":\"" + message + "\",\"username\":\"" + username + "\",\"avatar_url\":\"" + avatar + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());

        // Envoyer la requête
        res = curl_easy_perform(curl);

        // Nettoyer les en-têtes et terminer cURL
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();


}
int main(int argc, char* argv[])
{
    // Vérifier que nous avons au moins 4 arguments (nom du programme, URL du webhook, nom d'utilisateur et contenu du message)
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <invasion/yoda/vador/jedi/rex/auto>" << std::endl;
        return 1;
    }
    Yoda yoda;
    Stormtrooper stormtrooper;
    DarkVador darkvador;
    Jedi jedi;

    std::srand(std::time(nullptr));
    
    if(std::strcmp(argv[1], "rex") == 0) {
        send_message("Rex", "https://static.wikia.nocookie.net/hunterxhunter/images/0/05/Hunter_Association_logo.png/revision/latest?cb=20180405075402", "Il y a bien longtemps, dans une galaxie lointaine, très lointaine...");
    }
    else if(std::strcmp(argv[1], "invasion") == 0) {
        for(int i = 0; i < 7; i++) {
            send_message("Stormtrooper", storm_avatar, stormtrooper.repliques[std::rand() % 15]);
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    else if(std::strcmp(argv[1], "yoda") == 0) {
        send_message("Yoda", yoda_avatar, yoda.repliques[std::rand() % 16]);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
    }
    else if(std::strcmp(argv[1], "vador") == 0) {
        send_message("Dark Vador", dark_vador_avatar, darkvador.repliques[std::rand() % 15]);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    else if(std::strcmp(argv[1], "jedi") == 0) {
        send_message("Jedi", jedi_avatar, jedi.repliques[std::rand() % 6]);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    else if(std::strcmp(argv[1], "auto") == 0){
        send_message("Rex", "https://static.wikia.nocookie.net/hunterxhunter/images/0/05/Hunter_Association_logo.png/revision/latest?cb=20180405075402", "Il y a bien longtemps, dans une galaxie lointaine, très lointaine...");
        while(true) {
            int random_perso = std::rand() % 4;
            switch (random_perso) {
                case 0:
                    send_message("Stormtrooper", storm_avatar, stormtrooper.repliques[std::rand() % 15]);
                    break;
                case 1:
                    send_message("Yoda", yoda_avatar, yoda.repliques[std::rand() % 16]);
                    break;
                case 2:
                    send_message("Dark Vador", dark_vador_avatar, darkvador.repliques[std::rand() % 15]);
                    break;
                case 3:
                    send_message("Jedi", jedi_avatar, jedi.repliques[std::rand() % 6]);
                    break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(95));
        }
    }
}
