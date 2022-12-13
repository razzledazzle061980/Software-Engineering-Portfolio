package com.project.two;

import android.content.Context;
import android.media.Rating;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.RatingBar;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;
import java.util.Random;

public class ItemsAdapter extends RecyclerView.Adapter<ItemsAdapter.ViewHolder> {

    public static class ViewHolder extends RecyclerView.ViewHolder {

        public TextView cardTitle;
        public TextView cardDescription;
        public ImageView cardImage;
        public RatingBar cardRating;
        public ToggleButton cardFav;


        public ViewHolder(View itemView) {
            super(itemView);
            cardTitle = itemView.findViewById(R.id.cardTitle);
            cardDescription = itemView.findViewById(R.id.cardDescription);
            cardImage = itemView.findViewById(R.id.cardImage);
            cardRating = itemView.findViewById(R.id.cardRating);
            cardFav = itemView.findViewById(R.id.cardFav);
        }


    }

   private List<Item> mItems;

    public ItemsAdapter(List<Item> items) {
        mItems = items;
    }

    @NonNull
    @Override
    public ItemsAdapter.ViewHolder onCreateViewHolder( ViewGroup parent, int viewType) {
        Context context = parent.getContext();
        LayoutInflater inflater = LayoutInflater.from(context);

        View itemView = inflater.inflate(R.layout.item_card, parent, false);
        return new ViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Item item = mItems.get(position);

        TextView titleView = holder.cardTitle;
        titleView.setText(item.getTitle());
        TextView descriptionView = holder.cardDescription;
        descriptionView.setText(item.getDescription());
        ImageView imageView = holder.cardImage;
        imageView.setImageResource(R.drawable.image_icon);
        RatingBar ratingView = (RatingBar) holder.cardRating;
        ratingView.setRating(item.getRating());
        ToggleButton favView = holder.cardFav;
        favView.setChecked(item.getIsFavorite());
    }

    @Override
    public int getItemCount() {
        return mItems.size();
    }

    public void addItem(String item) {
        String description = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Tortor id aliquet lectus proin nibh nisl condimentum id. Hac habitasse platea dictumst quisque sagittis purus. Enim tortor at auctor urna nunc id. Dui nunc mattis enim ut tellus elementum sagittis.";
        String options = "0123456789";
        Float[] ratingOptions = {0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f};
        Boolean[] favOptions = {true, false};
        Boolean isFav = favOptions[new Random().nextInt(favOptions.length)];
        int rand = new Random().nextInt(options.length());
        Float rating = ratingOptions[new Random().nextInt(ratingOptions.length)];
        mItems.add(new Item("Item ", description, "@drawable/image_icon", rand, isFav, rating));
        notifyItemInserted(mItems.size() - 1);
    }

    public void deleteItem(int position) {
        mItems.remove(position);
        notifyItemRemoved(position);
    }

}
