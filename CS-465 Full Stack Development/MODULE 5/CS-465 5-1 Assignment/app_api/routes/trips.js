// Require modules
const express = require('express');
const router = express.Router();
const controller = require('../controllers/trips');

// Declare methods
router.get('/:tripCode?', controller.getTrips);

module.exports = router;