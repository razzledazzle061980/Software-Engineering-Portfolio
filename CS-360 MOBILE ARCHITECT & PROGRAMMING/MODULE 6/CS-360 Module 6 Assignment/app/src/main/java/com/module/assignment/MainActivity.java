package com.module.assignment;
import android.annotation.SuppressLint;
import android.content.Context;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.RotateAnimation;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {

    private SensorManager mSensorManager;
    private Sensor mMagnetometer;
    private Sensor mAccelerometer;
    private final float[] mRotationMatrix = new float[9];
    private final float[] mOrientationAngles = new float[3];
    private float[] accelerometerReading = new float[3];
    private float[] magnetometerReading = new float[3];
    private float mLastDirectionInDegrees = 0f;
    RotateAnimation mRotateAnimation;
    ImageView mImageViewCompass;
    TextView mTextViewDegree;
    Sensor sensor;
    SensorEventListener magnetometerEventListener;
    SensorEventListener accelerometerEventListener;


    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Initialize compass image
        // Define the compass image
        mImageViewCompass = (ImageView) findViewById(R.id.imageViewNeedle);
        mTextViewDegree = (TextView) findViewById(R.id.degreeTextView);
        // Device sensor manager
        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        mMagnetometer = mSensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        mAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);

        // Create and initialize accelerometer listener SensorEventListener
        accelerometerEventListener = new SensorEventListener() {

            @Override
            public void onSensorChanged(SensorEvent event) {
                accelerometerReading = event.values;
                if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                    SensorManager.getRotationMatrix(mRotationMatrix, null, accelerometerReading, magnetometerReading);
                    SensorManager.getOrientation(mRotationMatrix, mOrientationAngles);
                    updateOrientationAngles();
                }
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int accuracy) {
                // Do nothing
            }
        };

        // Create and initialize listener SensorEventListener
        magnetometerEventListener = new SensorEventListener() {

            @Override
            public void onSensorChanged(SensorEvent event) {
                magnetometerReading = event.values;
                if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
                    SensorManager.getRotationMatrix(mRotationMatrix, null, accelerometerReading, magnetometerReading);
                    SensorManager.getOrientation(mRotationMatrix, mOrientationAngles);
                    updateOrientationAngles();
                }
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int accuracy) {
                // Do nothing
            }
        };
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (mAccelerometer != null) {
            mSensorManager.registerListener(accelerometerEventListener, mAccelerometer,
                    SensorManager.SENSOR_DELAY_NORMAL, SensorManager.SENSOR_DELAY_UI);
        }
        if (mMagnetometer != null) {
            mSensorManager.registerListener(magnetometerEventListener, mMagnetometer,
                    SensorManager.SENSOR_DELAY_NORMAL, SensorManager.SENSOR_DELAY_UI);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        // Stop the listener when the application is paused
        mSensorManager.unregisterListener(accelerometerEventListener);
        mSensorManager.unregisterListener(magnetometerEventListener);
    }
        /*mRotateAnimation = new RotateAnimation(
                mLastDirectionInDegrees,
                -degree,
                Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF,
                0.5f);
        mRotateAnimation.setDuration(210);
        mRotateAnimation.setFillAfter(true);
        mImageViewCompass.startAnimation(mRotateAnimation);
        mLastDirectionInDegrees = -degree;*/


    public void updateOrientationAngles() {
        String direction;
        // Update rotation matrix, which is needed to update orientation angles.
        SensorManager.getRotationMatrix(mRotationMatrix, null,
                accelerometerReading, magnetometerReading);

        // "rotationMatrix" now has up-to-date information.

        SensorManager.getOrientation(mRotationMatrix, mOrientationAngles);


        int rotationVector = (int) Math.round((mOrientationAngles[0] * 180 / 3.1459));
        if (rotationVector == 0) direction = "N";
        else if (rotationVector == 90) direction = "E";
        else if (rotationVector == -180) direction = "S";
        else if (rotationVector == -90) direction = "W";
        else if (rotationVector > 0 && rotationVector < 90) direction = "NE";
        else if (rotationVector > 90 && rotationVector < 180) direction = "SE";
        else if (rotationVector < 0 && rotationVector > -90) direction = "NW";
        else if (rotationVector < -90 && rotationVector > -180) direction = "SW";
        else direction = "N";
        mTextViewDegree.setText(String.valueOf(rotationVector + "° " + direction));
        mImageViewCompass.setRotation((int) rotationVector);

        // "orientationAngles" now has up-to-date information.5
    }

}
