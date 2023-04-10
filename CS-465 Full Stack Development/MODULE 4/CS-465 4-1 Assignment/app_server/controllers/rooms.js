const fs = require('fs');

const roomInfo = JSON.parse(fs.readFileSync('./data/rooms.json', 'utf-8'));

const rooms = (req, res) => {
    res.render('rooms', { title: 'Rooms', roomInfo });
}

module.exports = {
    rooms
}
