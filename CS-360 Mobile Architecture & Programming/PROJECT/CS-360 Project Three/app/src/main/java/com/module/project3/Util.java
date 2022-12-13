/**
 * File contains utility methods used throughout the app
 */
package com.module.project3;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.widget.EditText;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * The type Util.
 */
public class Util {


    /**
     * Input length greater boolean.
     *
     * @param input     the input
     * @param maxLength the max length
     * @return the boolean
     */
    public static Boolean inputLengthGreater(EditText input, int maxLength) {
        if (input.length() > maxLength) {
            return false;
        }
        else {
            return true;
        }
    };

    /**
     * Input length less boolean.
     *
     * @param input     the input
     * @param minLength the min length
     * @return the boolean
     */
    public static Boolean inputLengthLess(EditText input, int minLength) {
        if (input.length() < minLength) {
            return false;
        }
        else {
            return true;
        }
    };

    /**
     * Input length equal boolean.
     *
     * @param input  the input
     * @param length the length
     * @return the boolean
     */
    public static Boolean inputLengthEqual(EditText input, int length) {
        if (input.length() != length) {
            return false;
        } else {
            return true;
        }
    };

    /**
     * Compare input boolean.
     *
     * @param input1 the input 1
     * @param input2 the input 2
     * @return the boolean
     */
    public static Boolean compareInput(String input1, String input2) {
        return input1.equals(input2);
    };

    /**
     * Input no letters boolean.
     *
     * @param input the input
     * @return the boolean
     */
    public static Boolean inputNoLetters(EditText input) {
        if (input.getText().toString().matches(".*[a-zA-Z]+.*")) {
            return false;
        } else {
            return true;
        }
    };

    /**
     * Input currency boolean.
     *
     * @param input the input
     * @return the boolean
     */
    public static Boolean inputCurrency(EditText input) {
        if (!input.getText().toString().matches("^[0-9]+(\\.[0-9]{1,2})?$")) {
            return false;
        } else {
            return true;
        }
    };

    /**
     * Input null boolean.
     *
     * @param input the input
     * @return the boolean
     */
    public static final Boolean inputNull(EditText input) {
        if (input.getText().toString().isEmpty()) {
            return true;
        } else {
            return false;
        }
    };

    /**
     * Gets image.
     *
     * @param image the image
     * @return the image
     */
    public static Bitmap getImage(byte[] image) {
        return BitmapFactory.decodeByteArray(image, 0, image.length);
    }

    /**
     * Get bytes byte [ ].
     *
     * @param inputStream the input stream
     * @return the byte [ ]
     * @throws IOException the io exception
     */
    public static byte[] getBytes(InputStream inputStream) throws IOException {
        ByteArrayOutputStream byteBuffer = new ByteArrayOutputStream();
        int bufferSize = 1024;
        byte[] buffer = new byte[bufferSize];

        int len = 0;
        while ((len = inputStream.read(buffer)) != -1) {
            byteBuffer.write(buffer, 0, len);
        }
        return byteBuffer.toByteArray();
    }




}
