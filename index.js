var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');
var serialPort = '/dev/ttyACM0';
var lastSerialMessage = '';
var activeConnections = [];


io.on('connection', function(socket){
  activeConnections.push(socket);

  console.log('a user connected');
  io.emit('serverStatus', { for: 'everyone'});
  
  setInterval(function(){
  	io.emit('serverStatus', { for: 'everyone' });
  },100);


  socket.on('userCommand', function(msg){
    //io.emit('userCommand', msg);
    console.log(msg);

    if (msg.command){
      sendToSerial(msg.command);
    }
  });

  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});

io.on('connection', function(socket){

/*  setInterval(function(){
  	fs.readFile(__dirname + '/images/camera.jpg', function(err, buf){
	    // it's possible to embed binary data
	    // within arbitrarily-complex objects
	    socket.emit('imageBlob', { image: true, buffer: buf.toString('base64') });
	    //socket.emit('imageBlob', { buffer: buf });
	  });


  },41)

*/
});



var SerialPort = require("serialport");
var port = new SerialPort(serialPort, {
  baudRate: 9600,
  parser: SerialPort.parsers.readline('\n')
});

port.on('open', function() {
  port.write('main screen turn on', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
  });
});
 
// open errors will be emitted as an error event 
port.on('error', function(err) {
  console.log('Error: ', err.message);
});

port.on('data', function(data){
  console.log("Recebido da serial: " + data);
  lastSerialMessage = data;
  
  sendToAllConnections(data);
});

var sendToSerial = function(msg){
  port.write(msg);
};

var sendToAllConnections = function(data){
  for (var i = activeConnections.length - 1; i >= 0; i--) {
    activeConnections[i].write(data);
  }
}



app.get('/', function(req, res){
  res.send('<h1>Controle do robô</h1>');
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
