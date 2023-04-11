// Require modules
const express = require('express');
const router = express.Router();
const controller = require('../controllers/trips');
const { expressjwt: jwt } = require('express-jwt');

const auth = jwt({ secret: process.env.JWT_SECRET, algorithms: ['HS512'] });

// Declare methods
router.get('/:tripCode?', controller.getTrips);
router.post('/', auth, controller.addTrip);
router.put('/:tripCode', auth, controller.updateTrip);

module.exports = router;