require('dotenv').load()

var express = require('express')
var app = express()
var http = require('http').Server(app)
var path = require('path')
var havenondemand = require('havenondemand')
var hodClient = new havenondemand.HODClient('http://api.havenondemand.com', process.env.hpe_apikey)
var Twitter = require('twitter')

var twitterClient = new Twitter({
  consumer_key: process.env.consumer_key,
  consumer_secret: process.env.consumer_secret,
  access_token_key: process.env.access_token,
  access_token_secret: process.env.access_token_secret
})

var port = process.env.PORT || 5000
app.use(express.static(path.join(__dirname, 'public')))

var nLogos = 0
var nFaces = 0

twitterClient.stream('statuses/filter', {track: 'halloweeniot'}, function(stream) {
  stream.on('data', function(tweet) {
    console.log("------------------------------")
    console.log(tweet.text)
    debugger
    var imageUrl = tweet.extended_entities.media[0].media_url
    var data1 = {image_type: 'complex_3d', indexes: 'corporatelogos', url: imageUrl}
    hodClient.call('recognizeimages', data1, function(err1, resp1, body1){
      debugger
      var logos = resp1.body.object
      for (var i=0; i<logos.length; i++) { nLogos += 1; }
      var data2 = {url: imageUrl}
      hodClient.call('detectfaces', data2, function(err2, resp2, body2){
        debugger
        var faces = resp2.body.face
        for (var i=0; i<faces.length; i++) { nFaces += 1; }
        console.log("# Faces " + nFaces)
        console.log("# Logos " + nLogos)
        //
        // Microcontroller access software
        //
      })
    })
  })

  stream.on('error', function(error) {
    throw error
  })
})
