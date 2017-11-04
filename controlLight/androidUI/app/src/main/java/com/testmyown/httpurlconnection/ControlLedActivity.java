package com.testmyown.httpurlconnection;

import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class ControlLedActivity extends AppCompatActivity {

    String host;
    String port;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control_led);

        Intent intent = getIntent();
        String hostTmp = intent.getStringExtra("host");
        String portTmp = intent.getStringExtra("port");

        host = hostTmp;
        port = portTmp;

        Button onButton = (Button) findViewById(R.id.on);
        onButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                sendPostRequest(view, "on");
            }
        });

        Button offButton = (Button) findViewById(R.id.off);
        offButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                sendPostRequest(view, "off");
            }
        });
    }

    public void sendPostRequest(View view, String status) {
        new PostClass(this).execute(status);
    }

    private class PostClass extends AsyncTask<String, Void, Void> {
        private final Context context;

        public PostClass(Context c) {
            this.context = c;
        }

        @Override
        protected Void doInBackground(String... strings) {
            try {
                final TextView outputView = (TextView) findViewById(R.id.showOutput);
                String urlString = "http://" + host + ":" + port + "/light";
                URL url = new URL(urlString);
                //String urlParameters = "status=on";
                HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                connection.setRequestMethod("POST");
                connection.setRequestProperty("USER-AGENT", "Mozilla/5.0");
                connection.setRequestProperty("content-type", "application/json");
                connection.setDoOutput(true);
                JSONObject data = new JSONObject();
                data.put("status", strings[0]);

                DataOutputStream dStream = new DataOutputStream(connection.getOutputStream());
                dStream.writeBytes(data.toString());
                dStream.flush();
                dStream.close();

                int responseCode = connection.getResponseCode();
                final StringBuilder output = new StringBuilder("Request URL: " + url);
                output.append(System.getProperty("line.separator") + "Request Parameters " + data.toString());
                output.append(System.getProperty("line.separator") + "Response Code " + responseCode);
                output.append(System.getProperty("line.separator") + "Type " + "POST");
                BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
                String line = "";
                StringBuilder responseOutput = new StringBuilder();
                System.out.println("output: " + br);
                while((line = br.readLine()) != null) {
                    responseOutput.append(line);
                }
                br.close();
                output.append(System.getProperty("line.separator") + "Response " + System.getProperty("line.separator") + System.getProperty("line.separator") + responseOutput.toString());

                ControlLedActivity.this.runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        outputView.setText(output);
                        //progress.dismiss();
                    }
                });

            } catch (MalformedURLException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }
            return null;
        }
    }
}
