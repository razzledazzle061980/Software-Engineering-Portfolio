const mongoose= require( 'mongoose');
const trips= mongoose.model('trips');

// Get trips methods
const getTrips = async (req, res) => {
    if (!!req.params.tripCode) {
        try{
            let response = await trips.findOne({ 'code': req.params.tripCode });
            res.json(response);
        } catch (err) {
            res.status(404).send(`No trip found with code ${req.params.tripCode}`);
        }
        return;
    } else {
        res.json(await trips.find({}));
    }
}

const addTrip = async (req, res) => {
    const newTrip = req.body;

    if (!newTrip) {
        // 404 BAD REQUEST error because no trip was sent in the body of the request
        res.status(400).send('No trip record found in body of request');
        return;
    }

    try {
        const savedTrip = await trips.create(newTrip);

        // 201 CREATED response with the trip -- we send it back
        res.status(201).json(savedTrip);
    } catch (err) {
        // 400 BAD REQUEST because the trip failed to be created
        res.status(400).json(err);
    }
}

const updateTrip = async (req, res) => {
    const tripCode = req.params.tripCode;
    let trip = req.body;
    console.log(tripCode, trips);

    // tripCode in /api/trips/:tripCode and the tripCode of the request body may not match
    // Overwrite the one in the body with one in the URL
    trip = Object.assign(trip, {tripCode});

    try {
        const updateTrip = await trips.findOneAndUpdate({ 'code': tripCode}, trip, { new: true });

        // Null indicates no match was found..return 404 NOT FOUND
        if (updateTrip == null) {
            res.status(404).send(`No trip found with code ${tripCode}`);
            return;
        }

        // Send 200 status message along with updated trip
        res.status(200).json(updateTrip);
    } catch (err) {
        // Send 500 status message along with error
        res.status(500).json(err);
        console.log(`Error Message: ${err.message}`);
    }
}

module.exports = {
    getTrips,
    addTrip,
    updateTrip
}