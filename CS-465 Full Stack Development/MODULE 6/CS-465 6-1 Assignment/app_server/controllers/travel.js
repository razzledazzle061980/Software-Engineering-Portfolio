/* Get travel view */
const mongoose = require('mongoose');
const trips = mongoose.model('trips');

const travel = async (req, res) => {
    res.render('travel', { title: 'Travlr Getaway', trips: await trips.find({}) });
}

module.exports = {
    travel
}