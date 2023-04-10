const mongoose= require( 'mongoose');
const trips= mongoose.model('trips');

// Get trips methods
const getTrips = async (req, res) => {
    if (req.params.tripCode) {
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


module.exports = {
    getTrips
}