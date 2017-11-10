package com.testmyown.temphum;

import android.app.ActivityManager;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.ResultReceiver;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class TempHumActivity extends AppCompatActivity {

    String host;
    String port;
    Intent mServiceIntent;
    private SensorService mSensorService;
    Context ctx;
    TextView temperatureView;
    TextView humidityView;
    public Context getCtx() {
        return ctx;
    }
    MyResultReceiver resultReceiver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ctx = this;
        setContentView(R.layout.activity_temp_hum);

        Intent intent = getIntent();
        host = intent.getStringExtra("host");
        port = intent.getStringExtra("port");


        temperatureView =  (TextView) findViewById(R.id.temperature);
        humidityView = (TextView) findViewById(R.id.humidity);
        mSensorService = new SensorService(getCtx());
        mServiceIntent = new Intent(getCtx(), mSensorService.getClass());
        resultReceiver = new MyResultReceiver(null);
        mServiceIntent.putExtra("receiver", resultReceiver);
        mServiceIntent.putExtra("host", host);
        mServiceIntent.putExtra("port", port);
        if (!isMyServiceRunning(mSensorService.getClass())) {
            startService(mServiceIntent);
        }

    }


    class UpdateUI implements Runnable {
        String temperatureUpdateString;
        String humidityUpdateString;

        public UpdateUI(String temp, String hum) {
            this.temperatureUpdateString = temp;
            this.humidityUpdateString = hum;

            Log.e("temperatureUpdateString", temperatureUpdateString);
        }


        @Override
        public void run() {
            temperatureView.setText(temperatureUpdateString + "*C");
            humidityView.setText(humidityUpdateString + "%");

        }
    }

    class MyResultReceiver extends ResultReceiver {
        public MyResultReceiver(Handler handler) {
            super(handler);
        }

        @Override
        protected void onReceiveResult(int resultCode, Bundle resultData) {
            if(resultCode == 200) {
                runOnUiThread(new UpdateUI(resultData.getString("temperature"), resultData.getString("humidity")));
            }
        }
    }

    private boolean isMyServiceRunning(Class<?> serviceClass) {
        ActivityManager manager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        for (ActivityManager.RunningServiceInfo service : manager.getRunningServices(Integer.MAX_VALUE)) {
            if (serviceClass.getName().equals(service.service.getClassName())) {
                Log.i ("isMyServiceRunning?", true+"");
                return true;
            }
        }
        Log.i ("isMyServiceRunning?", false+"");
        return false;
    }

    @Override
    protected void onDestroy() {
        stopService(mServiceIntent);
        Log.i("MAINACT", "onDestroy!");
        super.onDestroy();

    }

}
