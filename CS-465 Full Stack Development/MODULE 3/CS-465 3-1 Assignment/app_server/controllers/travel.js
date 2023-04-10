/* Get travel view */
const fs = require('fs');

const trips = JSON.parse(fs.readFileSync('./data/trips.json', 'utf-8'));

const travel = (req, res) => {
    res.render('travel', { title: 'Travlr Getaway', trips });
}

module.exports = {
    travel
}