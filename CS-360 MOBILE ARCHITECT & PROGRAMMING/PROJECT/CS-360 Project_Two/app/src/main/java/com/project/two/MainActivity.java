package com.project.two;

import static androidx.lifecycle.Transformations.map;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContract;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.activity.result.contract.ActivityResultContracts.RequestMultiplePermissions;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_activity);


        ActivityResultLauncher<String[]> permissionsLauncher =
            registerForActivityResult(new ActivityResultContracts
                .RequestMultiplePermissions(), result -> {
                    Boolean isReadPermissionGranted = result.getOrDefault(
                            Manifest.permission.READ_EXTERNAL_STORAGE, false);
                    Boolean isWritePermissionGranted = result.getOrDefault(
                            Manifest.permission.WRITE_EXTERNAL_STORAGE, false);
                    Boolean isCameraPermissionGranted = result.getOrDefault(
                            Manifest.permission.CAMERA, false);
                    Boolean isSMSPermissionGranted = result.getOrDefault(
                            Manifest.permission.SEND_SMS, false);

                    if (Boolean.TRUE.equals(isReadPermissionGranted) && Boolean.TRUE.equals(isWritePermissionGranted) && Boolean.TRUE.equals(isCameraPermissionGranted) && Boolean.TRUE.equals(isSMSPermissionGranted)) {
                        Intent intent = new Intent(getApplicationContext(), MainActivity.class);
                        startActivity(intent);
                    } else if (shouldShowRequestPermissionRationale(Manifest.permission.READ_EXTERNAL_STORAGE) || shouldShowRequestPermissionRationale(Manifest.permission.WRITE_EXTERNAL_STORAGE) || shouldShowRequestPermissionRationale(Manifest.permission.CAMERA) || shouldShowRequestPermissionRationale(Manifest.permission.SEND_SMS)) {
                       new PermissionsDialog();
                    }
                });
                permissionsLauncher.launch(new String[]{
                        Manifest.permission.READ_EXTERNAL_STORAGE,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE,
                        Manifest.permission.CAMERA,
                        Manifest.permission.SEND_SMS
                });

        final Button registerButton = findViewById(R.id.registerButton);
        final Button loginButton = findViewById(R.id.loginButton);

        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), RegisterActivity.class);
                startActivity(intent);
            }
        });

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), InventoryActivity.class);
                startActivity(intent);
            }
        });

    }
};