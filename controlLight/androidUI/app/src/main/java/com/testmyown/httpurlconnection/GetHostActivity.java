package com.testmyown.httpurlconnection;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class GetHostActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_get_host);

        Button submitBtn = (Button) findViewById(R.id.submit);
        submitBtn.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {

                Intent myIntent = new Intent( GetHostActivity.this , ControlLedActivity.class);
                TextView hostText = (TextView) findViewById(R.id.host);
                String host = hostText.getText().toString();
                myIntent.putExtra("host", host);
                TextView portText = (TextView) findViewById(R.id.port);
                String port = portText.getText().toString();
                myIntent.putExtra("port", port);

                startActivity(myIntent);
            }
        });



    }
}
