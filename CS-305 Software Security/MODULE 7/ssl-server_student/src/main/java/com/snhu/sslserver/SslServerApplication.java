package com.snhu.sslserver;

import org.springframework.boot.SpringApplication;

import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;


@SpringBootApplication
public class SslServerApplication {
	// Function creating the hash and returns its value
	public static byte[] digest(byte[] input, String alg) {
		try {
			MessageDigest md = MessageDigest.getInstance(alg);
			return md.digest(input);
		} catch (NoSuchAlgorithmException e) {
			throw new IllegalArgumentException(e);
		}
	}

	// Converts the string provided into hex characters
	public static String bytesToHex(byte[] bytes) {
		/* default */
		StringBuilder sb = new StringBuilder();
		for (byte b : bytes) {
			sb.append(String.format("%02x", b));
		}
		return sb.toString();
	}

	/* default */
	public static void main(String[] args) {
		SpringApplication.run(SslServerApplication.class, args);
	}
}
	@RestController
	class ServerController{
		/* default */ String ALGORITHM = "SHA-256";
		/* default */ String PHRASE = "Eric Wallace";

		// URI mapping
		@RequestMapping("/checksum")
		public String generateHash() {
			// Sets the character set to use
			Charset utf8 = StandardCharsets.UTF_8;

			// Call to generate the hash and return it to a variable
			/* default */ byte[] inBytes = SslServerApplication.digest(PHRASE.getBytes(utf8), ALGORITHM);

			// This outputs the hash, cipher and then converts the hash to a hex value
			return "Phrase:  " + PHRASE + "<br>" +
					"Cipher:  " + ALGORITHM + "<br>" +
					"Checksum:  " + SslServerApplication.bytesToHex(inBytes);
			
		}
	}



