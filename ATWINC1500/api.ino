void postSensorData(
    String sensorName,

    float dhtCelsius,
    float dhtHumidity,

    float batteryCharge,
    float batteryPercent
) {
    String path = "/homeTracker/upload";
    String url = "http://" + String(CONFIG_API_HOSTNAME) + path;

    JsonDocument doc;
    doc["sensorName"] = sensorName;

    doc["tempCelsius"] = dhtCelsius;
    doc["humidity"] = dhtHumidity;

    doc["batteryCharge"] = batteryCharge;
    doc["batteryPercent"] = batteryPercent;

    httpPOSTRequest(url, doc);
}
