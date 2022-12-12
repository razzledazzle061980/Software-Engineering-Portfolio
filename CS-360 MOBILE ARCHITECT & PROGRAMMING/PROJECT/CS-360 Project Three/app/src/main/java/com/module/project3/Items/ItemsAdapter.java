package com.module.project3.Items;


import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.module.project3.*;
import com.module.project3.db.ItemDataManager;

import java.util.List;


/**
 * The type Items adapter.
 */
public class ItemsAdapter extends RecyclerView.Adapter<ItemsAdapter.ViewHolder> {
    /**
     * The Item db helper.
     */
    ItemDataManager itemDbHelper;


    private final List<Item> mItems;

    /**
     * Instantiates a new Items adapter.
     *
     * @param items the items
     */
    public ItemsAdapter(List<Item> items) {
        mItems = items;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        Context context = parent.getContext();
        LayoutInflater inflater = LayoutInflater.from(context);
        return new ViewHolder(inflater.inflate(R.layout.item_card, parent, false));
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        holder.itemTitle.setText(mItems.get(position).getTitle());
        holder.itemDescription.setText(mItems.get(position).getDescription());
        holder.itemPrice.setText(String.valueOf(mItems.get(position).getPrice()));
        holder.itemQuantity.setText(String.valueOf(mItems.get(position).getQuantity()));
        holder.itemFavBtn.setChecked(mItems.get(position).getFavorite());
    }

    @Override
    public int getItemCount() {
        return 0;
    }


    /**
     * The type View holder.
     */
    public class ViewHolder extends RecyclerView.ViewHolder {
        /**
         * The Item title.
         */
        public TextView itemTitle;
        /**
         * The Item description.
         */
        public TextView itemDescription;
        /**
         * The Item price.
         */
        public TextView itemPrice;
        /**
         * The Item image.
         */
        public ImageView itemImage;
        /**
         * The Item quantity.
         */
        public TextView itemQuantity;
        /**
         * The Item fav btn.
         */
        public ToggleButton itemFavBtn;

        /**
         * Instantiates a new View holder.
         *
         * @param itemView the item view
         */
        public ViewHolder(View itemView) {
        super(itemView);
        itemTitle = itemView.findViewById(R.id.itemName);
        itemDescription = itemView.findViewById(R.id.itemDescription);
        itemPrice = itemView.findViewById(R.id.itemPrice);
        itemQuantity = itemView.findViewById(R.id.itemQuantity);
        itemFavBtn = itemView.findViewById(R.id.itemFavButton);
    }
}

}
