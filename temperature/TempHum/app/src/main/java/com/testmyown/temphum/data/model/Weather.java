package com.testmyown.temphum.data.model;

/**
 * Created by ledinhduy on 17/09/2017.
 */

public class Weather {
    public double temperature;
    public double humidity;

    public Weather(double temperature, double humidity) {
        this.temperature = temperature;
        this.humidity = humidity;
    }

    public Weather() {

    }
}
