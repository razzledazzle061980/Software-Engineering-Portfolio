package com.testapp;

import io.dropwizard.Application;
import io.dropwizard.setup.Bootstrap;
import io.dropwizard.setup.Environment;
import com.testapp.resources.TestAppResource;

public class TestAppApplication extends Application<TestAppConfiguration> {

    public static void main(final String[] args) throws Exception {
        new TestAppApplication().run(args);
    }

    @Override
    public String getName() {
        return "TestApp";
    }

    @Override
    public void initialize(final Bootstrap<TestAppConfiguration> bootstrap) {
        // TODO: application initialization
    }

    @Override
    public void run(final TestAppConfiguration configuration,
        final Environment environment) {
            environment.jersey().register(
                    new TestAppResource()
            );
    }

}
