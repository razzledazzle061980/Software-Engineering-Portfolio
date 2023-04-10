const fs = require('fs');

//const latest = JSON.parse(fs.readFileSync('./data/news_latest.json', 'utf-8'));
const newsInfo = JSON.parse(fs.readFileSync('./data/news.json', 'utf-8'));

const news = (req, res) => {
    res.render('news', { title: 'News', newsInfo });
}

module.exports = {
    news
}
