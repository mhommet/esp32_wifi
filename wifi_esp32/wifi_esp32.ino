#include <WiFi.h>

// SSID du hotspot et mot de passe initial
const char* apSSID = "wifi_m2dfs_milan";
char apPassword[32];  // Stocke le mot de passe actuel du hotspot

// Liste des mots de passe possibles
const char* passwords[] = {
        "kxzvaajn", "nulebozl", "sylmukyv", "fzxhzodw", "mnhfwylw", "xhnvtwdd", "jrulvtsp", "ochdamfa", "plaluafr", "ovnkkilc",
        "oizuxgas", "tjrdbrav", "pklzocye", "vtapalxp", "rtagjdnv", "frvuyeoe", "xghgxava", "rgolvnna", "yfxeqlny", "aewazmzb",
        "shsiejiu", "iuvmohlb", "cjvxdfsl", "qpikserq", "utacmzqp", "ooxevhdn", "sxthtwxj", "llrwdkcx", "ddudifar", "zphrewdm",
        "mpdkrxev", "updhshlc", "tllzdwkl", "riyypzdz", "oemqckth", "tffobpzd", "gtffxvfi", "txjtdwqy", "jfiqxhca", "sgypghxn",
        "juixjinr", "aowreqdu", "swjeitqz", "igjautba", "aiyqeglh", "oswyyore", "xptdcttd", "pcprabke", "kmqzndiw", "dpqzamtm",
        "dyzcslls", "navqcfvd", "anowzypk", "suahetlj", "yfhccclh", "qbmdivqr", "qblucjky", "dguzkxel", "ylpyzgjf", "kbfcdujc",
        "ctuqkrdr", "ajevmebu", "skmcsqfz", "ffzlwiio", "aftglkvf", "xxdgtzlw", "cvlfsunn", "bhdvmvku", "nfqzutau", "ggxbhrho",
        "qyfalgmh", "tcxkbhrn", "qpogobwf", "cllvemtd", "vthbmclx", "mygnkqqa", "whfrjrlf", "gwfeqkgf", "fkvgcrjw", "lezddzaj",
        "xvczgqaa", "iekrpdyj", "ebkftonw", "eoudylkl", "ebxoxxfm", "janmvljn", "xfudqipe", "yuyfhefw", "irxkfjbq", "kwdvygqs",
        "yvhsdunb", "qhqzskuo", "nkcuqjjx", "treyrebr", "iubgkumg", "iqeblqrp", "awllfhdq", "ywbvnsvp", "eqivzdwz", "feskhshm",
        "fytbaolk", "lnqguosc", "mplxzpwm", "vsedeanw", "rvcnmtqq", "fsptuhkw", "pmjuvole", "fxwnbwxl", "rnkilsjh", "uqpkhdhl"
    };
const int numPasswords = sizeof(passwords) / sizeof(passwords[0]);

void changeHotspotPassword() {
    int randomIndex = random(0, numPasswords);
    strncpy(apPassword, passwords[randomIndex], sizeof(apPassword) - 1);
    apPassword[sizeof(apPassword) - 1] = '\0';

    WiFi.softAP(apSSID, apPassword);  // Met à jour le hotspot avec un nouveau mot de passe
    Serial.printf("Hotspot password changed to: %s\n", apPassword);
}

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case WIFI_EVENT_AP_STACONNECTED:
            Serial.println("Client connected, changing password...");
            changeHotspotPassword();
            break;

        case WIFI_EVENT_AP_STADISCONNECTED:
            Serial.println("Client disconnected");
            break;

        default:
            break;
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Setting up Wi-Fi access point...");

    randomSeed(analogRead(0)); // Initialise la génération de nombres aléatoires
    changeHotspotPassword(); // Définit un mot de passe initial aléatoire

    WiFi.onEvent(WiFiEvent); // Écoute les événements Wi-Fi
    WiFi.softAP(apSSID, apPassword);

    Serial.print("Access Point IP address: ");
    Serial.println(WiFi.softAPIP());
}

void loop() {
    scanAndConnect();
    delay(30000); // Attendre 30 secondes avant de refaire un scan
}

void scanAndConnect() {
    Serial.println("🔍 Scanning for Wi-Fi networks...");

    int numNetworks = WiFi.scanNetworks();
    if (numNetworks == -1) {
        Serial.println("❌ Error during Wi-Fi scan");
        return;
    }

    Serial.printf("✅ Found %d networks:\n", numNetworks);

    // Filtrer les SSID qui correspondent à "wifi_m2dfs_****"
    String targetSSIDs[numNetworks];
    int targetCount = 0;

    for (int i = 0; i < numNetworks; i++) {
        String ssid = WiFi.SSID(i);
        if (ssid.startsWith("wifi_m2dfs_")) {
            targetSSIDs[targetCount++] = ssid;
        }
    }

    Serial.printf("🔒 Found %d target networks matching 'wifi_m2dfs_****'\n", targetCount);

    if (targetCount == 0) {
        Serial.println("❌ No matching networks found.");
        return;
    }

    // Essayer chaque mot de passe sur tous les réseaux avant de passer au suivant
    for (int j = 0; j < numPasswords; j++) {
        Serial.printf("🔑 Trying password: %s on all networks\n", passwords[j]);

        for (int i = 0; i < targetCount; i++) {
            Serial.printf("💻 Trying to connect to %s with password %s...\n", targetSSIDs[i].c_str(), passwords[j]);

            WiFi.begin(targetSSIDs[i].c_str(), passwords[j]);
            unsigned long startTime = millis();

            while (millis() - startTime < 10000) { // Timeout de 10 sec
                if (WiFi.status() == WL_CONNECTED) {
                    Serial.printf("🎉 Connected successfully to %s!\n", targetSSIDs[i].c_str());
                    Serial.printf("🌐 IP Address: %s\n", WiFi.localIP().toString().c_str());
                    return; // Stopper dès qu'une connexion réussit
                }
                delay(500);
            }

            Serial.println("❌ Incorrect password! Trying next... 🔄");
            WiFi.disconnect();
            delay(4000); // Délai de 4 secondes avant de tester le prochain réseau
        }
    }

    WiFi.scanDelete(); // Libère la mémoire après le scan
}

