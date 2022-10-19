package com.example.gridlayout;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class GameOver extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game_over);
        Intent intent = getIntent();
        TextView tv = findViewById(R.id.textView);
        String time_message = "Used " + intent.getStringExtra("time") + " seconds.\n";
        String won = intent.getStringExtra("result");
        String win_lose;
        if(won.equals("won")){
            win_lose="You won!";
        }else{
            win_lose="You lost.";
        }
        String final_message = time_message + win_lose;
        tv.setText(final_message);
    }
    public void replay(View view){
        // Create a new intent to restart game
        Intent intent = new Intent(GameOver.this, MainActivity.class);
        startActivity(intent);
    }
}