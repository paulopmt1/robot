var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');


io.on('connection', function(socket){
  console.log('a user connected');
  io.emit('serverStatus', { for: 'everyone'});
  
  setInterval(function(){
  	io.emit('serverStatus', { for: 'everyone' });
  },100);


  socket.on('userCommand', function(msg){
    io.emit('userCommand', msg);
    console.log(msg);
  });

  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});

io.on('connection', function(socket){

  setInterval(function(){
  	fs.readFile(__dirname + '/images/camera.jpg', function(err, buf){
	    // it's possible to embed binary data
	    // within arbitrarily-complex objects
	    socket.emit('imageBlob', { image: true, buffer: buf.toString('base64') });
	    //socket.emit('imageBlob', { buffer: buf });
	  });


  },41)
});



app.get('/', function(req, res){
  res.send('<h1>Controle do robô</h1>');
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
