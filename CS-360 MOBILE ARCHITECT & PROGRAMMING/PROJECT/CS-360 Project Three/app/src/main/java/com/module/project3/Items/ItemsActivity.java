package com.module.project3.Items;

import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.module.project3.*;
import com.module.project3.db.ItemDataManager;

import java.util.ArrayList;
import java.util.List;

/**
 * The type Items activity.
 */
public class ItemsActivity extends AppCompatActivity {

    private RecyclerView recyclerView;
    private RecyclerView.Adapter adapter;
    private RecyclerView.LayoutManager layoutManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.view_items);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbarMain);
        setSupportActionBar(toolbar);

        RecyclerView recyclerView = findViewById(R.id.items_list);
        ItemDataManager itemDataManager = new ItemDataManager(this);
        List<Item> items = new ArrayList<>();
        Cursor c = itemDataManager.selectAll();

        while(c.moveToNext()) {
            Integer id  = c.getInt(0);
            String title = c.getString(1);
            String description = c.getString(2);
            Integer quantity = c.getInt(3);
            double price = c.getDouble(4);
            boolean fav = c.getInt(5) == 1;
            byte[] image = c.getBlob(6);

            items.add(new Item(id, title, description, quantity, price, fav, image));
        }

        ItemsAdapter adapter = new ItemsAdapter(items);

        recyclerView.setAdapter(adapter);

        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        ImageButton addBtn = findViewById(R.id.itemsAddBtn);

        addBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent addItemIntent = new Intent(ItemsActivity.this, ItemActivity.class);
                addItemIntent.putExtra("type", "new");
                addItemIntent.putExtra("id", 0);
                startActivity(addItemIntent);
            }
        });
    }
}
