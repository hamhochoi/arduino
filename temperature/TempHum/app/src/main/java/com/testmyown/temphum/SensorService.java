package com.testmyown.temphum;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.IBinder;
import android.os.ResultReceiver;
import android.support.annotation.Nullable;
import android.util.Log;

import com.testmyown.temphum.data.model.Weather;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;


/**
 * Created by fabio on 30/01/2016.
 */
public class SensorService extends Service {
    public int counter=0;
    ResultReceiver resultReceiver;
    public Weather weather = new Weather(1.0, 1.0);
    String host;
    String port;


    public SensorService(Context applicationContext) {
        super();
        Log.i("HERE", "here I am!");
    }

    public SensorService() {
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        resultReceiver = intent.getParcelableExtra("receiver");
        host = intent.getStringExtra("host");
        port = intent.getStringExtra("port");
        startTimer();

        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i("EXIT", "ondestroy!");
        Intent broadcastIntent = new Intent("uk.ac.shef.oak.ActivityRecognition.RestartSensor");
        sendBroadcast(broadcastIntent);
        stoptimertask();
    }

    private Timer timer;
    private TimerTask timerTask;

    public void startTimer() {
        //set a new Timer
        timer = new Timer();
        //initialize the TimerTask's job
        initializeTimerTask();
        //schedule the timer, to wake up every 1 second
        timer.schedule(timerTask, 1000, 1000); //
    }

    /**
     * it sets the timer to print the counter every x seconds
     */
    public void initializeTimerTask() {
        timerTask = new TimerTask() {
            public void run() {
                //Log.i("in timer", "in timer ++++  "+ (counter++));
                //GetWeatherInfor();
                Bundle bundle = new Bundle();

                try {
                    String urlString;
                    if (port != "") {
                        urlString = "http://" + host + ":" + port + "/weather";
                        Log.e("urlString: ", urlString);
                    } else {
                        urlString = "htt://" + host + "/weather";
                        Log.e("urlString: ", urlString);
                    }


                    URL url = new URL(urlString);

                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();

                    connection.setRequestMethod("GET");
                    System.out.println("connection inputStream: " + connection.getInputStream());

                    BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                    String line;

                    StringBuilder responseOutput = new StringBuilder();
                    while((line = br.readLine()) != null ) {
                        System.out.println("line " + line);
                        responseOutput.append(line);
                    }
                    br.close();

                    JSONObject weatherObject = new JSONObject(responseOutput.toString());

                    weather.temperature = weatherObject.getDouble("temperature");
                    weather.humidity = weatherObject.getDouble("humidity");
                    bundle.putString("temperature", String.valueOf(weather.temperature));
                    bundle.putString("humidity", String.valueOf(weather.humidity));
                    resultReceiver.send(200, bundle);
                    Log.e("temperature", String.valueOf(weather.temperature));

                } catch (MalformedURLException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        };
    }

    /**
     * not needed
     */
    public void stoptimertask() {
        //stop the timer, if it's not already null
        if (timer != null) {
            timer.cancel();
            timer = null;
        }
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}