require('dotenv').load()

var express = require('express')
var app = express()
var http = require('http').Server(app)
var path = require('path')
var spark = require('spark')
var havenondemand = require('havenondemand')
var hodClient = new havenondemand.HODClient('http://api.havenondemand.com', process.env.hpe_apikey)
var Twitter = require('twitter')

var twitterClient = new Twitter({
  consumer_key: process.env.consumer_key,
  consumer_secret: process.env.consumer_secret,
  access_token_key: process.env.access_token,
  access_token_secret: process.env.access_token_secret
})

spark.login({accessToken: process.env.access_token_spark})

var port = process.env.PORT || 5000
app.use(express.static(path.join(__dirname, 'public')))

var nLogos = 0
var nFaces = 0
var c = 0.2
var powerBar
var hashTag = 'halloweeniot'

spark.getDevice(process.env.device_id_spark, function(err, device) {
  debugger
  console.log('Device name: ' + device.name)
  twitterClient.stream('statuses/filter', {track: hashTag}, function(stream) {
    stream.on('data', function(tweet) {
      console.log("------------------------------")
      console.log(tweet.text)
      debugger
      var imageUrl = tweet.extended_entities.media[0].media_url
      if (imageUrl) {
        var data1 = {url: imageUrl}
        hodClient.call('detectfaces', data1, function(err1, resp1, body1) {
          debugger
          var faces = resp1.body.face
          if (faces.length>0){
            for (var i=0; i<faces.length; i++) { nFaces += 1; }
            var data2 = {image_type: 'complex_3d', indexes: 'corporatelogos', url: imageUrl}
            hodClient.call('recognizeimages', data2, function(err2, resp2, body2) {
              debugger
              var logos = resp2.body.object
              for (var i=0; i<logos.length; i++) {
                if( logos[i].name ==="HPQ" ){ nLogos += 1; } // increase only if logo is HP
              }
              powerBar = Math.floor( nFaces*(1 + c*nLogos) )
              console.log("# Faces " + nFaces)
              console.log("# Logos " + nLogos)
              console.log("Power bar " + powerBar)
              // Microcontroller access software
              device.callFunction('sendFaces', nFaces, function(error1, data1) {
                if (err) {
                  console.log('An error occurred:', error1)
                } else {
                  console.log('Function called succesfully:', data1)
                }
              })
              device.callFunction('sendLogos', nLogos, function(error2, data2) {
                if (err) {
                  console.log('An error occurred:', error2)
                } else {
                  console.log('Function called succesfully:', data2)
                }
              })
              device.callFunction('sendPowerBar', powerBar, function(error3, data3) {
                if (err) {
                  console.log('An error occurred:', error3)
                } else {
                  console.log('Function called succesfully:', data3)
                }
              })
              //
            })
          }
        })
      }
    })

    stream.on('error', function(error) {
      throw error
    })
  })
})
