// Require all modules
const express = require('express');
const router = express.Router();
const tripsRouter = require('./trips');
const authRouter = require('./authentication');

// Use all routes
router.use('/trips', tripsRouter);
router.use('/auth', authRouter);


module.exports = router;