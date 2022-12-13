package com.project.two;

import static android.app.PendingIntent.getActivity;

import android.content.DialogInterface;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AlertDialog;
import androidx.fragment.app.DialogFragment;
import androidx.fragment.app.FragmentManager;

import java.util.Objects;

public class PermissionsDialog extends DialogFragment {
    private Button mButton;

    public PermissionsDialog() {
        showPermissionsDialog();
    }

    public static PermissionsDialog newInstance(String title) {
        PermissionsDialog frag = new PermissionsDialog();
        Bundle args = new Bundle();
        args.putString("title", title);
        frag.setArguments(args);
        return frag;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(R.layout.permissions_dialog, container);
    }

    public void showPermissionsDialog() {
        FragmentManager fm = requireActivity().getSupportFragmentManager();
        PermissionsDialog dialog = new PermissionsDialog();
        dialog.show(fm, "permissions_dialog");
    }

    public void onClose() {
        dismiss();
    }


}