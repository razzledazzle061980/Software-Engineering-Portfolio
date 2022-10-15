package com.snhu.sslserver;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


@SpringBootApplication
public class ServerApplication {
    // Function creating the hash and returns its value
    public static byte[] digest(byte[] input, String algorithm) {
        MessageDigest md;
        try {
            md = MessageDigest.getInstance(algorithm);
        } catch (Exception e) {
            throw new IllegalArgumentException(e);
        }
        byte[] result = md.digest(input);
        return result;
    }

    // Converts the value provided to hexidecimal characters
    public static String bytesToHex(byte[] bytes) {
        StringBuilder sb = new StringBuilder();
        for (byte b : bytes) {
            sb.append(String.format("%02x", b));
        }
        return sb.toString();
    }

	public static void main(String[] args) {
		SpringApplication.run(ServerApplication.class, args);
    }

@RestController
class ServerController{
    String algorithm = "SHA-256";
    String hash = "Eric Wallace";

    // URI mapping
    @RequestMapping("/hex")
    public String executeHash() {
        // Sets the character set to use
        Charset utf8 = StandardCharsets.UTF_8;

        // Call to generate the hash and return it to a variable
        byte[] inBytes = ServerApplication.digest(hash.getBytes(utf8), algorithm);

        // This ouputs the hash, cipher and then converts the hash to a hex value
        return "Hash:  " + hash + "<br><br>" + " Cipher: " + algorithm + "<br><br> Checksum: " + bytesToHex(inBytes);
    }
}

}


