package com.module5.assignment;

import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EditText name = (EditText) findViewById(R.id.nameText);
        TextView greeting = (TextView) findViewById(R.id.textGreeting);
        Button button = (Button) findViewById(R.id.buttonSayHello);
        name.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if (name.getText().length() == 0) {
                    button.setEnabled(false);
                    greeting.setText("You must enter a name");
                } else {
                    button.setEnabled(true);
                }
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if (name.getText().length() == 0) {
                    button.setEnabled(false);
                    greeting.setText("You must enter a name");
                } else {
                    button.setEnabled(true);
                }
            }

            @Override
            public void afterTextChanged(Editable editable) {
                if (name.getText().length() == 0) {
                    button.setEnabled(false);
                    greeting.setText("You must enter a name");
                } else {
                    button.setEnabled(true);
                }
            }
        });
    }

    public void SayHello(View view) {
        EditText name = (EditText) findViewById(R.id.nameText);
        TextView greeting = (TextView) findViewById(R.id.textGreeting);
        if (name.getText().length() > 0) {
            greeting.setText("Hello " + name.getText());
        } else {
            greeting.setText("You must enter a name");
        }
    }




}