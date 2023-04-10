const mongoose = require('mongoose');
const host = process.env.DB_HOST || '127.0.0.1'
const connURI = `mongodb://${host}/travlr`;

// Import seed
const {seed } = require('./seed');

// Register trips model
require('./trips')

mongoose.

// Detect changes in database connection state
mongoose.connection.on('connected', () => console.log('CONNECTED'));
mongoose.connection.on('error', err => console.log(`Mongoose connection error: ${err}`));
mongoose.connection.on('disconnected', () => console.log('Mongoose disconnected'));

mongoose.set('strictQuery', false);

// Kill MongoDB connections before exiting the app
const gracefulShutdown = (msg, callback) => {
    mongoose.connection.close( () => {
        console.log(`Mongoose disconnected through ${msg}`);
        callback();
    });
};
// For nodemon restarts
process.once('SIGUSR2', () => {
    gracefulShutdown('nodemon restart', () => process.kill(process.pid, 'SIGUSR2'))
});

process.on('SIGINT', () => {
    gracefulShutdown('app termination', () => process.exit(0))
});

const main = async () => {
    await mongoose.connect(connURI);
    await seed();
}

main().catch(err => console.log(err));