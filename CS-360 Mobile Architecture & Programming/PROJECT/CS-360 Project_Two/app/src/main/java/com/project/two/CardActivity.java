package com.project.two;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class CardActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.item_card);

        final Button favBtn = findViewById(R.id.cardFav);

        favBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (favBtn.getTag().equals("fav")) {
                    favBtn.setBackgroundResource(R.drawable.ic_fav_off);
                    favBtn.setTag("notFav");
                } else {
                    favBtn.setBackgroundResource(R.drawable.ic_fav_on);
                    favBtn.setTag("fav");
                }
            }
        });
    }
}