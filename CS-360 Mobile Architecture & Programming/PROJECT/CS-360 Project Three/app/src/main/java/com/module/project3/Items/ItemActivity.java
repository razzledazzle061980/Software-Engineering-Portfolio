package com.module.project3.Items;

import static com.module.project3.Util.inputNull;

import static java.lang.Integer.parseInt;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ToggleButton;

import androidx.appcompat.app.AppCompatActivity;

import com.module.project3.*;
import com.module.project3.db.ItemDataManager;
import com.module.project3.db.UserDataManager;

/**
 * The type Item activity.
 */
public class ItemActivity extends AppCompatActivity {
    private Button saveBtn, deleteBtn;
    private EditText titleText, descriptionText, quantityText, priceText;
    private ToggleButton favBtn;
    private ItemDataManager dbHelper;


    /**
     * The Add item intent.
     */
    Intent addItemIntent = new Intent();
    /**
     * The Type.
     */
    String type = getIntent().getStringExtra("type");
    /**
     * The Item id.
     */
    Integer itemId = getIntent().getIntExtra("itemId", 0);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_item);
        dbHelper = new ItemDataManager(this);

        saveBtn = findViewById(R.id.itemSaveBtn);
        deleteBtn = findViewById(R.id.itemDeleteBtn);
        favBtn = findViewById(R.id.itemFavBtn);
        titleText = findViewById(R.id.itemTitleEdit);
        descriptionText = findViewById(R.id.itemDescEdit);
        quantityText = findViewById(R.id.itemQuantityEdit);
        priceText = findViewById(R.id.itemPriceEdit);

        saveBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String title = titleText.getText().toString();
                String description = descriptionText.getText().toString();
                int quantity = parseInt(quantityText.getText().toString());
                double price = parseInt(priceText.getText().toString());
                boolean fav = favBtn.isChecked();

                if(inputNull(titleText)) {
                    titleText.setError("Title is required");
                } else if(inputNull(descriptionText)) {
                    descriptionText.setError("Description is required");
                } else if(inputNull(quantityText)) {
                    quantityText.setError("Quantity is required");
                } else if(inputNull(priceText)) {
                    priceText.setError("Price is required");
                } else {
                    if(type.equals("add")) {
                        dbHelper.insert(title, description, quantity, price, fav);
                    } else if(type.equals("edit")) {
                        dbHelper.update(itemId, title, description, quantity, price, fav);
                    }
                    finish();
                }
            }
        });

        deleteBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                dbHelper.delete(itemId);
                finish();
            }
        });



    }
}
