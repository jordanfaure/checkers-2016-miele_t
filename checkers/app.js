var express = require('express');

var app = express()

app.use(express.static(__dirname + '/static'));

app.get('/', function(request, response) {
    response.render('app.ejs', {})
});

app.use(function(request, response, next) {
    response.setHeader('Content-Type', 'text/plain');
    response.send(404, 'Page not found !');
});

app.listen(8080);
