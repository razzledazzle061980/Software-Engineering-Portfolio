package com.project.two;

import java.util.ArrayList;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.Menu;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

public class InventoryActivity extends AppCompatActivity {

    ArrayList<Item> items;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.inventory_activity);

        @SuppressLint({ "MissingInflatedId", "LocalSuppress" })

        RecyclerView inventoryItems = (RecyclerView) findViewById(R.id.inventoryItems);

        items = Item.createItemList(20);

        ItemsAdapter adapter = new ItemsAdapter(items);

        inventoryItems.setAdapter(adapter);

        inventoryItems.setLayoutManager(new LinearLayoutManager(this));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.toolbar, menu);
        return true;
    }
}
