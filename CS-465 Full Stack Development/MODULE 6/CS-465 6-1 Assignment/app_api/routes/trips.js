// Require modules
const express = require('express');
const router = express.Router();
const controller = require('../controllers/trips');

// Declare methods
router.get('/:tripCode?', controller.getTrips);
router.post('/', controller.addTrip);
router.put('/:tripCode', controller.updateTrip);
router.delete('/:tripCode', controller.deleteTrip);

module.exports = router;