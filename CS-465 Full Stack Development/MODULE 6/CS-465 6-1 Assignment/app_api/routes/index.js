// Require all modules
const express = require('express');
const router = express.Router();
const tripsRouter = require('./trips');

// Use all routes
router.use('/trips', tripsRouter);


module.exports = router;