package com.gameroom.gameauth;

import io.dropwizard.Application;
import io.dropwizard.Configuration;
import io.dropwizard.auth.AuthDynamicFeature;
import io.dropwizard.auth.AuthValueFactoryProvider;
import io.dropwizard.auth.basic.BasicCredentialAuthFilter;
import io.dropwizard.client.JerseyClientBuilder;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;

import javax.ws.rs.client.Client;

import org.glassfish.jersey.server.filter.RolesAllowedDynamicFeature;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.gameroom.gameauth.auth.GameAuthenticator;
import com.gameroom.gameauth.auth.GameAuthorizer;
import com.gameroom.gameauth.auth.GameUser;

import com.gameroom.gameauth.controller.GameUserRESTController;
import com.gameroom.gameauth.controller.RESTClientController;

import com.gameroom.gameauth.healthcheck.AppHealthCheck;
import com.gameroom.gameauth.healthcheck.HealthCheckController;



public class GameAuthApplication extends Application<Configuration> {
	private static final Logger LOGGER = LoggerFactory.getLogger(GameAuthApplication.class);

	@Override
	public void initialize(Bootstrap<Configuration> b) {
	}

	@Override
	public void run(Configuration c, Environment e) throws Exception 
	{
		
		LOGGER.info("Registering REST resources");
 
		// Register REST Controller with Jersey
		e.jersey().register(new GameUserRESTController(e.getValidator()));

		// Create instance of JerseyClientBuilder
		final Client client = new JerseyClientBuilder(e).build("DemoRESTClient");

		// Register REST Client Controller
		e.jersey().register(new RESTClientController(client));

		// Application health check
		e.healthChecks().register("APIHealthCheck", new AppHealthCheck(client));

		// Run multiple health checks
		e.jersey().register(new HealthCheckController(e.healthChecks()));
		
		//Setup Basic Security
		e.jersey().register(new AuthDynamicFeature(new BasicCredentialAuthFilter.Builder<GameUser>()
                .setAuthenticator(new GameAuthenticator())
                .setAuthorizer(new GameAuthorizer())
                .setRealm("App Security")
                .buildAuthFilter()));
        e.jersey().register(new AuthValueFactoryProvider.Binder<>(GameUser.class));
        e.jersey().register(RolesAllowedDynamicFeature.class);
	}

	public static void main(String[] args) throws Exception {
		new GameAuthApplication().run(args);
	}
}