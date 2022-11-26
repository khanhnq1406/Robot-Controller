/************************* WiFi Access Point *********************************/

struct WifiConfig {
  // Home
  const char* homeSsid = "Moc My";
  const char* homePassword = "123456789";
  // Boarding House
  const char* boardingSsid = "TP-LINK_D7E0";
  const char* boardingPassword = "79377393";
  // Yana Coffee
  const char* yanaSsid = "Yana Coffee Tang1";
  const char* yanaPassword = "184hoangdieu2";
  // an
  const char* AnSsid = "an123";
  const char* AnPassword = "1237894567";
};
struct WifiConfig wifiConfig;
#define WIFI_SSID       wifiConfig.homeSsid
#define WIFI_PASSWORD   wifiConfig.homePassword

#define FIREBASE_HOST "https://robot-controller-71ebb-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "AIzaSyAGSoXB8u6OYhbO7Jb_YHMrQTOyec7Tcvo"