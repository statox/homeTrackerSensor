#define CONFIG_API_HOSTNAME "api.statox.fr"
#define CONFIG_SLEEP_SECONDS 60 * 10
#define CONFIG_SENSOR_NAME "dev-sensor"

// One of these must be defined
// #define MAIN_SENSOR_BME
// #define MAIN_SENSOR_DHT
#define MAIN_SENSOR_SHT

// Indicate that the board has 2 sensors and one of
// them is used to monitor inside of the enclosure
#define HAS_INTERNAL_SENSOR

// Only one DHT sensor by board is supported
// (which is fine I don't expect to have boards with 2 DHTs)
#define DHTPIN A1     // Pin used to read the DHT sensor
#define DHTTYPE DHT11 // DHT11 or DHT22
